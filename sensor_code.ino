#include <WiFi.h>
#include <HTTPClient.h>

#define WIFI_SSID "TemPuRa"           
#define WIFI_PASSWORD "0804738686"    

#define BOT_TOKEN "8508894947:AAEGA5pAmyH_te_QBPZP8rp7_dOEylue0-A"
#define CHAT_ID "7818715318"

void setup() {
  Serial.begin(115200);
  
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("\nWiFi connected!");
}

void loop() {
  int myID = 1;
  float temp = random(250, 350) / 10.0;
  float hum = random(400, 600) / 10.0;
  float volt = random(300, 330) / 100.0;

  if (WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    // ใช้ POST ส่งข้อมูลแบบ JSON
    http.begin(client, "https://api.telegram.org/bot" + String(BOT_TOKEN) + "/sendMessage");
    http.addHeader("Content-Type", "application/json");

    String jsonPayload = "{\"chat_id\": \"" + String(CHAT_ID) + "\", \"text\": \"ESP32 Sensor Report\\nID: " + String(myID) + "\\nTemp: " + String(temp) + " C\\nHumidity: " + String(hum) + " %\\nVoltage: " + String(volt) + " V\"}";

    Serial.print("Sending message to Telegram... ");
    int httpResponseCode = http.POST(jsonPayload);

    if (httpResponseCode == 200) {
      Serial.println("Success!");
    } else {
      Serial.print("Failed, error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }

  delay(10000);
}
hello my name is Nemo
