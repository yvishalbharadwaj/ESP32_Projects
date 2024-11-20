//this program will show the LED glowing on the OLED display like RED for red LED, same for green and yellow

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// OLED Display Dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_I2C_ADDRESS 0x3C

// Create an SSD1306 display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// LED Pins
#define GREEN_LED 25
#define RED_LED 26
#define YELLOW_LED 27

void setup() {
  // Initialize Serial Communication
  Serial.begin(115200);

  // Initialize the OLED Display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Stop if initialization fails
  }

  // Initialize LED Pins
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);

  // Clear OLED Display
  display.clearDisplay();
}

void loop() {
  // Display Green and Turn on Green LED
  displayColor("GREEN", SSD1306_WHITE);
  digitalWrite(GREEN_LED, HIGH);
  delay(500);
  digitalWrite(GREEN_LED, LOW);

  // Display Red and Turn on Red LED
  displayColor("RED", SSD1306_WHITE);
  digitalWrite(RED_LED, HIGH);
  delay(500);
  digitalWrite(RED_LED, LOW);

  // Display Yellow and Turn on Yellow LED
  displayColor("YELLOW", SSD1306_WHITE);
  digitalWrite(YELLOW_LED, HIGH);
  delay(500);
  digitalWrite(YELLOW_LED, LOW);
}

void displayColor(const char* colorText, uint16_t textColor) {
  // Clear the OLED Display
  display.clearDisplay();

  // Set text properties
  display.setTextSize(2); // Larger Text
  display.setTextColor(textColor); // White (since it's monochrome)
  display.setCursor(10, 20); // Centered-ish text

  // Display the text
  display.println(colorText);
  display.display();
}
