#include <SPI.h>
#include <LoRa.h>

#define SS 10
#define RST 7
#define DIO0 2
#define SF 7

// LoRa parameters
#define BAND 915E6 // LoRa frequency band
#define NODE "Node 1 "

int counter = 0;
String Data = "pretend this is the fast reading sensor sending a MCU analog current ";
String Wide = "Wide1-1 ";
int current;

void setup() {
  Serial.begin(9600);
  while (!Serial);

  // Initialize LoRa module
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) {
    Serial.println("LoRa initialization failed. Check your connections.");
    while (true);
  }
  LoRa.setSpreadingFactor(SF);
  LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Node_1 Initializing Ok !");

  delay(1000);
}

void sensor(int currentTimeSecond) {

  current = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  // print out the value you read:
  delay(3000);
}

void sendMessage() {
  String packet = Wide;
  packet += NODE;
  packet += Data;
  packet += current;
  packet += " P#";
  packet += counter;

  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();
}

void loop() {
  unsigned long currentTime = millis();
  int currentTimeSecond = currentTime/1000;
  sensor(currentTimeSecond);
  if (currentTimeSecond % 2 == 0 && Data.length() > 0) {
    counter++;
    sendMessage();
    Serial.print("Time : ");
    Serial.println(currentTimeSecond);
    
  }
}
