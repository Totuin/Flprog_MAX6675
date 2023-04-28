#pragma once
#include "Arduino.h"
#include "flprogUtilites.h"
#include "flprogSPI.h"

#define FLPROG_MAX6675_SETTINGS (SPISettings(1000000, FLPROG_MSBFIRST, FLPROG_SPI_MODE2))
#define FLPROG_MAX6675_THERMOCOUPLE_OPEN_BIT 0x04
#define FLPROG_MAX6675_THERMOCOUPLE_OPEN -1.0
#define FLPROG_MAX6675_READ_PERIOD 250
#define FLPROG_MAX6675_CONVERSION_RATIO 0.25

class FLProgMAX6675
{
public:
    FLProgMAX6675(AbstractFLProgSPI *device, uint16_t pinCS);
    void begin();
    float getTempC() { return temp; };
    float getTempF();
    void readTemp();

private:
    bool isReady();
    AbstractFLProgSPI *spi;
    uint16_t pin;
    float temp = 0;
    uint16_t incomingMessage;
};
