

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <HTTPClient.h>

#include <WiFi.h>
#include <time.h>
#include <SPI.h>
#include <LoRa.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define LIGHT_SENSOR_PIN 36

int counter = 0;
HTTPClient http;
String mac;

Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "WiFi Fritzbox";
const char* password = "jorisputteneers";

void setup() {
  pinMode(25, OUTPUT);
  pinMode(LIGHT_SENSOR_PIN, INPUT);
  Serial.begin(115200);

  delay(1000);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  // dont use adc2 pins if you want to use wifi
  while(WiFi.status() != WL_CONNECTED){
      Serial.print(".");
      oled.print(".");
      delay(100);
  }

  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
  mac = WiFi.macAddress();

  // initialize OLED display with address 0x3C for 128x64
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(100);         
  oled.clearDisplay();
  oled.setTextColor(WHITE);
  oled.setCursor(0, 10);

  oled.setTextSize(2);
  oled.println("MAC");
  oled.setTextSize(1);
  oled.println(WiFi.macAddress());
  Serial.println(WiFi.localIP());
  oled.display();   
  delay(3000);   
}

//functions
void blinkLed(){
  digitalWrite(25,LOW);
  delay(200);
  digitalWrite(25,HIGH);
  delay(200);
}

uint16_t readSensor(){
  return analogRead(LIGHT_SENSOR_PIN);
}

void printOled(){
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setCursor(0, 10);
  oled.println(readSensor());
  oled.println(WiFi.localIP());
  oled.display();   
  delay(2000);
}

void sendData(uint16_t sensorID, String value, String time)
{
  http.begin("http://hasdata.xyz/");
  http.addHeader("Content-Type", "application/json");


  String json = "{\"sensorID\":\"";
  json.concat(sensorID);
  json.concat("\", \"value\": \"");
  json.concat(value);
  json.concat("\" ,\"time\": \"");
  json.concat(time);
  json.concat("\"}");

  int httpResponseCode = http.PUT(json);
  Serial.println(httpResponseCode);

  http.end();
}
void loop() {
  printOled();
  blinkLed();
  sendData(readSensor(),"sensor2","sensor2");
  delay(5000);
}