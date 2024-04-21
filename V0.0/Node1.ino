#include <SPI.h>
#include <LoRa.h>

#define SS 10
#define RST 7
#define DIO0 2
#define SF 7

#define BAND 915E6
#define NODE "1"

//packet counter
int counter = 0;

void setup() {
  //initialize Serial Monitor
  Serial.begin(9600);
  
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(SF);
  
  Serial.println("LoRa Node_1 Initializing Ok !");

  delay(1000);
}

void loop() {
   
  Serial.print("Node 1 ");
  Serial.print("Sending packet: ");
  Serial.println(counter);

  String packet = "Wide2-2 V0.0 test P#";
  packet += counter;
  packet += " Node ";
  packet += NODE;


  //Send LoRa packet to receiver
  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();
  
  counter++;
  
  //delay(60000);
  delay(30000);
}
