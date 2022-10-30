#include "timer.h"
#include <U8x8lib.h>

Timer timer;
//oled used
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);


const int LM393 = 17;
int counter = 0;

void setup() {
  attachInterrupt(digitalPinToInterrupt(LM393), count, RISING);
  Serial.begin(115200);
  timer.setInterval(10000);
  timer.setCallback(KMH);
  timer.start();
  u8x8.begin();
  u8x8.setFont(u8x8_font_chroma48medium8_r);
}

void count() {
  counter++;
}

void KMH() {
  // this converts the number to rpm and into kmh, the 60 is for rpm and the first number is wheel diameter in cm k = d * r * 0.001885
  int speed = 2.57 * counter * 60 * 0.001885;
  u8x8.setCursor(0, 0);
  char buf[15];
  sprintf(buf, "SPEED: %d km/h", speed);
  u8x8.print(buf);
  counter = 0;
}

void loop() {
  timer.update();
}