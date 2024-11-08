#include "ArduinoToPico.hpp"

#include "pico/stdlib.h"
#include "pico/stdio.h"
#include "pico/time.h"
#include "hardware/i2c.h"

static const int I2C_TIMEOUT = 10000;

void PicoTwoWire::beginTransmission(uint8_t address) {
   this->currentAddress = address; 
}

int PicoTwoWire::endTransmission(bool stopOrRestart) {
    int bytesWritten = i2c_write_blocking(i2c_default, this->currentAddress, this->txBuffer, this->txBufferPos, !stopOrRestart);

    this->txBufferPos = 0;
    return 0; // TODO: Supposed to return if target ACK'd or not
}

int PicoTwoWire::write(uint8_t *bytes, size_t len) {
    if (len + this->txBufferPos > MAX_BUFFER_SIZE) {
        return 0;
    } else {
        memcpy(this->txBuffer + this->txBufferPos, bytes, len);
        this->txBufferPos += len;

        return len;
    }
}

int PicoTwoWire::requestFrom(uint8_t address, uint8_t bytesToRead) {
    this->rxBufferSize = i2c_read_timeout_us(i2c_default, address, this->rxBuffer, bytesToRead, false, I2C_TIMEOUT);
    this->rxBufferPos = 0;

    return this->rxBufferSize;
}

char PicoTwoWire::read() {
    char val;

    if (this->rxBufferPos > this->rxBufferSize) {
        val = 0;    
    } else {
        val = this->rxBuffer[this->rxBufferPos];
        this->rxBufferPos++;
    }

    return val;
}

void PicoPrintfStream::print(const char* s) {
    printf("%s", s);
}

void PicoPrintfStream::print(uint32_t num) {
    printf("%i", num);
}

void PicoPrintfStream::print(uint32_t ui, uint8_t format) {
    printf("%X", ui);
}

void PicoPrintfStream::print(void) {
    printf(" ");
}

void PicoPrintfStream::println(uint16_t ui) {
    printf("%i\n", ui);
}
void PicoPrintfStream::println(const char* s) {
    printf("%s\n", s);
}

void PicoPrintfStream::println(const uint8_t thing, uint8_t format) {
    printf("%X\n", thing);
}

bool PicoPrintfStream::available() {
    // Write only stream
    return false;
}

int PicoPrintfStream::read() {
    // Write only stream
    return 0;
}

void pinMode(uint8_t pin, uint8_t mode) {
    // Unimplemented, don't need debug pin
}

void digitalWrite(uint8_t pin, uint8_t state) {
    // Unimplemented, don't need debug pin
    //gpio_put(pin, state);
}

unsigned long millis(void) {
    absolute_time_t current = get_absolute_time();
    return to_ms_since_boot(current);
}

void delay(uint32_t time) {
    sleep_ms(time);
}
