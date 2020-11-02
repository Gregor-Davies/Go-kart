const int inPin = A0;
int current

void setup() {
  pinMode(inPin, INPUT);
}

void loop() {
  current = (2.5 - analogRead(inPin) / 66;
}
