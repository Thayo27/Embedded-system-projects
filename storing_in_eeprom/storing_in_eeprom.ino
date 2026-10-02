#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  EEPROM.write(0, 199);

  Serial.println("Value written to EEPROM");

}

void loop() {
  // put your main code here, to run repeatedly:

}
