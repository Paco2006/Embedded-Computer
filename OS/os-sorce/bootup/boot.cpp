// boot.cpp
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

    //================ space for configuring the system if needed ================









    //============================================================================
    //loading the kernel
    MCRefGlobal->usb->printcln("Trying SD...\n");
    if (MCRefGlobal->sd->begin(MCCfgGlobal->SDCardCS)) {
        MCRefGlobal->usb->printcln("SD ready");
        uintptr_t file = 0;
        int size = 0;
        file = MCRefGlobal->sd->open("/system/kernel.bin", "r");
        size = MCRefGlobal->sd->size(file);
        MCRefGlobal->usb->printintln(size);
        void* buffer = MCRefGlobal->base->memalign(16, size);
        MCRefGlobal->sd->read(file, buffer, size);
        MCRefGlobal->sd->close(file);
        MCRefGlobal->usb->printcln("Kernel loaded");
        
        typedef void (*BootFunc)(RamContext*);
        BootFunc boot = (BootFunc)((uintptr_t)buffer | 1);
        boot(MCCtxGlobal);

        
    } else {
        MCRefGlobal->usb->printcln("SD init failed");
    }
    
}

