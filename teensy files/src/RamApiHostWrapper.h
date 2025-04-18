// RamHostWrapper.h
#ifndef RAM_HOST_WRAPPER_H
#define RAM_HOST_WRAPPER_H

#include "RamApiWrapper.h"
#include "Structures.h"
#include "RamContext.h"
#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <stdlib.h>





// --- Global instance ---
extern RamApiWrapper GlobalRamApi;

void initRamHostApi(Interfaces* iface);

#endif // RAM_HOST_WRAPPER_H

