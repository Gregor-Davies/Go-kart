// wifiy
#include <WiFi.h>
#include "ESPAsyncWebServer.h"

#include <SPIFFS.h>

// lora stuff
#include <SPI.h>
#include <LoRa.h>

//oled stugg
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//  ntp stuff
#include <NTPClient.h>
#include <WiFiUdp.h>


//defining lora pins
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define  DIO0 26

// legal operating band for the lora frequency "can be changed"
#define BAND 866E6

// oled pins
#define OLED_SDA 4
#define OLED_SCL 15
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED WIDYH
#define SCREEN_HEIGHT 64 // OLED SVCREEN HEIGHT 


// IMPORTANT
// IMPORTANT
// IMPORTANT will update with wifimanager
// IMPORTANY
// REPLACE ssid
const char* ssid = "";
const char* password = "";

// define ntp to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

// variables to save date and time
String formattedDate;
String day;
String hour;
String timestamp;

// init varibles to get and store lora
int rssi;
String loRaMessage;
String temperature;
String readingID;

// create async web
AsyncWebServer server(80);

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

//replaces placeholders
String processor(const String& var){
  if(var == "TEMPERATURE"){
    return temperature;
  }
  else if(var == "RRSI"){
    return String(rssi);
  }
  return String();
}

// init the bloody display
void startOLED(){
  //reset the oled
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //innit the display
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) {
    Serial.println(F("SSD1306 ALLOCATION FAILED"));
    for(;;); // if failed don't do anything and repeat.
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LORA SENDER");
}

// init the lora module
void startLoRa(){
  int counter;
  //spi lora pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup transciever
  LoRa.setPins(SS, RST, DIO0);

  while (!LoRa.begin(BAND) && counter < 10) {
    Serial.print(".");
    counter++;
    delay(500);
  }
  if (counter == 10) {
    // incremnet reading id every new reading
    Serial.println("STARTING LORA FAILED");
  }
  Serial.println("lora ok!");
  display.setCursor(0,10);
  display.clearDisplay();
  display.print("lora ok!");
  display.display();
  delay(2000);
}

void connectWiFi(){
  // connect with ssid and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // print ip and start web
  Serial.println("");
  Serial.println("WiFI connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  display.setCursor(0,20);
  display.print("Access the webserver at: ");
  display.setCursor(0,30);
  display.print(WiFi.localIP());
  display.display();
}
//get lora packet and the readings
void getLoRaData() {
  Serial.print("Lora packet recieved: ");
  // read packet
  while (LoRa.available()) {
    String LoRaData = LoRa.readString();
    //String example: 1/27.43&654#95.34
    Serial.print(LoRaData);

    // get reading id and temp
    int pos1 = LoRaData.indexOf('/');
    int pos2 = LoRaData.indexOf('&');
    readingID = LoRaData.substring(0, pos1);
    temperature = LoRaData.substring(pos1 +1, pos2);    
  }
  // get rssi
  rssi = LoRa.packetRssi();
  Serial.print(" with RSSI");
  Serial.println(rssi);
}

// function to get date and time
void getTimeStamp() {
  while (!timeClient.update()) {
    timeClient.forceUpdate();
  }
  // the date comes like this 2022-05-28T16:00:13Z so it has to be extracted
  formattedDate = timeClient.getFormattedDate();
  Serial.println(formattedDate);

  // extract date
  int splitT = formattedDate.indexOf("T");
  day = formattedDate.substring(0, splitT);
  Serial.println(hour);
  timestamp = day + " " + hour;
}

void setup() {
  // init serial monitor
  Serial.begin(115200);
  startOLED();
  startLoRa();
  connectWiFi();

  if(!SPIFFS.begin()){
    Serial.println("AN ERROR OCCURED WHILE MOUNTING SPIFFS");
    return;
  }
  // route for web  pahe might need to add stylesheet here
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html", String(), false, processor);
  });
  server.on("/temperature", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", temperature.c_str());
  });
  server.on("/timestamp", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", timestamp.c_str());
  });
  server.on("/rssi", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", String(rssi).c_str());
  });
  // start the server
  server.begin();

  // init the ntp client
  timeClient.begin();
  // settig the offset current is gmt + 1
  timeClient.setTimeOffset(3600);
}

void loop() {
  // checks if anyt lora packets are avaliable
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    getLoRaData();
    getTimeStamp();
  }
}
