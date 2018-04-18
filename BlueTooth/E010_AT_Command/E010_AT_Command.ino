#include <SoftwareSerial.h>

#define pinRX 2
#define pinTX 3

SoftwareSerial BluetoothSerial =  SoftwareSerial(pinRX, pinTX);

char receivechar;
char transmitchar;

void setup()  {
  Serial.begin(9600);
  BluetoothSerial.begin(9600);
}


void loop() {
  if ( BluetoothSerial.available() > 0 ) {
    receivechar = BluetoothSerial.read();
    Serial.write( receivechar );
  }

  if ( Serial.available() > 0 ) {
    transmitchar = Serial.read();
    BluetoothSerial.write( transmitchar );
  }
}
