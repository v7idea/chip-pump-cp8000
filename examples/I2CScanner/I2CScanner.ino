#include <Wire.h>

static void printHexByte(uint8_t value) {
  const char digits[] = "0123456789ABCDEF";
  Serial.print("0x");
  Serial.print(digits[(value >> 4) & 0x0F]);
  Serial.print(digits[value & 0x0F]);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("I2C scanner");
  Serial.println("SDA=D6(GPIO6), SCL=D7(GPIO7), 100kHz");
}

void loop() {
  uint8_t found = 0;

  Serial.println("Scanning...");
  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    if (Wire.endTransmission() == 0) {
      Serial.print("Found ");
      printHexByte(address);
      Serial.println();
      found++;
    }
  }
  Serial.print("Scan done, devices=");
  Serial.println(found);
  delay(3000);
}
