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
Servo servo;
int currentSpeedVal;
int lastInputSpeedVal;

void setup() {
  BT.begin(9600); // set the data rate for the SoftwareSerial port
  BT.println("Hello from Arduino");
  servo.attach(10); // connect servo output signal to pin 10
  lastInputSpeedVal = 0;
  currentSpeedVal = 0;
}

int SetSpeed() {
  if (BT.available()) {
    int command = BT.read();
    switch (command) {
      case '1': lastInputSpeedVal = 1 * 102; break;
      case '2': lastInputSpeedVal = 2 * 102; break;
      case '3': lastInputSpeedVal = 3 * 102; break;
      case '4': lastInputSpeedVal = 4 * 102; break;
      case '5': lastInputSpeedVal = 5 * 102; break;
      case '6': lastInputSpeedVal = 6 * 102; break;
      case '7': lastInputSpeedVal = 7 * 102; break;
      case '8': lastInputSpeedVal = 8 * 102; break;
      case '9': lastInputSpeedVal = 9 * 102; break;
      case 'm': lastInputSpeedVal = 1023; break; // max 1023
      case 's': lastInputSpeedVal = 0; break; // stop = 0
      default: BT.println("command: " + String(command)); delay(100); break;
    }
  }
  BT.println("lastInputSpeedVal: " + String(lastInputSpeedVal));
  return lastInputSpeedVal;
}

void Program() {


  while (currentSpeedVal < SetSpeed()) {
    currentSpeedVal++;
    servo.write(currentSpeedVal);
    BT.println("Current speed (increasing): " + String(currentSpeedVal));
    delay(50);
  }

  while (currentSpeedVal > SetSpeed()) {
    currentSpeedVal--;
    servo.write(currentSpeedVal);
    BT.println("Current speed (decreasing): " + String(currentSpeedVal));
    delay(50);
  }

  servo.write(currentSpeedVal);
  BT.println("Coasting speed: " + String(currentSpeedVal));
}

void loop() {
  Program();
}
