#include <SPI.h>
#include <LoRa.h>

#define SS 10
#define RST 7
#define DIO0 2
#define SF 7

#define BAND 915E6
#define NODE "Node 1 "

int seed = 3521;

//packet counter
int counter = 0;

String dummyData = "Pretend that this is a data from the sensors ";
String Wide = "Wide2-2 ";

void sendMessage(){
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
  //initialize Serial Monitor
  Serial.begin(9600);
  randomSeed(seed);
  
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  if (!LoRa.begin(BAND)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setSpreadingFactor(SF);
  LoRa.setSyncWord(0xF1);
  Serial.println("LoRa Node_1 Initializing Ok !");

}

void loop() {

  if (dummyData){
    int randomDelay = random(1000, 3000);
    Serial.print("Node 1 sending packet with delay : ");
    Serial.print(randomDelay);
    Serial.print(" Packet #");
    Serial.println(counter);
    delay(randomDelay);
    counter++;
    sendMessage();
  }

} 

