//this is Client code aklso use Server code with other ESP32

#include <WiFi.h>
#include <HTTPClient.h>

// WiFi Credentials
const char* ssid = "Babbu_Home";         // Replace with your WiFi SSID
const char* password = "Babuchitti_33"; // Replace with your WiFi password

// Server IP address
const char* serverIP = "192.168.0.69"; // Replace with the ESP32 server's IP address

void setup() {
  Serial.begin(115200);

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    // Send GET request to the server's "/connect" endpoint
    String url = String("http://") + serverIP + "/connect";
    http.begin(url);

    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("Connected to server: " + String(httpCode));
      Serial.println("Response: " + http.getString());
    } else {
      Serial.println("Error connecting to server");
    }

    http.end();
  }

  delay(10000); // Repeat every 10 seconds
}
