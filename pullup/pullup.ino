// create the variables
const int buttonPin = 2;
const int ledPin = 8;

void setup() {
  // put your setup code here, to run once:
  //CONFIGURE THE PINS 
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  int buttonState = digitalRead(buttonPin);

  if(buttonState == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

}
