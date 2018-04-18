#include <SoftwareSerial.h>

#define rxPin 10
#define txPin 11

// set up a new serial port
SoftwareSerial BluetoothSerial =  SoftwareSerial(rxPin, txPin);
String bluetoothName = "TEST_HC_06";

void setup()  {
  Serial.begin(9600);
  BluetoothSerial.begin(9600);

  delay(1000);

  BluetoothSerial.write("AT");
  waitForResponse();

  BluetoothSerial.print("AT+VERSION");
  waitForResponse();

  BluetoothSerial.print("AT+NAME" + bluetoothName);
  waitForResponse();

  Serial.println("Done.");
}

void waitForResponse() {
  delay(1000);
  while (BluetoothSerial.available()) {
    Serial.write(BluetoothSerial.read());
  }
  Serial.write("\n");
}


void loop() {


}
