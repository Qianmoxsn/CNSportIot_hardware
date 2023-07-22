#include <Arduino.h>
// #include <ArduinoJson.h>
// #include <PubSubClient.h>
#include <SPIFFS.h>
// #include <WiFi.h>
// #include <esp_camera.h>

#include "Mybase64.h"
#include "wifiop.h"
#include "cameraop.h"
#include "mqttop.h"

// #include "soc/soc.h"
// #include "soc/rtc_cntl_reg.h"

///// Configurations /////
// WiFi MQTT Configuration
String wifi_ssid;
String wifi_password;
String mqtt_server;
int mqtt_port;

//^^^ Define by netconfig.json which locate in data folder
/**
 * @example: netconfig.json
{
  "wifi": {
    "ssid": "testforesp",
    "password": "233233666"
  },
  "mqtt": {
    "address": "43.143.147.55",
    "port": 1883
  }
}
*/

// Pins Declaration
constexpr int ledOnBoard = 33;

///// End of Configurations /////



/**
 * @description: process the JSON config file
 * @param none
 * @return bool: true if config file is loaded successfully
 */
bool loadConfig() {
  // Read the configuration file and parse the JSON
  // Make sure you have the "config.json" file uploaded to your Arduino board's
  // filesystem
  StaticJsonDocument<200> doc;

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }

  File configFile = SPIFFS.open("/netconfig.json", "r");

  if (!configFile) {
    Serial.println("Config file not found");
    return false;
  }

  DeserializationError error = deserializeJson(doc, configFile);

  configFile.close();

  if (error) {
    Serial.print("Failed to parse config file ");
    Serial.println(error.c_str());
    return false;
  }
  // Copy values to the global variables
  wifi_ssid = doc["wifi"]["ssid"].as<String>();
  wifi_password = doc["wifi"]["password"].as<String>();
  mqtt_server = doc["mqtt"]["address"].as<String>();
  mqtt_port = doc["mqtt"]["port"].as<int>();

  Serial.println("Config loaded successfully");
  return true;
}


/// TODO: fill the description
/**
 * @description:
 * @param String str: string to be encoded
 * @return String: encoded string
 */
String urlencode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (c == ' ') {
      encodedString += '+';
    } else if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
      // encodedString+=code2;
    }
    yield();
  }
  return encodedString;
}

/**
 * @function: Entry point
 */
void setup() {
  pinMode(ledOnBoard, OUTPUT);
  digitalWrite(ledOnBoard, HIGH);
  Serial.begin(9600);
  Serial.println("Start");

  if (loadConfig()) {
    setupWifi(wifi_ssid.c_str(), wifi_password.c_str());
    mqttSetup(mqtt_server.c_str(), mqtt_port);
    setupCamera();
    // setup done, turn on the led
    digitalWrite(ledOnBoard, LOW);
  } else {
    abort();
  }
}

/**
 * @function: Main loop
 */
void loop() {
  mqttReconnect();
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
    
    mqttPublish(imageFile);

  }

  delay(20000);  // [ms]
  Serial.println("Get it.");
}
