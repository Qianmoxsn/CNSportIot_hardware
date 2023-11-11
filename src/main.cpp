#include <Arduino.h>

#include "Mybase64.h"
#include "cameraop.h"
#include "fileop.h"
#include "wifiop.h"
#include "easylight.h"

///// Configurations /////
// Instantiate the netconfig.json from the template and store it in data folder.
String config_file = "/netconfig.json";

// WiFi MQTT Global Variables
String wifi_ssid;
String wifi_password;
String ftp_server;
String ftp_user;
String ftp_pswd;



/// @function: Entry point

void setup() {
  // Time for open COM
  delay(2000);
  setupLights();

  Serial.begin(9600);
  Serial.println("Start");

  if (loadConfig(config_file, wifi_ssid, wifi_password, ftp_server, ftp_user, ftp_pswd)) {
    // setup wifi
    scanfWifi();
    setupWifi(wifi_ssid.c_str(), wifi_password.c_str());
    // setup camera
    setupCamera();
    // setup ftp


    // setup SUCCESS, turn on led
    turnOn(3);
  }
  else {
    // setup FAILED, turn on led
    turnOn(1);
    delay(1000);
    abort();
  }
}

/// @function: Main loop

void loop() {
  camera_fb_t* frame_buffer = esp_camera_fb_get();

  if (frame_buffer) {
    Serial.printf("width: %d, height: %d, buf: 0x%x, len: %d\n", frame_buffer->width, frame_buffer->height, frame_buffer->buf, frame_buffer->len);
    char* input = (char*)frame_buffer->buf;
    char output[base64_enc_len(3)];

    String imageFile = "data:image/jpeg;base64,";
    for (int i = 0; i < frame_buffer->len; i++) {
      base64_encode(output, (input++), 3);
      if (i % 3 == 0) imageFile += urlencode(String(output));
    }
    // clear camera buffer
    esp_camera_fb_return(frame_buffer);
    // FTP upload

  }

  delay(20000);  // [ms]
}
