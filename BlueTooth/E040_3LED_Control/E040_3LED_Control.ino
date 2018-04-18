
#include <SoftwareSerial.h>

#define pinRX 2
#define pinTX 3

#define pinLED1 8
#define pinLED2 9
#define pinLED3 10

SoftwareSerial BluetoothSerial =  SoftwareSerial(pinRX, pinTX);

char receivechar;
String receiveStr = "";
int led_status[3] = {0, 0, 0};

void setup()  {
  pinMode(pinLED1, OUTPUT);
  pinMode(pinLED2, OUTPUT);
  pinMode(pinLED3, OUTPUT);
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
    Serial.write("[B]");
    Serial.println(receiveStr);
    if ( receiveStr.equalsIgnoreCase("one") ) {
      led_status[0] = !led_status[0];
    }
    else if ( receiveStr.equalsIgnoreCase("two") ) {
      led_status[1] = !led_status[1];
    }
    else if ( receiveStr.equalsIgnoreCase("three") ) {
      led_status[2] = !led_status[2];
    }
    else if ( receiveStr.equalsIgnoreCase("all") ) {
      for (int i = 0; i < 3; i++ ) {
        led_status[i] = !led_status[i];
      }
    }
    else if ( receiveStr.equalsIgnoreCase("on") ) {
      for (int i = 0; i < 3; i++ ) {
        led_status[i] = 1;
      }
    }
    else if ( receiveStr.equalsIgnoreCase("off") ) {
      for (int i = 0; i < 3; i++ ) {
        led_status[i] = 0;
      }
    }
    else {
      Serial.println("ERROR : command can't parse");
    }

    ledstatus();
    receiveStr = "";
  }

}

void ledstatus() {
  for ( int i = 0; i < 3; i++ ) {
    digitalWrite( pinLED1 + i, led_status[i] );
  }
  delay(1000);
}

