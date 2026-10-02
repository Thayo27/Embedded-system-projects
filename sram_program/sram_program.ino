// program to show the size of the SRAM of the microController ATMEGA 2560
// variable to store temporary working data
int counter = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  // increase the value of counter
  counter++;

  Serial.print("counter = ");
  Serial.println(counter);

  delay(1000);

}
