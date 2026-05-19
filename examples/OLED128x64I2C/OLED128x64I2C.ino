#include <Wire.h>

static const uint8_t OLED_ADDR = 0x3C;
static const uint8_t OLED_WIDTH = 128;
static const uint8_t OLED_HEIGHT = 64;
static const uint8_t OLED_PAGES = OLED_HEIGHT / 8;
static const uint8_t OLED_COLUMN_OFFSET = 2; // 1.3 inch modules are often SH1106 with 132 columns.

static uint8_t frame[OLED_WIDTH * OLED_PAGES];

static void oledWriteCommands(const uint8_t *commands, uint8_t count) {
  while (count > 0) {
    uint8_t chunk = count > 30 ? 30 : count;
    Wire.beginTransmission(OLED_ADDR);
    Wire.write(0x00);
    Wire.write(commands, chunk);
    Wire.endTransmission();
    commands += chunk;
    count -= chunk;
  }
}

static void oledCommand(uint8_t command) {
  oledWriteCommands(&command, 1);
}

static void oledInit() {
  static const uint8_t initCommands[] = {
    0xAE,       // Display off
    0xD5, 0x80, // Clock divide
    0xA8, 0x3F, // Multiplex for 64 rows
    0xD3, 0x00, // Display offset
    0x40,       // Start line
    0x8D, 0x14, // Charge pump on
    0xAD, 0x8B, // SH1106 DC-DC on; ignored by many SSD1306 modules
    0xA1,       // Segment remap
    0xC8,       // COM scan direction
    0xDA, 0x12, // COM pins for 128x64
    0x81, 0xCF, // Contrast
    0xD9, 0xF1, // Pre-charge
    0xDB, 0x40, // VCOMH
    0xA4,       // Resume RAM display
    0xA6,       // Normal display
    0xAF        // Display on
  };

  delay(100);
  oledWriteCommands(initCommands, sizeof(initCommands));
}

static void oledClearBuffer() {
  for (uint16_t i = 0; i < sizeof(frame); i++) {
    frame[i] = 0;
  }
}

static void oledDisplay() {
  for (uint8_t page = 0; page < OLED_PAGES; page++) {
    uint8_t column = OLED_COLUMN_OFFSET;
    uint8_t pageCommands[] = {
      (uint8_t)(0xB0 | page),
      (uint8_t)(0x00 | (column & 0x0F)),
      (uint8_t)(0x10 | (column >> 4))
    };
    oledWriteCommands(pageCommands, sizeof(pageCommands));

    for (uint8_t x = 0; x < OLED_WIDTH; x += 16) {
      Wire.beginTransmission(OLED_ADDR);
      Wire.write(0x40);
      Wire.write(&frame[(uint16_t)page * OLED_WIDTH + x], 16);
      Wire.endTransmission();
    }
  }
}

static void drawPixel(int x, int y, bool color = true) {
  if (x < 0 || x >= OLED_WIDTH || y < 0 || y >= OLED_HEIGHT) {
    return;
  }

  uint16_t index = (uint16_t)(y / 8) * OLED_WIDTH + x;
  uint8_t mask = (uint8_t)(1U << (y & 7));
  if (color) {
    frame[index] |= mask;
  } else {
    frame[index] &= (uint8_t)~mask;
  }
}

static void drawLine(int x0, int y0, int x1, int y1) {
  int dx = x1 > x0 ? x1 - x0 : x0 - x1;
  int sx = x0 < x1 ? 1 : -1;
  int dy = y1 > y0 ? y0 - y1 : y1 - y0;
  int sy = y0 < y1 ? 1 : -1;
  int err = dx + dy;

  while (true) {
    drawPixel(x0, y0);
    if (x0 == x1 && y0 == y1) {
      break;
    }
    int e2 = 2 * err;
    if (e2 >= dy) {
      err += dy;
      x0 += sx;
    }
    if (e2 <= dx) {
      err += dx;
      y0 += sy;
    }
  }
}

static void drawRect(int x, int y, int w, int h) {
  drawLine(x, y, x + w - 1, y);
  drawLine(x, y + h - 1, x + w - 1, y + h - 1);
  drawLine(x, y, x, y + h - 1);
  drawLine(x + w - 1, y, x + w - 1, y + h - 1);
}

static void fillRect(int x, int y, int w, int h) {
  for (int yy = y; yy < y + h; yy++) {
    for (int xx = x; xx < x + w; xx++) {
      drawPixel(xx, yy);
    }
  }
}

