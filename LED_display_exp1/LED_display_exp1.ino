#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Define OLED display dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// I2C OLED address
#define OLED_I2C_ADDRESS 0x3C

// Create the SSD1306 display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);

  // Initialize the OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Loop forever if initialization fails
  }

  delay(2000); // Allow the display to initialize
  display.clearDisplay();

  // Display a simulated "multi-color" message
  displaySimulatedColors();
}

void loop() {
  // Scroll simulated "multi-color" text
  displaySimulatedColors();

  display.startscrollright(0x00, 0x0F);
  delay(5000);
  display.stopscroll();
  delay(1000);

  display.startscrollleft(0x00, 0x0F);
  delay(5000);
  display.stopscroll();
  delay(1000);
}

void displaySimulatedColors() {
  // Display "Red" text simulation
  display.setTextSize(4);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("RED");
  display.display();
  delay(1000);

  // Display "Green" text simulation
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("GREEN");
  display.display();
  delay(1000);

  // Display "Blue" text simulation
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("BLUE");
  display.display();
  delay(1000);

  // Draw simulated "multi-color" shapes
  display.clearDisplay();
  display.fillRect(0, 0, 64, 32, SSD1306_WHITE); // Rectangle
  display.fillCircle(96, 32, 15, SSD1306_WHITE); // Circle
  display.display();
  delay(1000);
}
