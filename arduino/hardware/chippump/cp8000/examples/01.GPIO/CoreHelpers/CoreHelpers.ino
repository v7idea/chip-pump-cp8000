void setup() {
  Serial.begin(115200);
}

void loop() {
  byte flags = 0;
  bitSet(flags, 2);
  bitWrite(flags, 4, bitRead(flags, 2));
  bitToggle(flags, 2);
  bitClear(flags, 4);

  uint16_t packed = word(0x12, 0x34);
  byte low = lowByte(packed);
  byte high = highByte(packed);

  long mapped = map(5, 0, 10, 0, 100);
  long clipped = constrain(mapped, 20, 80);
  long squared = sq(9);
  long roundedDegrees = round(degrees(radians(90)));

  Serial.println("CP8000 CoreHelpers");
  Serial.print("flags=");
  Serial.println(flags);
  Serial.print("word=");
  Serial.println(packed);
  Serial.print("low=");
  Serial.println(low);
  Serial.print("high=");
  Serial.println(high);
  Serial.print("clipped=");
  Serial.println(clipped);
  Serial.print("sq=");
  Serial.println(squared);
  Serial.print("degrees=");
  Serial.println(roundedDegrees);

  delay(2000);
}
