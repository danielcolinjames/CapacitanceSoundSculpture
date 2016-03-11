#include <Firmata.h>
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

SoftwareSerial xbee (2, 3); // (Rx, Tx)

void setup() {
  Serial.begin(9600);
  xbee.begin(9600);
  
  Serial.println("Starting...");
  
  Firmata.begin(57600);
}

void loop() {

  unsigned char incoming = xbee.read();
  
  long total1 = (long)incoming;
  
  // here I am sending the result as analog value. 
  // the first number normaly indicates the pin number. it can go up to 15
  Firmata.sendAnalog(8, total1);

  // arbitrary delay to limit data to serial port 
  delay(10);
}
