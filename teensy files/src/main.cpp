

#include <Arduino.h>
#include "Bios.h"
#include "Executor.h"
#include "Structures.h"
#include "imxrt.h"

Interfaces interfaces;
BiosConfig biosConfig;

ProgramExecutor programExecutor(&biosConfig, &interfaces);
Bios bios(&programExecutor, &biosConfig, &interfaces);



void setup() {
    bios.startup();
    Serial.println((uint32_t)&GPIO4_DR, HEX);
    programExecutor.execute();
    Serial.println("Booted up");
}

void loop() {
    unsigned long currentMillis = millis();

    if(Serial.available()){
        char c = Serial.read();
        if(c == '1'){
        }
        if(c == '2'){
            
        }
        
        if(c == '9'){
            Serial.println("IM TEENSY");
        }
    }
    
    
}