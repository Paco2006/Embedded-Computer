#include "RamApiHostWrapper.h"
// Static instances of structs
static BaseFunc baseFuncs;
static USBSerial usbFuncs;
static SPICom spiFuncs;
static I2CCom i2cFuncs;
static SerialMux serialMuxFuncs;

static Interfaces* interfacesRef = nullptr;

RamApiWrapper GlobalRamApi;
// --- BaseFunc ---
void basePrint(const char* msg) { Serial.println(msg); }

void basePrintf(const char* fmt, ...) {
    char buf[128];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    Serial.println(buf);
}

void baseDelay(unsigned long ms) { delay(ms); }
unsigned long baseMillis() { return millis(); }
unsigned long baseMicros() { return micros(); }
void baseDigitalWrite(uint8_t pin, uint8_t val) { digitalWrite(pin, val); }
uint8_t baseDigitalRead(uint8_t pin) { return digitalRead(pin); }
void basePinMode(uint8_t pin, uint8_t mode) { pinMode(pin, mode); }
void* baseMalloc(size_t size) { return malloc(size); }
void baseFree(void* ptr) { free(ptr); }

// --- USBSerial ---
void usbPrint(const char* msg) { Serial.print(msg); }
void usbPrintln( char* msg) { Serial.println(msg); }
int usbAvailable() { return Serial.available(); }
int usbRead() { return Serial.read(); }
void usbFlush() { Serial.flush(); }

// --- SPI ---
void spiBegin() { SPI.begin(); }
void spiBeginTransaction(void* settings) {
    SPI.beginTransaction(*reinterpret_cast<SPISettings*>(settings));
}
void spiEndTransaction() { SPI.endTransaction(); }
uint8_t spiTransfer(uint8_t b) { return SPI.transfer(b); }

// --- I2C ---
void i2cBegin() { Wire.begin(); }
void i2cBeginTransmission(uint8_t addr) { Wire.beginTransmission(addr); }
void i2cWrite(uint8_t data) { Wire.write(data); }
void i2cEndTransmission() { Wire.endTransmission(); }
uint8_t i2cRequestFrom(uint8_t addr, uint8_t qty) { return Wire.requestFrom(addr, qty); }
int i2cRead() { return Wire.read(); }

// --- SoftwareSerial Mux ---
void muxBegin(int idx, unsigned long baud) {
    if (!interfacesRef || idx < 0 || idx >= 10 || !interfacesRef->softwareSerial[idx]) return;
    interfacesRef->softwareSerial[idx]->begin(baud);
}

void muxEnd(int idx) {
    if (!interfacesRef || idx < 0 || idx >= 10 || !interfacesRef->softwareSerial[idx]) return;
    interfacesRef->softwareSerial[idx]->end();
}

int muxAvailable(int idx) {
    if (!interfacesRef || idx < 0 || idx >= 10 || !interfacesRef->softwareSerial[idx]) return false;
    return interfacesRef->softwareSerial[idx]->available();
}


int muxRead(int idx) {
    if (!interfacesRef || idx < 0 || idx >= 10 || !interfacesRef->softwareSerial[idx]) return -1;
    return interfacesRef->softwareSerial[idx]->read();
}


size_t muxWrite(int idx, uint8_t val) {
    if (!interfacesRef || idx < 0 || idx >= 10 || !interfacesRef->softwareSerial[idx]) return 0;
    return interfacesRef->softwareSerial[idx]->write(val);
}

void muxFlush(int idx) {
    if (!interfacesRef || idx < 0 || idx >= 10 || !interfacesRef->softwareSerial[idx]) return;
    interfacesRef->softwareSerial[idx]->flush();
}


void initRamHostApi(Interfaces* iface) {
    interfacesRef = iface;

    baseFuncs.print         = basePrint;
    baseFuncs.printf        = basePrintf;
    baseFuncs.delay         = baseDelay;
    baseFuncs.millis        = baseMillis;
    baseFuncs.micros        = baseMicros;
    baseFuncs.digitalWrite  = baseDigitalWrite;
    baseFuncs.digitalRead   = baseDigitalRead;
    baseFuncs.pinMode       = basePinMode;
    baseFuncs.malloc        = baseMalloc;
    baseFuncs.free          = baseFree;

    usbFuncs.print          = usbPrint;
    usbFuncs.println        = usbPrintln;
    usbFuncs.available      = usbAvailable;
    usbFuncs.read           = usbRead;
    usbFuncs.flush          = usbFlush;

    spiFuncs.begin              = spiBegin;
    spiFuncs.beginTransaction  = spiBeginTransaction;
    spiFuncs.endTransaction    = spiEndTransaction;
    spiFuncs.transfer          = spiTransfer;

    i2cFuncs.begin             = i2cBegin;
    i2cFuncs.beginTransmission= i2cBeginTransmission;
    i2cFuncs.write            = i2cWrite;
    i2cFuncs.endTransmission  = i2cEndTransmission;
    i2cFuncs.requestFrom      = i2cRequestFrom;
    i2cFuncs.read             = i2cRead;

    serialMuxFuncs.begin      = muxBegin;
    serialMuxFuncs.end        = muxEnd;
    serialMuxFuncs.available  = muxAvailable;
    serialMuxFuncs.read       = muxRead;
    serialMuxFuncs.write      = muxWrite;
    serialMuxFuncs.flush      = muxFlush;

    GlobalRamApi.base = &baseFuncs;
    GlobalRamApi.usb  = &usbFuncs;
    GlobalRamApi.spi  = &spiFuncs;
    GlobalRamApi.i2c  = &i2cFuncs;
    GlobalRamApi.serialMux  = &serialMuxFuncs;
}