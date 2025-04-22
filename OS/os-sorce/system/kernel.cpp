#include <stdint.h>
#include "RamContext.h"

extern "C" void boot_main(RamContext* MCRef) __attribute__((section(".boot"), noinline));

RamContext* MCCtxGlobal = nullptr;
RamApiWrapper* MCRefGlobal = nullptr;
BiosConfig* MCCfgGlobal = nullptr;

void boot_main(RamContext* MCctx) {
    MCCtxGlobal = MCctx;
    MCRefGlobal = MCctx->api;
    MCCfgGlobal = MCctx->config;

    //================ space for staring services ================

MCRefGlobal->usb->printcln("Loading services...");

    uintptr_t file = MCRefGlobal->sd->open("/config/services.txt", "r");
    
    if (file) {
        size_t size = MCRefGlobal->sd->size(file);
        char* buffer = (char*)MCRefGlobal->base->malloc(size + 1);
        MCRefGlobal->sd->read(file, buffer, size);
        buffer[size] = '\0'; 

        char* line = buffer;
        while (*line) {

            while (*line == '\n' || *line == '\r') line++;
            if (*line == '\0') break;


            char* end = line;
            while (*end && *end != '\n' && *end != '\r') end++;


            if (*end) *end = '\0';

            MCRefGlobal->usb->printcln("Loading: ");
            MCRefGlobal->usb->printcln(line);
            

            uintptr_t binFile = MCRefGlobal->sd->open(line, "r");
            if (binFile) {
                size_t binSize = MCRefGlobal->sd->size(binFile);
                void* binBuf = MCRefGlobal->base->memalign(16, binSize);
                MCRefGlobal->sd->read(binFile, binBuf, binSize);
                MCRefGlobal->sd->close(binFile);


                typedef void (*RamEntryFunc)(RamContext*);
                RamEntryFunc func = (RamEntryFunc)((uintptr_t)binBuf | 1);
                MCRefGlobal->threading->addthreadA((void (*)(void*))func, MCctx, 1024, MCRefGlobal->base->memalign(16, 1024));
            } else {
                MCRefGlobal->usb->printcln("Failed to open service binary.");
            }

            line = end + 1;
        }

        MCRefGlobal->base->free(buffer);
        MCRefGlobal->sd->close(file);
    } else {
        MCRefGlobal->usb->printcln("Failed to open /config/services.txt");
    }
    
    //=============================================================
    //rest of kernel i guess

    while(1){
        MCRefGlobal->base->delay(1000);
    }
}
