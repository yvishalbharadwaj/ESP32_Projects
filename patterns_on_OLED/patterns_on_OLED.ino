#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_I2C_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  displayPatterns();
}

void loop() {
}

void displayPatterns() {
  // Draw concentric circles
  for (int r = 5; r < 32; r += 5) {
    display.drawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, r, SSD1306_WHITE);
  }

  // Add a triangle in the center
  display.drawTriangle(40, 20, 80, 20, 60, 50, SSD1306_WHITE);

  // Add some text
  display.setTextSize(1);
  display.setCursor(10, SCREEN_HEIGHT - 10);
  display.setTextColor(SSD1306_WHITE);
  display.println("Cool Patterns");
  display.display();
}
