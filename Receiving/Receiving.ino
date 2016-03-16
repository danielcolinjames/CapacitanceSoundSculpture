#include <Firmata.h>
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

XBee xbee = XBee();

SoftwareSerial xbeeSerial (6, 7); // (Rx, Tx)

Rx16Response rx16 = Rx16Response();

long incoming;
uint8_t byteArray[4];

void setup() {
  Serial.begin(9600);
  xbeeSerial.begin(9600);

  xbee.setSerial(xbeeSerial);
  
  Serial.println("Starting...");
  
  Firmata.begin(57600);
}

void loop() {
  
  xbee.readPacket();
  
  if (xbee.getResponse().isAvailable()) {
    // got something
    
    if (xbee.getResponse().getApiId() == RX_16_RESPONSE) {
      xbee.getResponse().getRx16Response(rx16);
      
      byteArray[0] = rx16.getData(0);
      byteArray[1] = rx16.getData(1);
      byteArray[2] = rx16.getData(2);
      byteArray[3] = rx16.getData(3);
      
      incoming = (
        ((uint32_t)byteArray[0] << 24) +
        ((uint32_t)byteArray[1] << 16) +
        ((uint32_t)byteArray[2] << 8) + 
        ((uint32_t)byteArray[3] )
      );
      
    }
  }
  else if (xbee.getResponse().isError()) {
    
  }
  else {
    
  }
  
  // here I am sending the result as analog value. 
  // the first number normaly indicates the pin number. it can go up to 15
  Firmata.sendAnalog(8, incoming);
}
