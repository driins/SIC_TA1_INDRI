#include <WiFi.h>
#include <HTTPClient.h>
#include "DHT.h"
#define DHT11PIN 13

DHT dht(DHT11PIN, DHT11);

const char* ssid = "Kai"; // Change to ssid WiFi connection
const char* password = "yayayiya65678"; // Change to password WiFi connection
const char* server_url = "http://192.168.84.44:5000/sensor/data"; // Change to Flask server's running IP (cek di VSCode)
unsigned long lastMsg = 0;
float temp = 0;
float hum = 0;

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);
  Serial.println("Starting setup...");
  setup_wifi();
  dht.begin();
  Serial.println("Setup completed.");

  // Test connection to the server
  WiFiClient client;
  if (client.connect("192.168.84.44", 5000)) {  // Check and make sure this IP matches with Flask server's IP
    Serial.println("Connected to server for connection test");
    client.println("POST /sensor/data HTTP/1.1");
    client.println("Host: 192.168.84.44");
    client.println("Content-Type: application/json");
    client.println("Content-Length: 35");
    client.println();
    client.println("{\"temperature\": 27.90, \"humidity\": 92.0}");
    client.println();

    while (client.connected() || client.available()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }

    client.stop();
  } else {
    Serial.println("Connection to server failed");
  }
}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected. Reconnecting...");
    setup_wifi();
  }

  unsigned long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    float humi = dht.readHumidity();
    float temp = dht.readTemperature();

    if (isnan(humi) || isnan(temp)) {
      Serial.println("Failed to read from DHT sensor!");
      return;
    }

    HTTPClient http;
    http.begin(server_url);
    http.addHeader("Content-Type", "application/json");

    String payload = "{\"temperature\": " + String(temp, 2) + ", \"humidity\": " + String(humi, 1) + "}";
    Serial.print("Sending data to server: ");
    Serial.println(payload);

    int httpResponseCode = http.POST(payload);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
      Serial.print("Response from server: ");
      Serial.println(response);
    } else {
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
    }

    http.end();

    Serial.print("Temperature: ");
    Serial.println(temp);
    Serial.print("Humidity: ");
    Serial.println(humi);
  }
}
