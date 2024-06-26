#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define LORA_V1_0_OLED  0
#define LORA_V1_2_OLED  0
#define LORA_V1_6_OLED  1
#define LORA_V2_0_OLED  0

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26
#define BAND 915E6

#define MAX_HOPS 1 // Maximum number of hops allowed

//OLED pins
#define OLED_SDA 21
#define OLED_SCL 22 
#define OLED_RST 23
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//packet counter
int counter = 0;

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

void setup() {
  //initialize Serial Monitor
  Serial.begin(115200);

  //reset OLED display via software
  pinMode(OLED_RST, OUTPUT);
  digitalWrite(OLED_RST, LOW);
  delay(20);
  digitalWrite(OLED_RST, HIGH);

  //initialize OLED
  Wire.begin(OLED_SDA, OLED_SCL);
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3c, false, false)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0,0);
  display.print("LoRa Gateway ");
  display.display();
  
  Serial.println("LoRa Gateway");

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0,10);
  display.print("LoRa Initializing OK!");
  display.display();
  delay(2000);
}

void loop(){
    //try to parse packet
  int packetSize = LoRa.parsePacket();
  if (packetSize) {
    Serial.print("Received packet '");

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }

    Serial.print("' with RSSI ");
    Serial.print(LoRa.packetRssi());
    Serial.print(" and SNR ");
    Serial.println(LoRa.packetSnr());

   // Dsiplay information
   display.clearDisplay();
   display.setCursor(0,0);
   display.print("LoRa Gateway");
   display.setCursor(0,10);
   display.print("Received packet :");
   display.setCursor(0,20);
   display.print((char)LoRa.read());
   display.setCursor(0,30);
   display.print("RSSI:");
   display.setCursor(30,30);
   display.print(LoRa.packetRssi());
   display.setCursor(0,40);
   display.print("SNR :");
   display.setCursor(30,40);
   display.print(LoRa.packetSnr());
   display.display();
  
  }
  }
