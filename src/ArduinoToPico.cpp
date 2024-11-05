#include "ArduinoToPico.hpp"

#include "pico/stdlib.h"
#include "pico/time.h"
#include "hardware/i2c.h"

static const int I2C_TIMEOUT = 10000;

void PicoI2C::beginTransmission(uint8_t address) {
   this->currentAddress = address; 
}

int PicoI2C::endTransmission() {
    // No action needed
    return 0;
}
int PicoI2C::endTransmission(bool stopOrRestart) {
    // No action needed
    // TODO: Find a way to take the stopOrRestart parameter into account
    return 0;
}

int PicoI2C::write(uint8_t *bytes, size_t len) {
    return i2c_write_blocking(i2c_default, this->currentAddress, bytes, len, false);
}

int PicoI2C::requestFrom(uint8_t address, uint8_t bytesToRead) {
    this->currentBufferSize = i2c_read_timeout_us(i2c_default, address, this->buffer, bytesToRead, false, I2C_TIMEOUT);
    return this->currentBufferSize;
}

char PicoI2C::read() {
    char val;

    if (this->bufferPos > this->currentBufferSize) {
        val = 0;    
    } else {
        val = this->buffer[this->bufferPos];
        bufferPos++;
    }

    return val;
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
