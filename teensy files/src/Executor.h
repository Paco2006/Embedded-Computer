#ifndef EXECUTOR_H
#define EXECUTOR_H

#include <Arduino.h>
#include "Structures.h"

class ProgramExecutor {
public:
    ProgramExecutor(BiosConfig* config = nullptr, Interfaces* interface = nullptr);
    

    bool loadProgram(const uint8_t* program, size_t size);
    void execute();
    bool isEmpty();
    bool isLoaded();
    bool isRunning();


    void stop();

private:
    
    
    uint8_t currentState;
    uint8_t* programMemory;
    size_t programSize;
    
    // Memory management
    bool allocateMemory(size_t size);
    void freeMemory();
    
    BiosConfig* _biosConfig;
    Interfaces* _interfaces;
};

#endif