#define ledPIN  2

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPIN, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite( ledPIN, HIGH );
  delay(1000);
  digitalWrite( ledPIN, LOW );
  delay(1000);
}
