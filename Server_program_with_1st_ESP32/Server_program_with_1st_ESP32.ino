//This is Server code also use Client code with other ESP32

#include <WiFi.h>
#include <WebServer.h>

// WiFi Credentials
const char* ssid = "Babbu_Home";         // Replace with your WiFi SSID
const char* password = "Babuchitti_33"; // Replace with your WiFi password

// Create a web server object on port 80
WebServer server(80);

bool clientConnected = false; // Tracks client connection status

// Root page handler
void handleRoot() {
  // HTML content with a larger ASCII art smiley face
  String html = "<!DOCTYPE html>";
  html += "<html>";
  html += "<head><title>ESP32 Server</title></head>";
  html += "<body style='text-align: center; font-family: Courier;'>";
  html += "<h1>ESP32 Server Status</h1>";

  if (clientConnected) {
    html += "<pre>";
    html += "      *****         *****      \n";
    html += "   **     **     **     **   \n";
    html += "  *         *   *         *  \n";
    html += " *   O   O   * *   O   O   * \n";
    html += " *     ^     * *     ^     * \n";
    html += "  *   \\___/   *   \\___/   *  \n";
    html += "   **         ***         **   \n";
    html += "      *****         *****      \n";
    html += "</pre>";
    html += "<p>Client Connected!</p>";
  } else {
    html += "<pre>";
    html += "      *****         *****      \n";
    html += "   **     **     **     **   \n";
    html += "  *         *   *         *  \n";
    html += " *   -   -   * *   -   -   * \n";
    html += " *     .     * *     .     * \n";
    html += "  *   _____   *   _____   *  \n";
    html += "   **         ***         **   \n";
    html += "      *****         *****      \n";
    html += "</pre>";
    html += "<p>Waiting for Client...</p>";
  }

  html += "</body>";
  html += "</html>";

  // Send the HTML response to the client
  server.send(200, "text/html", html);
}

// Client connection handler
void handleClientConnect() {
  clientConnected = true; // Update the connection status
  server.send(200, "text/plain", "Client Connected!");
  Serial.println("Client has connected!");
}

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

  // Define routes
  server.on("/", handleRoot);                  // Root URL
  server.on("/connect", handleClientConnect); // Client connection endpoint

  // Start the server
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  // Handle incoming client requests
  server.handleClient();
}
