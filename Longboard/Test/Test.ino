#include <Servo.h>

Servo ESC;

void setup(){
  ESC.attach(8);
  ESC.writeMicroseconds(1000);
  Serial.begin(9600);
}

void loop(){
  int val;
  val = analogRead(A0);
  val = map(val, 0, 180, 1000, 5000);
  ESC.writeMicroseconds(val);
  Serial.println(val);
}
