#include <stdio.h>
#include <SoftwareSerial.h>

#include <core_build_options.h>
#include <swRTC.h>


#define TRUE  1
#define FALSE 0

#define pinRX 2
#define pinTX 3

// 블루투스 통신을 하기 위한 객체
SoftwareSerial bluetooth = SoftwareSerial(pinRX, pinTX);
// 시간정보를 관리할 객체
swRTC rtc;

int showPin = FALSE;    // 디버그 시 핀 정보를 보여줄것인가?
int showData = FALSE;   // 디버그 시 데이터 정보를 보여줄것인가?
int showLED = TRUE;     // LED로 출력을 보낸 것인가?

// arr_dat 배열값과 연결된 핀 번호 정보
int arr_pin[13] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
int arr_dat[13] = {0,};

// 모드를 설정할 변수
int mode = 1;

// 블루투스 통신을 하기 위한 변수
char receivechar;
String receiveString = "";

void print_array();
void display_led(int delaySecond);

void mode1();
void mode2();
void mode3();
void modeClock();

void readCommand();
int parseCommand(String command);
void runCommand(int mode);

void setup()
{
  Serial.begin(9600);
  bluetooth.begin(9600);

  for (int i = 0; i < 13; i++ )
  {
    pinMode( arr_pin[i], OUTPUT);
  }

  rtc.stopRTC();
  rtc.setTime(20, 40, 10);
  rtc.setDate(28, 5, 2018);
  rtc.startRTC();
  //블루투스에 인터럽트를 등록하여 처리하는 방법을 적용하여야 합니다.
  //http://www.hardcopyworld.com/gnuboard5/bbs/board.php?bo_table=lecture_pract&wr_id=2&page=2
  //attachInterrupt(0, callback, CHANGE);
}

void loop()
{
  readCommand();
  runCommand(mode);
  if (!showLED) delay(10000);
}

void readCommand()
{
  // 블루투스로부터 읽어 드릴 값이 있으면
  // 변수 receiveString에 쭈~~욱 읽어드립니다.
  while ( bluetooth.available() > 0 )
  {
    receivechar = bluetooth.read();
    receiveString += receivechar;
    delay(50);
  }

  if ( receiveString.length() > 0 )
  {
    Serial.print(">");
    Serial.println(receiveString);
    mode = parseCommand(receiveString);
    receiveString = "";
  }
}


int parseCommand(String command)
{
  // 명령어를 소문자로 변경합니다.
  command.toLowerCase();

  if ( command.equalsIgnoreCase("mode1") ) 
  {
    return 1;
  } 
  else if (command.equalsIgnoreCase("mode2")) 
  {
    return 2;
  } 
  else if (command.equalsIgnoreCase("mode3")) 
  {
    return 3;
  } 
  else if (command.equalsIgnoreCase("mode4")) 
  {
    return 4;
  } 
  else if (command.startsWith("set")) 
  {
    //set로 시작하면 시간을 셋팅하고 mode를 4번으로 반환합니다.
    String h = command.substring(3, 5);
    String m = command.substring(5);
    rtc.setTime( h.toInt(), m.toInt(), 0);
    return 4;
  } 
  else 
  {
    return 1;
  }
}

void runCommand(int mode) 
{

  switch (mode)
  {
    case 1: mode1();
      break;
    case 2: mode2();
      break;
    case 3: mode3();
      break;
    case 4: modeClock();
      break;
  }
}

void mode1()
{
  int i = 0;

  for (i = 0; i < 13; i++)
  {
    arr_dat[i] = HIGH;
    print_array();
    display_led(1);
  }

  for (i = 12; i >= 0; i--)
  {
    arr_dat[i] = LOW;
    print_array();
    display_led(1);
  }
}

void mode2()
{
  int i = 0;


  for (i = 0; i < 13; i += 2)
  {
    arr_dat[i] = HIGH;
  }
  print_array();
  display_led(1);

  for (i = 0; i < 13; i++)
  {
    arr_dat[i] = !arr_dat[i];
  }
  print_array();
  display_led(1);

  for (i = 0; i < 13; i++ ) {
    arr_dat[i] = LOW;
  }
}

