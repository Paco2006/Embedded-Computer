#include <Arduino.h>
#include "Bios.h"
#include "Executor.h"
#include "RamApiWrapper.h"
#include "RamApiHostWrapper.h"
#include "Structures.h"

Interfaces interfaces;
BiosConfig biosConfig;

RamContext ctx = {
    .api = &GlobalRamApi,
    .config = &biosConfig,
    .iface = &interfaces
};
    
ProgramExecutor programExecutor;
Bios bios(&programExecutor, &biosConfig, &interfaces);

void setup() {
    bios.startup();
    Serial.println("bios done");
    initRamHostApi(&interfaces); // Use your already existing global struct
    Serial.println("ram done");
    programExecutor.setRamContext(&ctx);
    programExecutor.execute();


    Serial.println("Booted up");
}

void loop() {

    delay(1000); // 1 second delay
}