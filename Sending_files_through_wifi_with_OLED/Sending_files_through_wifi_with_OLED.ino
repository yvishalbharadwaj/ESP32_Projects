#include <WiFi.h>
#include <WebServer.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPIFFS.h>

// Wi-Fi credentials
const char* ssid = "ESP32_File_Transfer";
const char* password = "12345678";

// Create a web server on port 80
WebServer server(80);

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// HTML form for file upload
const char* uploadForm = R"rawliteral(
<!DOCTYPE html>
<html>
  <head>
    <title>ESP32 File Transfer</title>
  </head>
  <body>
    <h1>File Upload</h1>
    <form method="POST" action="/upload" enctype="multipart/form-data">
      <input type="file" name="file">
      <button type="submit">Upload</button>
    </form>
    <a href="/download">Download File</a>
  </body>
</html>
)rawliteral";

// Initialize Wi-Fi and file system
void setup() {
  Serial.begin(115200);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED initialization failed");
    for (;;);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("Starting...");
  display.display();

  // Initialize SPIFFS
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount SPIFFS");
    SPIFFS.format();
    display.clearDisplay();
    display.println("SPIFFS Mount Failed");
    display.display();
    return;
  }

  // Start Wi-Fi in Access Point mode
  WiFi.softAP(ssid, password);
  Serial.println("WiFi started");
  Serial.print("IP address: ");
  Serial.println(WiFi.softAPIP());

  display.clearDisplay();
  display.println("WiFi started");
  display.println(WiFi.softAPIP().toString());
  display.display();

  // Define server routes
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", uploadForm);
  });

  server.on("/upload", HTTP_POST, []() {
    server.send(200, "text/plain", "File Uploaded Successfully");
    displayMessage("File Uploaded!");
  }, handleFileUpload);

  server.on("/download", HTTP_GET, []() {
    File file = SPIFFS.open("/uploaded_file", "r");
    if (!file) {
      server.send(404, "text/plain", "File not found");
      displayMessage("File Not Found");
      return;
    }
    server.streamFile(file, "application/octet-stream");
    file.close();
    displayMessage("File Downloaded!");
  });

  server.begin();
  Serial.println("HTTP server started");
  displayMessage("Server Started!");
}

void loop() {
  server.handleClient();
}

// Handle file upload
void handleFileUpload() {
  HTTPUpload& upload = server.upload();
  if (upload.status == UPLOAD_FILE_START) {
    Serial.printf("Uploading file: %s\n", upload.filename.c_str());
    File file = SPIFFS.open("/uploaded_file", "w");
    if (!file) {
      Serial.println("Failed to open file for writing");
      displayMessage("Upload Failed!");
      return;
    }
    file.close();
  } else if (upload.status == UPLOAD_FILE_WRITE) {
    File file = SPIFFS.open("/uploaded_file", "a");
    if (file) {
      file.write(upload.buf, upload.currentSize);
      file.close();
    }
  } else if (upload.status == UPLOAD_FILE_END) {
    Serial.printf("File upload complete: %s\n", upload.filename.c_str());
  }
}

// Display a message on the OLED
void displayMessage(const char* message) {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println(message);
  display.display();
}
