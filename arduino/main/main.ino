/*
  Arduino Slave for Raspberry Pi Master
  i2c_slave_ard.ino
  Connects to Raspberry Pi via I2C

  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/

// Include the Wire library for I2C
#include <Wire.h>

uint64_t turn_off_ms = 0;
uint64_t turn_off_delay_ms = 3000;

const int ledPin = 13;
const int fetPin = 10;
const int btnPin = 2;

void setup() {
  // Join I2C bus as slave with address 8
  Wire.begin(0x8);

  // Call receiveEvent when data received
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);

  // Setup pin 13 as output and turn LED off
  pinMode(ledPin, OUTPUT);
  pinMode(fetPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);
  digitalWrite(fetPin, LOW);
}

// Function that executes whenever data is received from master
void receiveEvent(int howMany) {
  while (Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    digitalWrite(fetPin, HIGH);
    digitalWrite(ledPin, HIGH);
    turn_off_ms = millis() + 3000;
  }
}

void requestEvent() {
  Wire.write(digitalRead(btnPin));
}

void loop() {
  if (turn_off_ms > 0 && millis() > turn_off_ms) {
    digitalWrite(fetPin, LOW);
    digitalWrite(ledPin, LOW);
    turn_off_ms = 0;
  }
  delay(100);
}
