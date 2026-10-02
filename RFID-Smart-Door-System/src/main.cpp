#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// ================= PIN CONFIGURATION =================
#define SS_PIN       53
#define RST_PIN      5

#define SERVO_PIN    9
#define BUZZER_PIN   8

// ================= RFID =================
MFRC522 rfid(SS_PIN, RST_PIN);

// ================= SERVO =================
Servo servoMotor;

const int SERVO_OPEN_ANGLE   = 90;
const int SERVO_CLOSED_ANGLE = 0;

// ================= DOOR =================
const unsigned long DOOR_OPEN_DURATION = 5000;

unsigned long unlockTime = 0;
bool doorIsOpen = false;

// ================= AUTHORIZED UIDs =================
// REPLACE THESE WITH YOUR REAL CARD UIDs

byte authorizedUID1[] = {0x17, 0x61, 0x95, 0x31};
byte authorizedUID2[] = {0x46, 0x2B, 0xD1, 0x3E};


// ================= FUNCTION PROTOTYPES =================
void accessGrantedSound();
void accessDeniedSound();
bool isAuthorized();
bool compareUID(byte *uid1, byte size1, byte *uid2, byte size2);
void openDoor();
void lockDoor();

// ================= SETUP =================
void setup() {

  Serial.begin(9600);

  // Buzzer
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);

  // Servo
  servoMotor.attach(SERVO_PIN);

  // Start in locked position
  servoMotor.write(SERVO_CLOSED_ANGLE);
  delay(500);

  // RFID
  SPI.begin();
  rfid.PCD_Init();

  delay(100);

  Serial.println("==============================");
  Serial.println(" RFID SMART DOOR SYSTEM");
  Serial.println("==============================");
  Serial.println("System ready...");
  Serial.println("Scan RFID card...");
}

// ================= MAIN LOOP =================
void loop() {

  // Automatically lock after 5 seconds
  if (doorIsOpen &&
      millis() - unlockTime >= DOOR_OPEN_DURATION) {

    lockDoor();
  }

  // Check for RFID card
  if (!rfid.PICC_IsNewCardPresent()) {
    return;
  }

  if (!rfid.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println();
  Serial.println("------------------------------");
  Serial.println("RFID CARD DETECTED");

  // Print UID
  Serial.print("Card UID: ");

  for (byte i = 0; i < rfid.uid.size; i++) {

    if (rfid.uid.uidByte[i] < 0x10) {
      Serial.print("0");
    }

    Serial.print(rfid.uid.uidByte[i], HEX);

    if (i < rfid.uid.size - 1) {
      Serial.print(" ");
    }
  }

  Serial.println();

  // Check authorization
  if (isAuthorized()) {

    Serial.println("ACCESS GRANTED");

    // Different sound for accepted card
    accessGrantedSound();

    // Open only if currently closed
    if (!doorIsOpen) {
      openDoor();
    }

  } else {

    Serial.println("ACCESS DENIED");

    // Different sound for rejected card
    accessDeniedSound();
  }

  // Stop RFID communication
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();

  delay(300);
}

// ================= ACCESS GRANTED SOUND =================
// Two high-pitched ascending tones

void accessGrantedSound() {

  tone(BUZZER_PIN, 1000);
  delay(150);
  noTone(BUZZER_PIN);

  delay(80);

  tone(BUZZER_PIN, 1800);
  delay(200);
  noTone(BUZZER_PIN);

  delay(50);
}

// ================= ACCESS DENIED SOUND =================
// Three low-pitched descending tones

void accessDeniedSound() {

  tone(BUZZER_PIN, 500);
  delay(250);
  noTone(BUZZER_PIN);

  delay(80);

  tone(BUZZER_PIN, 350);
  delay(250);
  noTone(BUZZER_PIN);

  delay(80);

  tone(BUZZER_PIN, 250);
  delay(400);
  noTone(BUZZER_PIN);
}

// ================= RFID AUTHORIZATION =================

bool isAuthorized() {

  if (
    compareUID(
      rfid.uid.uidByte,
      rfid.uid.size,
      authorizedUID1,
      sizeof(authorizedUID1)
    )
  ) {
    return true;
  }

  if (
    compareUID(
      rfid.uid.uidByte,
      rfid.uid.size,
      authorizedUID2,
      sizeof(authorizedUID2)
    )
  ) {
   byte authorizedUID1[] = {0x17, 0x61, 0x95, 0x31};
byte authorizedUID2[] = {0x46, 0x2B, 0xD1, 0x3E};
 return true;
  }

  return false;
}

// ================= COMPARE UID =================

bool compareUID(
  byte *uid1,
  byte size1,
  byte *uid2,
  byte size2
) {

  if (size1 != size2) {
    return false;
  }

  for (byte i = 0; i < size1; i++) {

    if (uid1[i] != uid2[i]) {
      return false;
    }
  }

  return true;
}

// ================= OPEN DOOR =================

void openDoor() {

  Serial.println("Opening door...");

  // Move servo
  servoMotor.write(SERVO_OPEN_ANGLE);

  delay(500);

  doorIsOpen = true;
  unlockTime = millis();

  Serial.println("Door OPEN");
}

// ================= LOCK DOOR =================

void lockDoor() {

  Serial.println("Locking door...");

  servoMotor.write(SERVO_CLOSED_ANGLE);

  delay(500);

  doorIsOpen = false;

  Serial.println("Door LOCKED");
}
