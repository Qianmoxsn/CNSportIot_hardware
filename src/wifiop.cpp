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
  // IP
  Serial.println("");
  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());
  // MAC
  uint8_t macAddr[6];
  WiFi.macAddress(macAddr);
  Serial.printf("MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);
}

/**
 * @description: scan WiFi
 * @param none
 * @return none
*/
void scanfWifi() {
  int numberOfNetworks = WiFi.scanNetworks();
  Serial.print("Networks found:");
  Serial.println(numberOfNetworks);
  for (int i = 0; i < numberOfNetworks; i++) {
    Serial.print("Net: ");
    Serial.print(WiFi.SSID(i));
    Serial.print("   Signal: ");
    Serial.print(WiFi.RSSI(i));
    Serial.println(" dBm");
  }
  Serial.println("-----------------------");
}

/**
 * @description: (re)connect to WiFi
 * @param const char* ssid: WiFi SSID
 * @param const char* password: WiFi password
 * @return none
 */
void reconWifi(const char* ssid, const char* password) {
  if (WiFi.status() != WL_CONNECTED) {
    setupWifi(ssid, password);
    Serial.println("WiFi Reconnected");
  }
}

/**
 * @description: sync time from NTP server
 * @param none
 * @return none
*/
void syncTime() {
  configTime(28800, 0, "ntp.aliyun.com", "time1.cloud.tencent.com", "ntp.ntsc.ac.cn");
  while (!time(nullptr)) {
    delay(500);
    Serial.println("Waiting for time sync...");
  }
  Serial.println("Time synced");
}