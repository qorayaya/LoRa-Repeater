#include <SPI.h>
#include <LoRa.h>

#define SS 10
#define RST 7
#define DIO0 2
#define SF 7

#define BAND 915E6
#define NODE "Node 1 "

int seed = 1234;

//packet counter
int counter = 0;
String Data = "pretend this is the fast reading sensor sending a MCU analog voltage ";
String Wide = "Wide1-1 ";
float voltage;

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
  sensor();
   if (Data){
    int randomDelay = random(0, 1000);
    Serial.print("Node 1 sending packet with delay : ");
    Serial.print(randomDelay);
    Serial.print(" Packet #");
    Serial.println(counter);
    delay(randomDelay);
    counter++;
    sendMessage();
    } 
} 

void sensor() {

  int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
  voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
  delay(2000);

}

void sendMessage(){
  String packet = Wide;
  packet += NODE;
  packet += Data;
  packet += voltage;
  packet += " P#";
  packet += counter;

  LoRa.beginPacket();
  LoRa.print(packet);
  LoRa.endPacket();
}
