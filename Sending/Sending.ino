#include <CapacitiveSensor.h>
#include <SoftwareSerial.h>

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

SoftwareSerial xbee (2, 3); // (Rx, Tx)

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  
  Serial.println("Starting...");
  
  // turn off autocalibrate on channel 1 - just as an example
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
}

void loop() {
  
  long total1 =  cs_4_2.capacitiveSensor(30);
  
  Serial.print("total1 = ");
  Serial.println(total1);
  
  xbee.write((unsigned char) total1);
  
  // arbitrary delay to limit data to serial port 
  delay(10);
}
