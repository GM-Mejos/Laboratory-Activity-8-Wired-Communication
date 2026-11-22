#include <Arduino.h>
#include <Wire.h>

const int I2C_SDA_PIN = 21;
const int I2C_SCL_PIN = 22;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("\nI2C Scanner Started");

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  int deviceCount = 0;
  for (byte address = 0x01; address <= 0x7E; address++) {
    Wire.beginTransmission(address);
    byte error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Found device at 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      deviceCount++;
    }
  }

  if (deviceCount == 0) {
    Serial.println("No I2C devices found");
  }
}

void loop() {
}
