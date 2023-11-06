#include <Arduino.h>

#include "Mybase64.h"
#include "cameraop.h"
#include "fileop.h"
#include "mqttop.h"
#include "wifiop.h"

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

/// @function: Entry point

void setup() {
  pinMode(ledOnBoard, OUTPUT);
  digitalWrite(ledOnBoard, HIGH);
  Serial.begin(9600);
  Serial.println("Start");

  if (loadConfig(config_file, wifi_ssid, wifi_password, mqtt_server, mqtt_topic,
    mqtt_port)) {
    scanfWifi();
    setupWifi(wifi_ssid.c_str(), wifi_password.c_str());
    mqttSetup(mqtt_server.c_str(), mqtt_port);
    setupCamera();
    // setup done, turn on the led
    digitalWrite(ledOnBoard, LOW);
  }
  else {
    abort();
  }
}

/// @function: Main loop

void loop() {
  mqttReconnect();
  
  camera_fb_t* frame_buffer = esp_camera_fb_get();

  if (frame_buffer) {
    Serial.printf("width: %d, height: %d, buf: 0x%x, len: %d\n",
      frame_buffer->width, frame_buffer->height, frame_buffer->buf,frame_buffer->len);
    char* input = (char*)frame_buffer->buf;
    char output[base64_enc_len(3)];
    String imageFile = "data:image/jpeg;base64,";

    for (int i = 0; i < frame_buffer->len; i++) {
      base64_encode(output, (input++), 3);
      if (i % 3 == 0) imageFile += urlencode(String(output));
    }
    // 释放buffer
    esp_camera_fb_return(frame_buffer);

    int mqtt_err = mqttPublish(mqtt_topic, imageFile);
    if (mqtt_err == 1) {
      Serial.println("MQTT_BEGIN_FAILED");
    }
    else if (mqtt_err == 2) {
      Serial.println("MQTT_END_FAILED");
    }
    else {
      Serial.println("MQTT_PUBLISH_SUCCESS");
    }
  }
  Serial.print("mqttLoop: ");
  Serial.println(mqttLoop());
  delay(30000);  // [ms]
  // Serial.println("Get it.");
}
