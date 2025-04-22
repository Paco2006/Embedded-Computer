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
        MCRefGlobal->usb->printcln("Hello output");
        MCRefGlobal->base->delay(5000);
    }
}
