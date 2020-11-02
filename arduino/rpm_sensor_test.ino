const int sensorPin = 3;
int val;
int revolutions;

void setup() {
  pinMode(sensorPin, INPUT);
}

void loop() {
  do {
    delay(1);
  }while (sensorPin == LOW);
  val++;
  if (val == 12){
    revolutions++;
    val = 0;
  }
}
