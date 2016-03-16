#include <CapacitiveSensor.h>
#include <SoftwareSerial.h>
#include <XBee.h>

/*
 * CapitiveSense Library Demo Sketch
 * Paul Badger 2008
 * Uses a high value resistor e.g. 10M between send pin and receive pin
 * Resistor effects sensitivity, experiment with values, 50K - 50M. 
 * Larger resistor values yield larger sensor values.
 * Receive pin is the sensor pin - try different amounts of foil/metal on this pin
 */
 
 /*
 + send capacitive sensing result via Firmata to your computer
 */

 // 10M resistor between pins 4 & 2, pin 2 is sensor pin, 
 // add a wire and or foil if desired
 
CapacitiveSensor   cs_4_2 = CapacitiveSensor(4, 2);

XBee xbee = XBee();

SoftwareSerial xbeeSerial (6, 7); // (Rx, Tx)

long reading;

uint8_t byteArray[4];

Tx16Request tx = Tx16Request(0x2, byteArray, 4);

void setup() {
  Serial.begin(9600);
  xbeeSerial.begin(9600);
  
  xbee.setSerial(xbeeSerial);
  
  Serial.println("Starting...");
  
  // turn off autocalibrate on channel 1 - just as an example
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void loop() {
  
  reading =  cs_4_2.capacitiveSensor(30);
  
  byteArray[0] = (int)((reading >> 24) & 0xFF);
  byteArray[1] = (int)((reading >> 16) & 0xFF);
  byteArray[2] = (int)((reading >> 8) & 0XFF);
  byteArray[3] = (int)((reading & 0XFF));
  
  tx = Tx16Request(0x2, byteArray, 4);
  
  xbee.send(tx);
  
  Serial.print("reading = ");
  Serial.println(reading);
  
  // arbitrary delay to limit data to serial port 
  delay(10);
}
