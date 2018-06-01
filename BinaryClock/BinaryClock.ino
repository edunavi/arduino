#include <core_build_options.h>
#include <swRTC.h>


swRTC rtc;

void setup() {

  for(int i=0; i <= A5; i++)
  {
    pinMode(i, OUTPUT);
  }
  
  
  rtc.stopRTC();
  rtc.setTime(20, 40, 10);
  rtc.setDate(28, 5, 2018);
  rtc.startRTC();
  Serial.begin(9600);

}

void loop() {
  
  byte hour = rtc.getHours();
  byte minute = rtc.getMinutes();
  int i = 0, output = 0;

  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.println(minute, DEC);
  
  Serial.print(hour, BIN);
  Serial.print(":");
  Serial.println(minute, BIN);
  /*
  Serial.println(A0, DEC);
  Serial.println(A1, DEC);
  Serial.println(A2, DEC);
  Serial.println(A3, DEC);
  Serial.println(A4, DEC);
  Serial.println(A5, DEC);
  */

  /* 분셋팅 */
  for( i=0; i < 7; i++ ){
    output = minute & (1<<i) ? HIGH : LOW;
    Serial.println(String(2+i) + "> " + output);
    digitalWrite(2+i, output); 
  }
  Serial.println("");
  /* 시 셋팅 */
  for( i=0; i < 6; i++ ){
    output = hour & (1<<i) ? HIGH : LOW;
    Serial.println(String(9+i) + "> " + output);
    digitalWrite(9+i, output);
  }
  Serial.println("");
  delay(1000);
}

