#include "Executor.h"
#include <malloc.h> // For memory allocation

/*
States:
 1- Empty: A program is not loaded or running.
 2- Loaded: The program is loaded into memory, but not yet running.
 3- Running: The program is running.

*/


ProgramExecutor::ProgramExecutor(BiosConfig* config, Interfaces* interface ) 
    {
        _biosConfig = config;
        _interfaces = interface;
        currentState = 1;
        programMemory = nullptr;
        programSize = 0;
    }

bool ProgramExecutor::loadProgram(const uint8_t* program, size_t size) {
    if (currentState != 1) {
        return false;
    }
    
    if (!allocateMemory(size)) {
        return false;
    }
    
    memcpy(programMemory, program, size);
    programSize = size;
    currentState = 2;
    Serial.println("Program loaded");
    return true;
}

void ProgramExecutor::execute() {
    if (currentState != 2) {
        return;
    }
    
    currentState = 3;
    
    // Function pointer to the loaded program
    void (*program)() = (void (*)())((uintptr_t)programMemory );
    Serial.printf("ProgMem: 0x%08X\n", (unsigned int)programMemory);
    Serial.printf("Jumping to address: 0x%08X\n", (unsigned int)program);

    uint32_t ptr = (unsigned int)program;

    for(uint32_t i = ptr ;i<ptr + programSize; i++){
        uint8_t b = *((uint8_t*)i);
        Serial.printf("0x%02X ", i);
        Serial.print(": ");
        Serial.printf("%02X ", b);
    }

    program();
    /*
    volatile uint32_t* a   = (uint32_t*)0x4200C000;
    volatile uint32_t* b   = (uint32_t*)0x4200C004;                                      

    *a   |= (1<< 6);
    *b   |= (1<< 6);
    */
    // Program finished or returned
    currentState = 1;
}

bool ProgramExecutor::isEmpty() {
    if (currentState == 1) {
        return true;
    }
    return false;
}

bool ProgramExecutor::isLoaded() {
    if (currentState == 2) {
        return true;
    }
    return false;
}

bool ProgramExecutor::isRunning() {
    if (currentState == 3) {
        return true;
    }
    return false;
}

void ProgramExecutor::stop() {
    if (currentState == 3) {
        // In a real system, you'd need to properly unwind the stack, etc.
        currentState = 2;
    }
}

bool ProgramExecutor::allocateMemory(size_t size) {
    freeMemory();

    programMemory = (uint8_t*)memalign(16, size);
    return programMemory != nullptr;
}

void ProgramExecutor::freeMemory() {
    if (programMemory) {
        free(programMemory);
        programMemory = nullptr;
    }
    programSize = 0;
}