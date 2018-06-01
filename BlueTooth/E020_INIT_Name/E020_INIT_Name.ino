#include <SoftwareSerial.h>

#define rxPin 2
#define txPin 3

// set up a new serial port
SoftwareSerial BluetoothSerial =  SoftwareSerial(rxPin, txPin);
String bluetoothName = "INK94_HC_06";
String password = "1234";

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

  BluetoothSerial.print("AT+PIN" + password);
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
