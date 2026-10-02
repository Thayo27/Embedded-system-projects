// create a variable to store the pin
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  // CONFIGURE THE PIN TO BE THE OUTPUT PIN
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  //short flashes
  for(int i = 0; i < 10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
  }

  //long flashes
  digitalWrite(ledPin, HIGH);

  // set the bulb to turn off for two seconds before turning on
  delay(2000);
  digitalWrite(ledPin, LOW);
  delay(2000);

   //short flashes
  for(int i = 0; i < 10; i++) {
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
    delay(50);
  }
  delay(2000);

}
