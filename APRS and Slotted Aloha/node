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
String dummyData = "Pretend that this is a data received from the sensors ";
String Wide = "Wide1-1 ";

void sendMessage() {
  String packet = Wide;
  packet += NODE;
  packet += dummyData;
  packet += "P#";
  packet += counter;

  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();
}

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

}

void loop() {
  unsigned int currentTime = millis();
  int currentTimeSecond = currentTime/1000;

  if (currentTimeSecond % 2 != 0 && dummyData.length() > 0) {
    counter++;
    sendMessage();
    delay(1000);
    Serial.print("Node 1 Sending Packet #");
    Serial.println(counter);
    Serial.println(currentTimeSecond);
  }
}
