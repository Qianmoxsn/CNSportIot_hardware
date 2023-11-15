#include <Arduino.h>

#include "fileop.h"
#include "mqttop.h"
#include "wifiop.h"
#include <WebSerial.h>

///// Configurations /////
// Instantiate the netconfig.json from the template and store it in data folder.
String config_file = "/netconfig.json";

// WiFi MQTT Global Variables
String wifi_ssid;
String wifi_password;
String mqtt_server;
String mqtt_topic;
int mqtt_port;

// Pins Declaration
const int ledOnBoard = 33;

AsyncWebServer server(80);
/// @function: Entry point

// broadcast Serial message to WebSerial
void broadcastMsg() {
  String msg = Serial.readStringUntil('\n');
  if (msg.length() > 0){
    WebSerial.println(msg);
  }
}

void setup() {
  pinMode(ledOnBoard, OUTPUT);
  digitalWrite(ledOnBoard, HIGH);

  Serial.begin(9600);
  Serial.println("Start");

  if (loadConfig(config_file, wifi_ssid, wifi_password, mqtt_server, mqtt_topic,
    mqtt_port)) {
    scanfWifi();
    setupWifi(wifi_ssid.c_str(), wifi_password.c_str());
    configTime(28800, 0, "ntp.aliyun.com", "time1.cloud.tencent.com", "ntp.ntsc.ac.cn");
    while (!time(nullptr)) {
      delay(500);
      Serial.println("Waiting for time sync...");
    }
    Serial.println("Time synced");
    WebSerial.begin(&server);
    server.begin();
    // setup done, turn on the led
    digitalWrite(ledOnBoard, LOW);
  }
  else {
    abort();
  }
}

/// @function: Main loop

void loop() {
  broadcastMsg();
}
