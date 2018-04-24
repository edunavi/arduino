int speaker = 9;
int frequency[8] = {262, 294, 330, 349,
                    392, 440, 494, 523
                   };
int i = 0;

void setup() {
  pinMode( speaker, OUTPUT );
}

void loop() {
  for (i = 0; i < 8; i++) {
    tone(speaker, frequency[i], 250);
    delay(250);
  }
  delay(5000);
}
