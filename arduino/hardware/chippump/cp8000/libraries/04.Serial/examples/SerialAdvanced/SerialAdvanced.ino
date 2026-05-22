class Label : public Printable {
public:
  size_t printTo(Print &p) const override {
    return p.print("CP8000-Printable");
  }
};

static Label label;

void setup() {
  Serial.begin(115200, SERIAL_8N1);
  Serial.setTimeout(120);

  while (!Serial) {
  }

  Serial.println("CP8000 SerialAdvanced");
  Serial.print("HEX=");
  Serial.println(255, HEX);
  Serial.print("BIN=");
  Serial.println(5, BIN);
  Serial.print("FLOAT=");
  Serial.println(3.14159, 3);
  Serial.print("PRINTABLE=");
  Serial.println(label);
  Serial.println("Send: 123 45.67 hello");
}

void loop() {
  if (Serial.available() <= 0) {
    delay(20);
    return;
  }

  int first = Serial.peek();
  Serial.print("peek=");
  Serial.println(first);

  Serial.println("parseInt...");
  long whole = Serial.parseInt();
  Serial.println("parseFloat...");
  float decimal = Serial.parseFloat();
  Serial.println("readBytesUntil...");
  char text[16] = {0};
  size_t count = Serial.readBytesUntil('\n', text, sizeof(text) - 1);
  String line = String(text);
  line += "-String";

  Serial.print("int=");
  Serial.println(whole);
  Serial.print("float=");
  Serial.println(decimal, 2);
  Serial.print("bytes=");
  Serial.println((unsigned int)count);
  Serial.print("text=");
  Serial.println(text);
  Serial.print("string=");
  Serial.println(line);
  Serial.flush();
}
