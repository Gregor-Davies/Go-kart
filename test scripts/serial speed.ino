#include "timer.h"

Timer timer;

const int LM393 = 17;
int counter = 0;
void setup() {
  attachInterrupt(digitalPinToInterrupt(LM393), count, RISING);
  Serial.begin(115200);
  timer.setInterval(10000);
  timer.setCallback(KMH);
  timer.start();
}

void count() {
  counter++;
}

void KMH() {
  // this converts the number to rpm and into kmh, the 60 is for rpm and the first number is wheel diameter in cm k = d * r * 0.001885
  Serial.print(2.57 * counter * 60 * 0.001885);
  Serial.println(" km/h");
  counter = 0;
}

void loop() {
  timer.update();
}