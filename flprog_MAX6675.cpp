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

double FLProgMAX6675::getTempF()
{
    return temp * 9.0 / 5.0 + 32;
}

void FLProgMAX6675::readTemp()
{
    if (!isReady())
    {
        return;
    }
#ifdef FLPROG_CORE_STM
    spi->setDataMode(SPI_MODE1);
    spi->setBitOrder(MSBFIRST);
    spi->setClockDivider(SPI_CLOCK_DIV32);
#else
    spi->beginTransaction(FLPROG_MAX6675_SETTINGS);
#endif
    digitalWrite(pin, false);
    incomingMessage = spi->transfer16(0);
    digitalWrite(pin, true);
#ifndef FLPROG_CORE_STM
    spi->endTransaction();
#endif
    if (incomingMessage & FLPROG_MAX6675_THERMOCOUPLE_OPEN_BIT)
    {
        temp = FLPROG_MAX6675_THERMOCOUPLE_OPEN;
        return;
    }
    temp = (incomingMessage >> 3) * FLPROG_MAX6675_CONVERSION_RATIO;
}

bool FLProgMAX6675::isReady()
{
    return true;
    if (spi == 0)
    {
        return false;
    }
    return spi->isReady();
}

void FLProgMAX6675::pool()
{
    checkReadPeriod();
}

void FLProgMAX6675::checkReadPeriod()
{
    if (readPeriod > 0)
    {
        if (flprog::isTimer(startReadPeriod, readPeriod))
        {
            startReadPeriod = millis();
            readTemp();
        }
    }
}

void FLProgMAX6675::setReadPeriod(uint32_t period)
{
    if (period < FLPROG_MAX6675_READ_PERIOD)
    {
        period = FLPROG_MAX6675_READ_PERIOD;
    }
    else
    {
        readPeriod = period;
    }
}