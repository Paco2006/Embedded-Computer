// boot.cpp
#include <stdint.h>
#include "RamApiWrapper.h"


extern "C" void boot_main(RamApiWrapper* MCRef) __attribute__((section(".boot"), noinline));

void boot_main(RamApiWrapper* MCRef) {
    MCRef->usb->print("Hello from Bootloader!\n");
    
}


