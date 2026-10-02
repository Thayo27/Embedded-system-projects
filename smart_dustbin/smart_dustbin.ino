#include <Arduino.h>
#include <Servo.h>

//ultrasonic sensor pins
#define TRIG_PIN 7
#define ECHO_PIN 6

// servo motor pins
#define SERVO_PIN 9

// object detection distance
#define DETECTION_DISTANCE 10

// create the servo object
Servo dustbinServo;

// variables to use
long duration;
float distance;

void setup() {
  // put your setup code here, to run once:
  // configure the pins

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  dustbinServo.attach(SERVO_PIN);

  dustbinServo.write(0); // initially the lid of bin is closed

}

void loop() {
  // put your main code here, to run repeatedly:
  // send the ultrasonic pulse to the microcontroller
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG_PIN, LOW);

  // read echo duration
  duration = pulseIn(ECHO_PIN, HIGH, 30000);

  // calculate the distance in centimeters

  if(duration == 0) {
    distance = -1;
  } else {
    distance = duration * 0.0343 / 2;
  }

  // check if an object is detected

  if(distance > 0 && distance <= DETECTION_DISTANCE) {
    // open the lid
    dustbinServo.write(90);

    // keep the lid open
    delay(3000);

    // close the lid
    dustbinServo.write(0);

    // allow lid to close
    delay(1000);
  }
  delay(200);

}
