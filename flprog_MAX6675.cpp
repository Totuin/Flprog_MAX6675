#include "flprog_MAX6675.h"

FLProgMAX6675::FLProgMAX6675(AbstractFLProgSPI *device, uint16_t pinCS)
{
    spi = device;
    pin = pinCS;
}

void FLProgMAX6675::begin()
{
    pinMode(pin, OUTPUT);
}

float FLProgMAX6675::getTempF()
{
    return temp * 9.0 / 5.0 + 32;
}

void FLProgMAX6675::readTemp()
{
    if (!isReady())
    {
        return;
    }
    spi->beginTransaction(FLPROG_MAX6675_SETTINGS);
    digitalWrite(pin, false);
    incomingMessage = spi->transfer16(0x00);
    digitalWrite(pin, true);
    spi->endTransaction();
    if (incomingMessage & FLPROG_MAX6675_THERMOCOUPLE_OPEN_BIT)
    {
        temp = FLPROG_MAX6675_THERMOCOUPLE_OPEN;
        return;
    }
    temp = (incomingMessage >> 3) * FLPROG_MAX6675_CONVERSION_RATIO;
}

bool FLProgMAX6675::isReady()
{
    if (spi == 0)
    {
        return false;
    }
    return spi->isReady();
}