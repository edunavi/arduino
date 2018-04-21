#define ledPIN1   7
#define ledPIN2   8
#define ledPIN3   9

void setup() {
  // put your setup code here, to run once:
  pinMode( ledPIN1, OUTPUT);
  pinMode( ledPIN2, OUTPUT);
  pinMode( ledPIN3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledPIN1, HIGH);
  digitalWrite(ledPIN2, HIGH);
  digitalWrite(ledPIN3, HIGH);
  delay(1000);
  digitalWrite(ledPIN1, LOW);
  digitalWrite(ledPIN2, LOW);
  digitalWrite(ledPIN3, LOW);
  delay(1000);
}
