#include <SoftwareSerial.h>

#define pinRX     2
#define pinTX     3

#define pinRED    9
#define pinGREEN  10
#define pinBLUE   11

SoftwareSerial BluetoothSerial =  SoftwareSerial(pinRX, pinTX);

char receivechar;
String receiveStr = "";
int led_status[4] = {0, 255, 255, 255};

void setup()  {
  pinMode(pinRED, OUTPUT);
  pinMode(pinGREEN, OUTPUT);
  pinMode(pinBLUE, OUTPUT);
  Serial.begin(9600);
  BluetoothSerial.begin(9600);
}


void loop() {

  while ( BluetoothSerial.available() > 0 ) {
    receivechar = BluetoothSerial.read();

    if ( receivechar == ')') {
      break;
    }
    receiveStr += receivechar;
    delay(50);
  }

  Serial.println(receiveStr);

  if ( receiveStr.length() > 0 ) {
    parsecolor(receiveStr);
    receiveStr = "";
  }
  ledstatus();
}

void parsecolor(String str) {
  Serial.println(str);
  if ( str.equalsIgnoreCase("on") ) {
    led_status[0] = 1;
  } else if (str.equalsIgnoreCase("off")) {
    led_status[0] = 0;
  } else {
    int SP1 = str.indexOf('.');
    int SP2 = str.indexOf('.', SP1 + 1);
    int SP3 = str.indexOf('.', SP2 + 1);
    String R = str.substring(0, SP1);
    String G = str.substring(SP1 + 1, SP2);
    String B = str.substring(SP2 + 1, SP3);
    led_status[1] = constrain(R.toInt(), 0, 255);
    led_status[2] = constrain(G.toInt(), 0, 255);
    led_status[3] = constrain(B.toInt(), 0, 255);
  }
}

void ledstatus() {
  if ( led_status[0] == 0 ) {
    setcolor(255, 0, 0);
  }
  else {
    setcolor(led_status[1], led_status[2], led_status[3] );
  }

  led_status[0] == 1 ? Serial.print("[ON] ") : Serial.print("[OFF] ");
  Serial.println(String(led_status[0]) + " [COLOR]" + String(led_status[1]) + ":" + String(led_status[2]) + ":" + String(led_status[3]));
  delay(1000);
}


void setcolor(int red, int green, int blue) {
  analogWrite(pinRED, red);
  analogWrite(pinGREEN, green);
  analogWrite(pinBLUE, blue);
}