void mode3()
{
  int i = 0, j = 0;

  for (i = 0; i < 13; i++ )
  {
    for (j = 0; j < 13; j++)
    {
      if ( i == j ) arr_dat[j] = HIGH;
      else arr_dat[j] = LOW;
    }
    print_array();
    display_led(1);
  }

  for (i = 11; i >= 0; i-- )
  {
    for (j = 0; j < 13; j++)
    {
      if ( i == j ) arr_dat[j] = HIGH;
      else arr_dat[j] = LOW;
    }
    print_array();
    display_led(1);
  }
}

void modeClock()
{
  byte hour = rtc.getHours();
  byte minute = rtc.getMinutes();
  byte hour10, hour1;
  byte minute10, minute1;

  int i = 0, j = 0;

  /*
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.println(minute, DEC);

  Serial.print(hour, BIN);
  Serial.print(":");
  Serial.println(minute, BIN);
  */

  minute1 = minute % 10;
  minute10 = minute / 10;

  hour1 = hour % 10;
  hour10 = hour / 10;

  for (i = 0; i < 4; i++ )
  {
    arr_dat[j++] = minute1 & (1 << i) ? HIGH : LOW;
  }
  for (i = 0; i < 3; i++ )
  {
    arr_dat[j++] = minute10 & (1 << i) ? HIGH : LOW;
  }
  for (i = 0; i < 4; i++ )
  {
    arr_dat[j++] = hour1 & (1 << i) ? HIGH : LOW;
  }
  for (i = 0; i < 2; i++ )
  {
    arr_dat[j++] = hour10 & (1 << i) ? HIGH : LOW;
  }

  /*
    for( i=0; i < 7; i++ )
    {
    arr_dat[j++] = minute & (1<<i) ? HIGH : LOW;
    }

    for( i=0; i < 6; i++)
    {
    arr_dat[j++] = hour & (1<<i) ? HIGH : LOW;
    }
  */

  print_array();
  display_led(1);
}


void display_led(int delaySecond)
{
  if ( showLED == TRUE )
  {
    for (int i = 0; i < 13; i++ )
    {
      digitalWrite( arr_pin[i], arr_dat[i] );
    }
    delay( delaySecond * 1000 );
  }
}

void print_array()
{

  char buf[4][12] = {0,};

  if ( showPin == TRUE )
  {
    Serial.println("== Pin Information ==");
    // 핀정보
    sprintf(buf[0], "   %2d    %2d",               arr_pin[10],             arr_pin[3] );
    sprintf(buf[1], "   %2d %2d %2d",               arr_pin[9], arr_pin[6], arr_pin[2] );
    sprintf(buf[2], "%2d %2d %2d %2d", arr_pin[12], arr_pin[8], arr_pin[5], arr_pin[1] );
    sprintf(buf[3], "%2d %2d %2d %2d", arr_pin[11], arr_pin[7], arr_pin[4], arr_pin[0] );
    for (int i = 0; i < 4; i++ )
    {
      Serial.println(buf[i]);
    }
  }

  if ( showData == TRUE )
  {
    // 자료정보
    sprintf(buf[0], "   %2d    %2d",               arr_dat[10],             arr_dat[3] );
    sprintf(buf[1], "   %2d %2d %2d",               arr_dat[9], arr_dat[6], arr_dat[2] );
    sprintf(buf[2], "%2d %2d %2d %2d", arr_dat[12], arr_dat[8], arr_dat[5], arr_dat[1] );
    sprintf(buf[3], "%2d %2d %2d %2d", arr_dat[11], arr_dat[7], arr_dat[4], arr_dat[0] );
    Serial.println("== Data Information ==");
    for (int i = 0; i < 4; i++ )
    {
      Serial.println(buf[i]);
    }
  }
  return;
}
