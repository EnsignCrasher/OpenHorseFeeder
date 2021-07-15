#include <string.h>
#include <stdlib.h>     /* atoi */


/*
  Arduino Slave for Raspberry Pi Master
  i2c_slave_ard.ino
  Connects to Raspberry Pi via I2C

  DroneBot Workshop 2019
  https://dronebotworkshop.com
*/
int pos = 1;

void getline(char * buffer)
{
  uint8_t idx = 0;
  char c;
  buffer[0] = 0;
  do
  {
    while (Serial.available() == 0) ; // wait for a char this causes the blocking
    c = Serial.read();
    buffer[idx++] = c;
  }
  while (c != '\n' && c != '\r');
  buffer[idx] = 0;
}

void wait_for_address()
{
  char buf[128];
  while(millis() < 5000) {
    while(Serial.available()) {
      getline(buf);
      if (strncmp(buf, "pos: ", 5) == 0) {
        int new_pos = atoi(&buf[4]) + 1;
        if (pos != new_pos) {
          pos = new_pos;
          Serial.print("Setting new position to ");
          Serial.println(pos);
        }
      }
      Serial.print("received: ");
      Serial.println(buf);
    }
    Serial.print("pos: ");
    Serial.println(pos);
    delay(100);
  }
  Serial.print("Starting I2C at address ");
  Serial.println(pos);
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
  Serial.println("start");

  // Setup pin 13 as output and turn LED off
  pinMode(ledPin, OUTPUT);
  pinMode(fetPin, OUTPUT);
  pinMode(btnPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);
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
