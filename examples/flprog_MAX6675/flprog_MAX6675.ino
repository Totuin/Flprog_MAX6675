#include "flprog_MAX6675.h"

FLProgSPI spiBus(0);
FLProgMAX6675 chip(&spiBus, PA4);
float celsius;
uint32_t startTime = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("****MAX6675 thermocouple library****");
  Serial.println();
  spiBus.begin();
  chip.setReadPeriod(500);
  chip.begin();
}

void loop()
{
  chip.pool();

  if (flprog::isTimer(startTime, 1000)) {
    celsius = chip.getTempC();
    Serial.print("T in С = ");
    Serial.print(celsius);
    Serial.print(". T in Fahrenheit = ");
    Serial.println(chip.getTempF());
    startTime = millis();
  }

}