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

    while(1){
        int i = MCRefGlobal->base->digitalRead(7);
        if(i == 1){
            MCRefGlobal->usb->printcln("pressed!");
        }
        MCRefGlobal->base->delay(100);
    }
}
