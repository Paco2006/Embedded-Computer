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

    const int   adcPin   = 21;
    const int   maxAdc   = 1023;
    const uint32_t periodMs = 20; 

    while(1){
        int v = MCRefGlobal->base->analogRead(21);
        if (v < 0)       v = 0;
        else if (v>maxAdc) v = maxAdc;

        // compute on/off durations
        uint32_t onTime  = (uint32_t)v * periodMs / maxAdc;
        uint32_t offTime = periodMs - onTime;


        MCRefGlobal->base->digitalWrite(4, 1);
        MCRefGlobal->base->delay(onTime);
        MCRefGlobal->base->digitalWrite(4, 0);
        MCRefGlobal->base->delay(offTime);
    }
}

