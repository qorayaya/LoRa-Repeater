//Library for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 23
#define DIO0 26

//define LoRa parameters
#define BAND 915E6
#define SF 7
#define MAX_HOPS 2 // Maximum number of hops allowed

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
  display.print("LoRa Repeater ");
  display.display();
  
  Serial.println("LoRa Repeater");

  //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(SF);
  LoRa.setSyncWord(0xF1);
  
  Serial.println("LoRa Initializing OK!");
  display.setCursor(0,10);
  display.print("LoRa Initializing OK!");
  display.display();
}

void loop() {
  // Receive packet
  int packetSize = LoRa.parsePacket();

  if (packetSize) {
    // Read packet
    String incoming = "";
    while (LoRa.available()) {
      incoming += (char)LoRa.read();
    }

    // Display received packet
    Serial.println("Received    : " + incoming + " With RSSI and SNR : " + LoRa.packetRssi() + " and " + LoRa.packetSnr() );

    // Check WideN path
    if (incoming.startsWith("Wide")) {
      int dashIndex = incoming.indexOf('-');
      if (dashIndex != -1) {
        String hopCountStr = incoming.substring(dashIndex + 1);
        int hopCount = hopCountStr.toInt();

        // If hop count is valid, decrement and retransmit if necessary
        if (hopCount > 0 && hopCount <= MAX_HOPS) {
          hopCount--;
          
          String newPacket = "Wide" + incoming.substring(dashIndex - 1 , dashIndex) + "-" + String(hopCount) + incoming.substring(dashIndex + 2);
          
          LoRa.beginPacket();
          LoRa.print(newPacket);
          LoRa.endPacket();
          counter ++;
          Serial.println("Transmitted : " + newPacket);

          display.clearDisplay();
          display.setCursor(0,0);
          display.print("LoRa Repeater ");
          display.setCursor(0,10);
          display.print("PR   : ");
          display.setCursor(40,10);
          display.print(counter);
          display.setCursor(0,20);
          display.print("RSSI : ");
          display.setCursor(40,20);
          display.print( LoRa.packetRssi() );
          display.setCursor(0,30);
          display.print("SNR  : ");
          display.setCursor(40,30);
          display.print( LoRa.packetSnr() );
          display.setCursor(0,40);
          display.print("Packet Transmitted ");
          display.display();
          
        } else if ( hopCount <= 0 || hopCount >= MAX_HOPS || !incoming.startsWith("Wide") ){
          Serial.println("Packet Dropped");
          display.clearDisplay();
          display.setCursor(0,0);
          display.print("LoRa Repeater ");
          display.setCursor(0,10);
          display.print("PR   : ");
          display.setCursor(40,10);
          display.print(counter);
          display.setCursor(0,20);
          display.print("RSSI : ");
          display.setCursor(40,20);
          display.print( LoRa.packetRssi() );
          display.setCursor(0,30);
          display.print("SNR  : ");
          display.setCursor(40,30);
          display.print( LoRa.packetSnr() );
          display.setCursor(0,40);
          display.print("Packet Dropped ");
          display.display();
        }
      }
    }
  }
}
