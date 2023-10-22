#include <Arduino.h>

#include "Mybase64.h"
#include "cameraop.h"
#include "fileop.h"
#include "mqttop.h"
#include "wifiop.h"
#include "easylight.h"

///// Configurations /////
// Instantiate the netconfig.json from the template and store it in data folder.
// String config_file = "/netconfig.json";

// WiFi MQTT Global Variables
// String wifi_ssid;
// String wifi_password;
// String mqtt_server;
// int mqtt_port;


/// @function: Entry point

void setup() {
  setupLights();
  
  Serial.begin(9600);
  Serial.println("Start");
  turnOn(5);
  
  // if (loadConfig(config_file, wifi_ssid, wifi_password, mqtt_server,
  //                mqtt_port)) {
    
    //scanfWifi();
    // setupWifi(wifi_ssid.c_str(), wifi_password.c_str());
    // mqttSetup(mqtt_server.c_str(), mqtt_port);
    setupCamera();
    // setup done, turn on the led
    turnOn(1,3);
  // } else {
  //   abort();
  // }
}

/// @function: Main loop

void loop() {
  // mqttReconnect();
  camera_fb_t* frame_buffer = esp_camera_fb_get();

  if (frame_buffer) {
    Serial.printf("width: %d, height: %d, buf: 0x%x, len: %d\n",
                  frame_buffer->width, frame_buffer->height, frame_buffer->buf,
                  frame_buffer->len);
    char* input = (char*)frame_buffer->buf;
    char output[base64_enc_len(3)];
    String imageFile = "data:image/jpeg;base64,";

    for (int i = 0; i < frame_buffer->len; i++) {
      base64_encode(output, (input++), 3);
      if (i % 3 == 0) imageFile += urlencode(String(output));
    }
    // Serial.println(imageFile);
    esp_camera_fb_return(frame_buffer);

    // mqttPublish(imageFile);
  }

  delay(20000);  // [ms]
  Serial.println("Get it.");
}
