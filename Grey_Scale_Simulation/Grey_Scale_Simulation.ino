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
  grayscaleSimulation();
}

void loop() {
}

void grayscaleSimulation() {
  for (int i = 0; i < 3; i++) {
    display.clearDisplay();

    // Dark shade
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
      for (int x = 0; x < SCREEN_WIDTH; x += 2) {
        if (y % 2 == 0) display.drawPixel(x, y, SSD1306_WHITE);
      }
    }
    display.display();
    delay(1000);

    // Medium shade
    display.clearDisplay();
    for (int y = 0; y < SCREEN_HEIGHT; y++) {
      for (int x = 0; x < SCREEN_WIDTH; x++) {
        if ((x + y) % 2 == 0) display.drawPixel(x, y, SSD1306_WHITE);
      }
    }
    display.display();
    delay(1000);

    // Light shade
    display.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, SSD1306_WHITE);
    display.display();
    delay(1000);
  }
}
