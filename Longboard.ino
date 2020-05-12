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
SoftwareSerial BT(0, 1);
char command; // stores incoming character from other device

void setup()
{
  pinMode(13, OUTPUT); // set digital pin to control as an output
  BT.begin(9600); // set the data rate for the SoftwareSerial port
  BT.println("Hello from Arduino");
}

void loop()
{
  if (BT.available())
  {
    command = (BT.read());
    switch(command){
      case 't': BT.println("working..."); break; // t = test 
      defualt: BT.println("error receiving command"); break; // t = test
    }
  }
}
