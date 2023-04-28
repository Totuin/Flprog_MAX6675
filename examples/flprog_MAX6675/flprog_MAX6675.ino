#include "flprog_MAX6675.h"

FLProgSPI spiBus(0);
FLProgMAX6675 chip(&spiBus, 10);

void setup()
{
  Serial.begin(9600);
  Serial.println("****MAX6675 thermocouple library by E. Kremer****");
  Serial.println();
  spiBus.begin();
   chip.begin();
}

void loop()
{
  chip.readTemp();
  float celsius = chip.getTempC();
  float fahrenheit = chip.getTempF();
  Serial.print("T in С = ");
  Serial.print(celsius);
  Serial.print(". T in Fahrenheit = ");
  Serial.println(fahrenheit);
  delay(1000);
}