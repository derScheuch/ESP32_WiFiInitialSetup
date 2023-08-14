
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <EEPROM.h>

const char* defaultSSID = "ESP32";
const char* defaultPassword = "Hello";

WebServer server(80);

void setup() {
  Serial.begin(115200);

  // Initialize EEPROM
  EEPROM.begin(512);

  // Attempt to connect to WiFi using EEPROM data
  connectToWiFi();

  // If connection couldn't be established, start own AP
  if (WiFi.status() != WL_CONNECTED) {
    startOwnAP();
  }

  // Set up the web server
  server.on("/", HTTP_GET, handleRoot);
  server.on("/save", HTTP_POST, handleSave);

  server.begin();
}

void loop() {
  server.handleClient();
  // Add your loop logic here
}

void handleRoot() {
  String html = "<html><body>";
  html += "<form action='/save' method='POST'>";
  html += "SSID: <input type='text' name='ssid'><br>";
  html += "Password: <input type='password' name='password'><br>";
  html += "<input type='submit' value='Save'>";
  html += "</form>";
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleSave() {
  String newSSID = server.arg("ssid");
  String newPassword = server.arg("password");

  // Save new SSID and password to EEPROM
  saveCredentials(newSSID, newPassword);

  // Connect to the new WiFi network
  connectToWiFi();

  server.send(200, "text/plain", "Data saved and connected to WiFi.");
}

void saveCredentials(const String& ssid, const String& password) {
  // Write data to EEPROM
  EEPROM.writeString(0, ssid);
  EEPROM.writeString(ssid.length() + 1, password);
  EEPROM.commit();
}

void connectToWiFi() {
  // Read SSID and password from EEPROM
  String storedSSID = EEPROM.readString(0);
  String storedPassword = EEPROM.readString(storedSSID.length() + 1);

  // Check if valid data is stored
  if (storedSSID.length() == 0 || storedPassword.length() == 0) {
    Serial.println("No valid network data stored.");
    return;
  }

  // Connect to the stored WiFi network
  WiFi.begin(storedSSID.c_str(), storedPassword.c_str());

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("Successfully connected to WiFi. IP Address: " + WiFi.localIP().toString());
  } else {
    Serial.println("Could not establish WiFi connection.");
  }
}

void startOwnAP() {
  Serial.println("Starting own WiFi network...");

  WiFi.softAP(defaultSSID, defaultPassword);

  IPAddress apIP(192, 168, 1, 1);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));

  Serial.println("Own WiFi network started. IP Address: " + WiFi.softAPIP().toString());
}