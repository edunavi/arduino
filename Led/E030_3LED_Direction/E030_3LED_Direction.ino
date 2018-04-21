#define ledPIN1   7
#define ledPIN2   8
#define ledPIN3   9

void setup() {
  // put your setup code here, to run once:
  pinMode( ledPIN1, OUTPUT);
  pinMode( ledPIN2, OUTPUT);
  pinMode( ledPIN3, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int i = 1, m = 0, pos = 0;
  while ( 1 ) {
    m = i % 4;


    if ( m == 0 ) {
      pos = 2;
    }
    else {
      pos = m;
    }
    Serial.println( String(i) + " : " + String(pos));
    displayLED(pos, 1);

    //i 값이 무한으로 갈 수 있으니... 중간에 끊어줍니다.
    if ( m == 0 ) break;

    i++;
  }
}

void displayLED(int pos, int sec) {
  for (int i = 0; i < 3; i++) {
    if ( i == (pos - 1) )
      digitalWrite(ledPIN1 + i, HIGH);
    else
      digitalWrite(ledPIN1 + i, LOW);
  }
  delay(1000 * sec);
}

