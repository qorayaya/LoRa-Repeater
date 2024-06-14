#include <SPI.h>
#include <LoRa.h>

#define SS 10
#define RST 7
#define DIO0 2
#define SF 7

#define BAND 915E6
#define NODE "Node 1 "

#define REQUEST_PACKET "RTS"
#define ACK_PACKET "ACK"
#define BUSY "BUSY"

int counter = 0;
int seed = 1234;
String dummyData = "Pretend that this is a data from the sensors like current ";
String Wide = "Wide1-1 ";

void sendMessage(){
  String packet = Wide;
  packet += NODE;
  packet += dummyData;
  packet += "P#";
  packet += counter;
  Serial.println(packet);

  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();
}

void setup() {
  Serial.begin(9600);

  Serial.println("Arduino LoRa CAD Node 1");
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(SF);
  LoRa.setSyncWord(0xF1);
  randomSeed(seed);
}

void loop() {
  unsigned long startTime;
  int randomDelay = random(1000,3000);
  if (counter<100){
  while (true) {
    // Send request to receiver
    Serial.println("Sending request to receiver");
    LoRa.beginPacket();
    LoRa.print(REQUEST_PACKET);
    LoRa.endPacket();

    // Wait for ACK from receiver with timeout
    Serial.println("Waiting for ACK...");
    startTime = millis();
    
    while (millis() - startTime < 5000) {  // Timeout after 5 seconds
      if (LoRa.parsePacket()) {
        String received = "";
        while (LoRa.available()) {
          received += (char)LoRa.read();
        }
        if (received == ACK_PACKET) {
          Serial.println("ACK received, sending data...");
          sendMessage();
          Serial.println(startTime);
          counter++;
          Serial.println("Data sent successfully");
          break; // Exit the inner while loop
        } else if (received == BUSY){
          Serial.println("Receiver is busy. Will retry...");
          break; // Exit the inner while loop
        }
      }
    }

    if (millis() - startTime >= 5000) {
      Serial.println("No ACK received, retrying...");
      Serial.println(startTime);
      delay(randomDelay); // Wait 2 seconds before retrying
    } else {
      // If ACK was received, break the outer while loop
      break;
    }
  }

  delay(5000); 
  }
}
