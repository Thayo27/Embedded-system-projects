//program to communicate info using LED
// create the variable
const int ledPin = 13;

void setup() {
  // put your setup code here, to run once:
  //CONFIGURE THE PIN TO BE AN OUTPUT PIN
  pinMode(ledPin, OUTPUT);
}
//create a function
//function to print dots
void dot() {
  digitalWrite(ledPin, HIGH);
  delay(200);
  digitalWrite(ledPin, LOW);
  delay(200);
}
//function to print dashes
void dash() {
  digitalWrite(ledPin, HIGH);
  delay(600);
  digitalWrite(ledPin, LOW);
  delay(600);
}
void loop() {
  // put your main code here, to run repeatedly:
  // print s
  dot();
  dot();
  dot();
  delay(400);

  //print o
  dash();
  dash();
  dash();
  delay(400);

  // print s
  dot();
  dot();
  dot();
  delay(2000);
}
