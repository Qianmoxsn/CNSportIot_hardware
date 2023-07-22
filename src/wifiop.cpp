#include "wifiop.h"

/**
 * @description: setup and connect to WiFi
 * @param const char* ssid: WiFi SSID
 * @param const char* password: WiFi password
 * @return none
 */
void setupWifi(const char* ssid, const char* password) {
  delay(10);
  // We start by connecting to a WiFi network
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("");
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
}