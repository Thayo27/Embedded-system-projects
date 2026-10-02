#include <Arduino.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// pin configuration
const int PIR_PIN = 2;
const int LED_PIN = 8;
const int BUZZER_PIN = 9;


// LCD Configuration
LiquidCrystal_I2C lcd(0x27, 16, 2);

//setup
void setup() {
  //configure pins
  pinMode(PIR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  //let both the buzzer and bulb be off when the system boots
  digitalWrite(LED_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN,LOW);

  //start the display screen
  lcd.init();
  lcd.backlight();

  //clear the screen
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Security System");

  lcd.setCursor(0, 1);
  lcd.print("Initializing");

  delay(2000);

  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("SYSTEM READY");

  lcd.setCursor(0, 1);
  lcd.print("AREA SECURE");

  delay(1500);
}

// main program
void loop() {
  //read the motion sensor
  int motion = digitalRead(PIR_PIN);

  // set condition to check what is to be done
  if (motion == HIGH) {
    // activate light
    digitalWrite(LED_PIN, HIGH);
    // activate buzzer
    digitalWrite(BUZZER_PIN, HIGH);

    //lcd alert
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("!!! WARNING !!!");

    lcd.setCursor(0, 1);
    lcd.print("MOTION DETECTED");
  }
  // else no motion
  else {
    // deactivate the alarm
    digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);

    // lcd status
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("SECURITY STATUS");

    lcd.setCursor(0, 1);
    lcd.print("AREA SECURE");

  }
  // delay for a second
  delay(1000);
}

