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
    double getTempC() { return temp; };
    double getTempF();
    void readTemp();
    void setReadPeriod(uint32_t period);
    void pool();

private:
    bool isReady();
    void checkReadPeriod();
    AbstractFLProgSPI *spi;
    uint16_t pin;
    double temp = 0;
    uint16_t incomingMessage;
    uint32_t readPeriod = 0;
    uint32_t startReadPeriod = 0;
};
