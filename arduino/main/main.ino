#include <string.h>
#include <stdlib.h>     /* atoi */


/*
  Arduino Slave for Raspberry Pi Master
  i2c_slave_ard.ino
  Connects to Raspberry Pi via I2C

  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
byte pos = 48;

void wait_for_address()
{
  byte new_pos = pos;
  while(millis() < 5000) {
    while(Serial.available()) {
      pos = Serial.read() + 1;
    }
    Serial.write(pos);
    delay(100);
  }
}

// Include the Wire library for I2C
#include <Wire.h>

uint64_t turn_off_ms = 0;
uint64_t turn_off_delay_ms = 3000;

const int ledPin = 13;
const int fetPin = 10;
const int btnPin = 2;

void setup() {
  Serial.begin(9600);

  // Setup pin 13 as output and turn LED off
  pinMode(ledPin, OUTPUT);
  pinMode(fetPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  for(int i=0; i<10; i++) {
    delay(50);
    digitalWrite(ledPin, HIGH);
    delay(50);
    digitalWrite(ledPin, LOW);
  }
  digitalWrite(fetPin, LOW);

  wait_for_address();

  Wire.begin(pos);

  // Call receiveEvent when data received
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent);
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
