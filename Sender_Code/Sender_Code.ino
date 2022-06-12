// Lora
#include <SPI.h>
#include <LoRa.h>

// Oled display libraries.
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// include the sensor libraries here
#include <DallasTemperature.h>
#include <OneWire.h>


// pins for the attenna meight need to change this as the lora32 might be different
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

// *Legal* Bands for frequency
#define BAND 866E6

// OLED pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED width (Pixels)
#define SCREEN_HEIGHT 64 // Screen height in pixels

//  Define the temp sensor here (Not added yet)
#define ONE_WIRE_BUS 2
OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

// packet counter
int readingID = 0;

int counter = 0;
String LoRaMessage = "";

float temperature = 0;

// this creates a display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

// start init of oled
void startOLED(){
  // reset the display
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  // init oled
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { //adress 0x3c for 128x32
    Serial.println(F("SSD1306 ALLOCATION HAS FAILED"));
    for(;;); // IF IT FAILS DONT PRECEED
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LORA SENDER");
}

// intialize the lora module 
void startLoRA(){
  // SPI LOra pins
  SPI.begin(SCK, MISO, MOSI, SS);
  // seyup the lora transciever modeul
  LoRa.setPins(SS, RST, DIO0);

  while (!LoRa.begin(BAND) && counter < 10) {
    Serial.print(".");
    counter++;
    delay(500);
  }
  if (counter == 10) {
    // add 1 when a new reading is done
    readingID++;
    Serial.println("STARTING LORA HAS FAILED!");
  }
  Serial.println("LORA INIT IS OK");
  display.setCursor(0,10);
  display.clearDisplay();
  display.print("LORA OK");
  display.display();
  delay(2000);
  }
// gets readings from temperature sensor 1
void getReadings(){
  sensors.begin();
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
}

void sendReadings() {
  LoRaMessage = String(readingID) + "/" + String(temperature);
  // send packet to reciever
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();

  display.clearDisplay();
  display.setCursor(0,0);
  display.setTextSize(1);
  display.print("PACKET SENT.");
  display.setCursor(0,20);
  display.print("Temp:");
  display.setCursor(72,20);
  display.print(temperature);
  display.setCursor(0,50);
  display.print("Reading ID:");
  display.setCursor(66,50);
  display.print(readingID);
  display.display();
  Serial.print("sending packet");
  Serial.println(readingID);
  readingID++;
}

// innit the serial monitor
void setup() {
  Serial.begin(115200);
  startOLED();
  startLoRA();
}

void loop() {
  getReadings();
  sendReadings();
  delay(10000);
}
