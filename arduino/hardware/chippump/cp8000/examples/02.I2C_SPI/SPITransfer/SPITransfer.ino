#include <SPI.h>

static void printHexByte(uint8_t value) {
  const char digits[] = "0123456789ABCDEF";
  Serial.print("0x");
  Serial.print(digits[(value >> 4) & 0x0F]);
  Serial.print(digits[value & 0x0F]);
}

void setup() {
  Serial.begin(115200);
  SPI.begin();
  Serial.println("SPI transfer test");
  Serial.println("Pins: NCS=D0, SCK=D1, MOSI=D2, MISO=D3");
  Serial.println("For loopback validation, connect D2(MOSI) to D3(MISO).");
}

void loop() {
  static uint8_t tx = 0x55;
  uint8_t rx = SPI.transfer(tx);
  Serial.print("TX=");
  printHexByte(tx);
  Serial.print(" RX=");
  printHexByte(rx);
  Serial.println();
  tx ^= 0xFF;
  delay(1000);
}
