#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  int value = EEPROM.read(0);

  Serial.print("Stored value = ");
  Serial.println(value);

}

void loop() {
  // put your main code here, to run repeatedly:

}
