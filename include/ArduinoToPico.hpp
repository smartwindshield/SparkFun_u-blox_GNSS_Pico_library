/**
 * Contains definitions from the Arduino API that are used by the u-blox library.
 *
 * These are then implemented using the Raspberry Pi pico SDK
 */
#ifndef ARDUINO_TO_PICO_HPP
#define ARDUINO_TO_PICO_HPP

#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

#include <cstring>

#define memcpy __builtin_memcpy
#define memcmp __builtin_memcmp
/*
 * Used for printing strings from flash memory on Arduino.
 * Not needed on Pi Pico so this macro makes it irrelevant
 */
#define F(a)  a
#define sscanf scanf

#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0

#define HEX 1

typedef uint8_t byte;

/**
 * Represents Arduino's "Stream" class. Only includes the functions 
 * that are used by the SparkFun library.
 *
 * @see PicoPrintfStream for an implementation of this using "printf"
 */
class Stream {
public:
    virtual void print(const char* s) = 0;
    virtual void print(uint32_t num) = 0;
    virtual void print(uint32_t ui, uint8_t format) = 0;
    virtual void print(void) = 0;

    virtual void println() {
        println("\n");
    }

    virtual void println(uint16_t ui) = 0;
    virtual void println(const char* s) = 0;
    virtual void println(const uint8_t thing, uint8_t format) = 0;

    virtual int write(uint8_t *data, size_t len) = 0;
    virtual int write(uint8_t singleByte) {
        return write(&singleByte, 1);
    }

    virtual bool available() = 0;
    virtual int read() = 0;
};

/**
 * Represents Arduino's "TwoWire" class for I2C communication.
 * Only includes methods that are used by the SparkFun library
 */
class TwoWire {
public:
    virtual void beginTransmission(uint8_t address) = 0;
    
    /**
     * @param stopOrRestart If false then a RESTART condition is issued, otherwise STOP is sent
     */
    virtual int endTransmission(bool stopOrRestart) = 0;
    
    virtual int endTransmission(void) {
        return endTransmission(true); // Release the bus by default
    }
    
    virtual int write(uint8_t *bytes, size_t len) = 0;

    virtual int write(uint8_t byte) {
        return write(&byte, 1);
    }

    virtual int requestFrom(uint8_t address, uint8_t bytesToRead) = 0;
    virtual char read(void) = 0;
};

#if UBLOX_PICO_ENABLE_SPI
#error "Ublox Library Pico Port: SPI not implemented yet."

/**
 * Represents Arduino's "SPIClass" used for SPI communication.
 * Currently not implemented.
 */
class SPIClass {
};
#endif

/**
 * Implementation of Arduino's TwoWire I2C communication class
 * using the Raspberry Pi Pico SDK.
 *
 * It will use the default i2c device.
 */
class PicoTwoWire : public TwoWire {
public:
    virtual void beginTransmission(uint8_t address) override;
    virtual int endTransmission(bool stopOrRestart) override;
    virtual int write(uint8_t *bytes, size_t len) override;
    virtual int requestFrom(uint8_t address, uint8_t bytesToRead) override;

    virtual char read() override;
private:
    static const size_t MAX_BUFFER_SIZE = 256;
    uint8_t currentAddress;

    uint8_t txBuffer[MAX_BUFFER_SIZE];
    uint8_t rxBuffer[MAX_BUFFER_SIZE];

    size_t rxBufferPos = 0;
    size_t rxBufferSize = 0;
    size_t txBufferPos = 0;
};

class PicoPrintfStream : public Stream {
public:
    virtual void print(const char* s) override;
    virtual void print(uint32_t num) override;
    virtual void print(uint32_t ui, uint8_t format) override;
    virtual void print(void) override;

    virtual void println(uint16_t ui) override;
    virtual void println(const char* s) override;
    virtual void println(const uint8_t thing, uint8_t format) override;

    virtual int write(uint8_t *data, size_t len) override;

    virtual bool available() override;
    virtual int read() override;
};

/*
 * Various standalone Arduino functions that need to be implemented using
 * Raspberry Pi Pico SDK functions.
 */

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t state); 
unsigned long millis(void);
void delay(uint32_t time); 

#endif // ARDUINO_TO_PICO_HPP
