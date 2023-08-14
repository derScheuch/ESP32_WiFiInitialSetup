# ESP32 WiFi Configuration and Access Point

This Arduino program is designed for the ESP32 microcontroller. It provides functionality to connect to a WiFi network using stored SSID and password information in the EEPROM memory. If the stored WiFi information is not available or the connection cannot be established, the ESP32 creates its own WiFi Access Point (AP) named "ESP32" with the password "Hello". You can then use this AP to configure WiFi settings via a web interface.

## Instructions

1. **Installation:** Make sure you have the necessary libraries installed in your Arduino IDE: WiFi.h, WiFiClient.h, and WebServer.h.

2. **Flash the ESP32:** Upload the provided sketch to your ESP32 using the Arduino IDE.

3. **Connecting to WiFi:**
   - If valid WiFi credentials are stored in the EEPROM, the ESP32 will attempt to connect to the stored network.
   - If the connection cannot be established, the ESP32 will start its own Access Point (AP) with SSID "ESP32" and password "Hello".

4. **Configuring WiFi:**
   - When connected to the ESP32's AP, open a web browser and navigate to http://192.168.1.1.
   - You will be presented with a form where you can input the SSID and password of the desired WiFi network.
   - After submitting the form, the ESP32 will attempt to connect to the specified network using the provided credentials.
   - If successful, the network information will be stored in the EEPROM for future connections.

5. **Serial Output:** The ESP32 will provide serial output indicating its status, including connection attempts and IP addresses.

## Note

- This is a basic example and should be extended for production use.
- Ensure you handle errors and edge cases properly in a real-world application.
- The EEPROM library used here might not be the most efficient choice; you may consider using the Preferences library for ESP32.

Feel free to modify and adapt the code to suit your specific needs.
