/**
   Author: Spencer Rosenvall
   Project Name: Electrical Longboard BT
   Date: 5/11/2020

   Connect BT module TX to D0
   Connect BT module RX to D1
   Connect BT Vcc to 5V, GND to GND

   connect to hc-06 on phone, pass=1234
   connect using serial bluetooth android app
*/

#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BT(0, 1);
Servo ESC;
int currentSpeedVal;
int lastInputSpeedVal;
int lastCommand;

void setup() {
  BT.begin(9600); // set the data rate for the SoftwareSerial port
  BT.println("Hello from Arduino");
  lastInputSpeedVal = 0;
  currentSpeedVal = 0;
  lastCommand = 0;
  ESC.attach(8);
  ESC.writeMicroseconds(1000);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH); // power for the rf/rx module
}

int SetSpeed() {
  if (BT.available()) {
    int command = BT.read();
    if (command != lastCommand) {
      switch (command) {
        case '1': lastInputSpeedVal = 1 * 102; lastCommand = command; break;
        case '2': lastInputSpeedVal = 2 * 102; lastCommand = command; break;
        case '3': lastInputSpeedVal = 3 * 102; lastCommand = command; break; // aroudn 300 appears to be the max
        case 'm': lastInputSpeedVal = 1023; lastCommand = command; break; // max 1023
        case 's': lastInputSpeedVal = 0; lastCommand = command; break; // stop = 0
        default: break;
      }
      BT.println("command: " + String(lastInputSpeedVal / 102));
    }
  }
  delay(15);
  return lastInputSpeedVal;
}

void Program() {
  currentSpeedVal = map(SetSpeed(), 0, 1023, 1000, 5000);
  ESC.writeMicroseconds(currentSpeedVal);
  //BT.println("Coasting speed: " + String(last));
}

void loop() {
  Program();
}
