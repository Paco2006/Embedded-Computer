// RamApiWrapper.h
#ifndef RAM_API_WRAPPER_H
#define RAM_API_WRAPPER_H

#include <stdint.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

// ------------------------------
// Base functions: timing, IO, memory
// ------------------------------
struct BaseFunc {
    void (*print)(const char*);
    void (*printf)(const char*, ...);
    void (*delay)(unsigned long);
    unsigned long (*millis)(void);
    unsigned long (*micros)(void);

    void (*digitalWrite)(uint8_t, uint8_t);
    uint8_t (*digitalRead)(uint8_t);
    void (*pinMode)(uint8_t, uint8_t);

    void* (*malloc)(size_t);
    void (*free)(void*);
};

// ------------------------------
// USB Serial class wrapper
// ------------------------------
struct USBSerial {
    void (*print)(const char*);
    void (*println)( char*);
    int (*available)();
    int (*read)();
    void (*flush)();
};

// ------------------------------
// SPI Communication wrapper
// ------------------------------
struct SPICom {
    void (*begin)();
    void (*beginTransaction)(void* settings); // Pass pointer to SPISettings if needed
    void (*endTransaction)();
    uint8_t (*transfer)(uint8_t);
};

// ------------------------------
// I2C Communication wrapper
// ------------------------------
struct I2CCom {
    void (*begin)();
    void (*beginTransmission)(uint8_t address);
    void (*write)(uint8_t data);
    void (*endTransmission)(void);
    uint8_t (*requestFrom)(uint8_t address, uint8_t quantity);
    int (*read)();
};

// ------------------------------
// Software Serial wrapper
// ------------------------------
struct SerialMux {
    void (*begin)(int index, unsigned long baud);
    void (*end)(int index);
    int  (*available)(int index);
    int  (*read)(int index);
    size_t (*write)(int index, uint8_t);
    void (*flush)(int index);
};

// ------------------------------
// Master API struct to hold everything
// ------------------------------
struct RamApiWrapper {
    BaseFunc* base;
    USBSerial* usb;
    SPICom* spi;
    I2CCom* i2c;
    SerialMux* serialMux;
};

#ifdef __cplusplus
}
#endif

#endif // RAM_API_WRAPPER_H