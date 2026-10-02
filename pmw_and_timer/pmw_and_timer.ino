// program to test on the PWM and timers
// variables to store LED pin
const int ledPin = 9;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

  // for loop to increase the brightness of the LED
  for (int brightness = 0; brightness <= 255; brightness++) {
    analogWrite(ledPin, brightness);
    delay(10);
  }
  // for loop to reduce the brightness of the LED
  for(int brightness = 255; brightness >=0; brightness--) {
    analogWrite(ledPin, brightness);
    delay(10);
  }

}
