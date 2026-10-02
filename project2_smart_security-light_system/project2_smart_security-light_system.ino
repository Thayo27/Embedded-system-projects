#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//pins used
const int PIR = 2;
const int LDR = A0;
const int LED_PIN = 8;

// settings 
const int DARK_THRESHOLD = 500;
const int DIM_BRIGHTNESS = 50;
const int BRIGHT_BRIGHTNESS = 255;

//LCD I2C Address
LiquidCrystal_I2C lcd(0x27, 16,2);

void setup() {
  // put your setup code here, to run once:

  // CONFIGURE PINS
  pinMode(PIR, INPUT);
  pinMode(LED_PIN, OUTPUT);

  // Turn on the LCD
  lcd.init();
  lcd.backlight();
  
  // messages to be printed on the LCD
  lcd.setCursor(0, 0);
  lcd.print("SMART HOME");
  lcd.setCursor(0, 1);
  lcd.print("stating...");
  delay(2000);
  lcd.clear();

}

void loop() {
  // put your main code here, to run repeatedly:

  //read sensors data
  int LightLevel = analogRead(LDR);
  int motion = digitalRead(PIR);

  // determine whether it is dark
  bool dark = LightLevel <DARK_THRESHOLD;

  // lighting logic
  if(dark && motion == HIGH) {
    analogWrite(LED_PIN, BRIGHT_BRIGHTNESS);
  } else if(dark && motion == LOW) {
    analogWrite(LED_PIN, DIM_BRIGHTNESS);
  } else {
    analogWrite(LED_PIN, 0);
  }

  // lcd
  lcd.setCursor(0, 0);
  lcd.print("Light: ");
  lcd.print(LightLevel);
  lcd.print(" ");

  lcd.setCursor(0, 1);

  if(!dark) {
    lcd.print("LIGHT: OFF");
  } else if (motion == HIGH) {
    lcd.print("LIGHT: BRIGHT");
  } else {
    lcd.print("LIGHT: DIM");
  }

  //DELAY
  delay(300);
  

}
