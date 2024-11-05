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
#define F(a)  a
#define sscanf scanf

#define HEX 1
#define byte uint8_t

// Pretty much all of these functions aren't really needed
// unless we want UART support
class Stream {
public:
    virtual void print(const char* s);
    virtual void print(uint32_t num) {
        println("Unimp");
    }
    virtual void print(uint32_t ui, uint8_t format) {
        print("Unimp");
    }
    virtual void print() {
        // Do nothing
    }

    virtual void println() {
        println("\n");
    }
    virtual void println(uint16_t ui) {
        println("Unimp"); // TODO
    }

    virtual void println(const char* s);
    virtual void println(const uint8_t thing, uint8_t format) {
        println("Unimp"); // TODO
    }

    virtual int write(uint8_t *data, size_t len);
    virtual int write(uint8_t singleByte) {
        return write(&singleByte, 1);
    }

    virtual bool available();
    virtual int read();
};

class TwoWire {
public:
    virtual void beginTransmission(uint8_t address) {

    }
    
    virtual int endTransmission() {

    }

    virtual int endTransmission(bool stopOrRestart) {

    }
    
    virtual int write(uint8_t *bytes, size_t len) {
    }

    virtual int write(uint8_t byte) {
        return write(&byte, 1);
    }

    virtual int requestFrom(uint8_t address, uint8_t bytesToRead) {
    }

    virtual char read() {
    }
};

class SPIClass {
};

class PicoI2C : public TwoWire {
public:
    virtual void beginTransmission(uint8_t address) override;
    virtual int endTransmission() override;
    virtual int endTransmission(bool stopOrRestart) override;
    virtual int write(uint8_t *bytes, size_t len) override;
    virtual int requestFrom(uint8_t address, uint8_t bytesToRead) override;

    virtual char read() override;
private:
    static const size_t MAX_BUFFER_SIZE = 256;
    uint8_t currentAddress;
    uint8_t buffer[MAX_BUFFER_SIZE];
    size_t bufferPos = 0;
    size_t currentBufferSize = 0;
};

class PicoSPI : SPIClass {
};

class PicoUART : Stream{
};

#define OUTPUT 1
#define INPUT 0
#define HIGH 1
#define LOW 0

void pinMode(uint8_t pin, uint8_t mode);
void digitalWrite(uint8_t pin, uint8_t state); 
unsigned long millis(void);
void delay(uint32_t time); 

#endif // ARDUINO_TO_PICO_HPP
