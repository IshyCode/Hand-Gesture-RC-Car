#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


RF24 radio(7, 8);   // CE, CSN
const byte address[6] = "00001";


void setup() {
  Serial.begin(115200);   // Must match STM32 baud rate
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_LOW);
  radio.stopListening();
}


void loop() {
  if (Serial.available()) {
    char cmd = Serial.read();
    radio.write(&cmd, sizeof(cmd));


    // Debug print
    Serial.print("Sent over RF: ");
    Serial.println(cmd);
  }
}