static const uint8_t *glyphFor(char value) {
  static const uint8_t blank[5] = {0, 0, 0, 0, 0};
  static const uint8_t dash[5] = {0x08, 0x08, 0x08, 0x08, 0x08};
  static const uint8_t colon[5] = {0, 0x36, 0x36, 0, 0};
  static const uint8_t slash[5] = {0x20, 0x10, 0x08, 0x04, 0x02};
  static const uint8_t xchar[5] = {0x63, 0x14, 0x08, 0x14, 0x63};
  static const uint8_t dot[5] = {0, 0x60, 0x60, 0, 0};
  static const uint8_t zero[5] = {0x3E, 0x51, 0x49, 0x45, 0x3E};
  static const uint8_t one[5] = {0x00, 0x42, 0x7F, 0x40, 0x00};
  static const uint8_t two[5] = {0x42, 0x61, 0x51, 0x49, 0x46};
  static const uint8_t three[5] = {0x21, 0x41, 0x45, 0x4B, 0x31};
  static const uint8_t four[5] = {0x18, 0x14, 0x12, 0x7F, 0x10};
  static const uint8_t five[5] = {0x27, 0x45, 0x45, 0x45, 0x39};
  static const uint8_t six[5] = {0x3C, 0x4A, 0x49, 0x49, 0x30};
  static const uint8_t seven[5] = {0x01, 0x71, 0x09, 0x05, 0x03};
  static const uint8_t eight[5] = {0x36, 0x49, 0x49, 0x49, 0x36};
  static const uint8_t nine[5] = {0x06, 0x49, 0x49, 0x29, 0x1E};
  static const uint8_t a[5] = {0x7E, 0x11, 0x11, 0x11, 0x7E};
  static const uint8_t letterC[5] = {0x3E, 0x41, 0x41, 0x41, 0x22};
  static const uint8_t d[5] = {0x7F, 0x41, 0x41, 0x22, 0x1C};
  static const uint8_t e[5] = {0x7F, 0x49, 0x49, 0x49, 0x41};
  static const uint8_t i[5] = {0x00, 0x41, 0x7F, 0x41, 0x00};
  static const uint8_t l[5] = {0x7F, 0x40, 0x40, 0x40, 0x40};
  static const uint8_t o[5] = {0x3E, 0x41, 0x41, 0x41, 0x3E};
  static const uint8_t p[5] = {0x7F, 0x09, 0x09, 0x09, 0x06};
  static const uint8_t r[5] = {0x7F, 0x09, 0x19, 0x29, 0x46};
  static const uint8_t s[5] = {0x46, 0x49, 0x49, 0x49, 0x31};
  static const uint8_t t[5] = {0x01, 0x01, 0x7F, 0x01, 0x01};

  switch (value) {
    case ' ': return blank;
    case '-': return dash;
    case ':': return colon;
    case '/': return slash;
    case '.': return dot;
    case 'x': return xchar;
    case '0': return zero;
    case '1': return one;
    case '2': return two;
    case '3': return three;
    case '4': return four;
    case '5': return five;
    case '6': return six;
    case '7': return seven;
    case '8': return eight;
    case '9': return nine;
    case 'A': return a;
    case 'C': return letterC;
    case 'D': return d;
    case 'E': return e;
    case 'I': return i;
    case 'L': return l;
    case 'O': return o;
    case 'P': return p;
    case 'R': return r;
    case 'S': return s;
    case 'T': return t;
    default: return blank;
  }
}

static void drawChar(int x, int y, char c, uint8_t scale) {
  const uint8_t *glyph = glyphFor(c);
  for (uint8_t col = 0; col < 5; col++) {
    for (uint8_t row = 0; row < 7; row++) {
      if (glyph[col] & (1U << row)) {
        fillRect(x + col * scale, y + row * scale, scale, scale);
      }
    }
  }
}

static void drawText(int x, int y, const char *text, uint8_t scale = 1) {
  while (*text) {
    drawChar(x, y, *text++, scale);
    x += 6 * scale;
  }
}

static void drawDemo(uint8_t frameNumber) {
  oledClearBuffer();
  drawRect(0, 0, OLED_WIDTH, OLED_HEIGHT);
  drawText(15, 7, "CP8000", 2);
  drawText(20, 29, "OLED I2C", 1);
  drawText(14, 42, "128x64 / 0x3C", 1);

  drawRect(10, 54, 108, 7);
  uint8_t width = (uint8_t)((frameNumber % 100) + 1);
  fillRect(12, 56, width, 3);
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("OLED 128x64 I2C demo");
  Serial.println("Address 0x3C, SDA=D6(GPIO6), SCL=D7(GPIO7)");

  oledInit();
  oledClearBuffer();
  oledDisplay();
}

void loop() {
  static uint8_t frameNumber = 0;
  static uint8_t heartbeat = 0;
  drawDemo(frameNumber++);
  oledDisplay();
  if ((heartbeat++ % 25) == 0) {
    Serial.println("OLED refresh");
  }
  delay(80);
}
