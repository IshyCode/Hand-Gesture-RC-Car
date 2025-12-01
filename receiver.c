#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>




// CE → 7, CSN → 8  (can be changed)
RF24 radio(7, 8);




// MUST MATCH STM32 (5 bytes)
const byte address[5] = {0xE7,0xE7,0xE7,0xE7,0xE7};




void setup() {
  Serial.begin(9600);
  Serial.println("NRF24 Receiver Starting...");




  if (!radio.begin()) {
    Serial.println("NRF24 not responding!");
    while (1);
  }




  // ---- Radio Configuration (must match STM32) ----
  radio.setAutoAck(false);        // STM32 uses no ACK
  radio.setRetries(0, 0);
  radio.setPALevel(RF24_PA_LOW);
  radio.setDataRate(RF24_1MBPS);  // Must match STM32 RF_SETUP
  radio.setChannel(76);           // Must match STM32 RF_CH
  radio.disableDynamicPayloads();  // STM32 sends variable payloads




  radio.openReadingPipe(0, address);
  radio.startListening();




  Serial.println("Receiver Ready. Listening...");
}




void loop() {
  if (radio.available()) {
    char text[32] = {0};




    uint8_t len = radio.getDynamicPayloadSize();
    if (len == 0 || len > 32) {
      // Invalid packet, flush
      radio.flush_rx();
      return;
    }




    radio.read(&text, len);




    Serial.print("Received: ");
    Serial.println(text);
  }
}
