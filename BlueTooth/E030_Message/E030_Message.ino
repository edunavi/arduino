#include <SoftwareSerial.h>

#define pinRX 2
#define pinTX 3

SoftwareSerial BluetoothSerial =  SoftwareSerial(pinRX, pinTX);

char receivechar;
char transmitchar;
String receiveStr = "";
String transmitStr = "";

void setup()  {
  Serial.begin(9600);
  BluetoothSerial.begin(9600);
}


void loop() {
  while ( BluetoothSerial.available() > 0 ) {
    receivechar = BluetoothSerial.read();
    receiveStr += receivechar;
    delay(50);
  }

  if ( receiveStr.length() > 0 ) {
    Serial.write("[IN]");
    Serial.println(receiveStr);
    receiveStr = "";
  }

  while ( Serial.available() > 0 ) {
    transmitchar = Serial.read();
    transmitStr += transmitchar;
    delay(50);
  }

  if ( transmitStr.length() > 0 ) {
    BluetoothSerial.write("[OUT]");
    BluetoothSerial.println(transmitStr);
    transmitStr = "";
  }
}
