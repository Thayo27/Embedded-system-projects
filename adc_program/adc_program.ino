// program to demonstrate ADC 
 const int sensorPin = A0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  int value = analogRead(sensorPin);

  Serial.println(value);

  delay(1000);

}
