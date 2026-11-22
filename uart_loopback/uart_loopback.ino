#include <Arduino.h>

const int UART_TX_PIN = 17;
const int UART_RX_PIN = 16;

unsigned long lastSend = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, UART_RX_PIN, UART_TX_PIN);
  delay(500);
  Serial.println("UART Loopback Test Started");
}

void loop() {
  if (millis() - lastSend >= 1000) {
    lastSend = millis();
    Serial2.println("PING");
  }

  while (Serial2.available() > 0) {
    char incoming = Serial2.read();
    Serial.write(incoming);
  }
}
