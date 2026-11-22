#include <Arduino.h>
#include <SPI.h>

const int SPI_SCK_PIN  = 14;
const int SPI_MOSI_PIN = 13;
const int SPI_MISO_PIN = 26;
const int SPI_CS_PIN   = 4;

SPIClass spi(HSPI);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("SPI Loopback Test Started");

  pinMode(SPI_CS_PIN, OUTPUT);
  digitalWrite(SPI_CS_PIN, HIGH);

  spi.begin(SPI_SCK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN, SPI_CS_PIN);
}

void loop() {
  byte txByte = 0xA5;

  spi.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE0));
  digitalWrite(SPI_CS_PIN, LOW);
  byte rxByte = spi.transfer(txByte);
  digitalWrite(SPI_CS_PIN, HIGH);
  spi.endTransaction();

  Serial.print("Sent 0xA5, received 0x");
  if (rxByte < 0x10) Serial.print("0");
  Serial.println(rxByte, HEX);

  delay(1000);
}
