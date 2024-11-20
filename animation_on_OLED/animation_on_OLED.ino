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
  display.display();
}

void loop() {
  // Scroll a rectangle across the screen
  for (int x = 0; x < SCREEN_WIDTH; x++) {
    display.clearDisplay();
    display.fillRect(x, 20, 30, 20, SSD1306_WHITE); // Rectangle
    display.setCursor(x, 50);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.println("Moving!");
    display.display();
    delay(50);
  }

  delay(1000);

  // Scroll text
  for (int x = SCREEN_WIDTH; x > -50; x--) {
    display.clearDisplay();
    display.setCursor(x, 30);
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.println("Scroll");
    display.display();
    delay(50);
  }
}
