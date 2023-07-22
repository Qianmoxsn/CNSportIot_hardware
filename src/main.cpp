#include <Arduino.h>
#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <SPIFFS.h>
// #include <WiFi.h>
#include <esp_camera.h>

#include "Mybase64.h"
#include "wifiop.h"

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
constexpr int kCameraPin_PWDN = 32;
constexpr int kCameraPin_RESET = -1;  // NC
constexpr int kCameraPin_XCLK = 0;
constexpr int kCameraPin_SIOD = 26;
constexpr int kCameraPin_SIOC = 27;
constexpr int kCameraPin_Y9 = 35;
constexpr int kCameraPin_Y8 = 34;
constexpr int kCameraPin_Y7 = 39;
constexpr int kCameraPin_Y6 = 36;
constexpr int kCameraPin_Y5 = 21;
constexpr int kCameraPin_Y4 = 19;
constexpr int kCameraPin_Y3 = 18;
constexpr int kCameraPin_Y2 = 5;
constexpr int kCameraPin_VSYNC = 25;
constexpr int kCameraPin_HREF = 23;
constexpr int kCameraPin_PCLK = 22;
constexpr int ledOnBoard = 33;

///// End of Configurations /////

WiFiClient espClient;
PubSubClient g_pub_sub_client(espClient);

// String msg;
// int timeCount = 0;

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

/**
 * @description: return a string of mqtt state number
 * @param int state: mqtt state number
 * @return String: mqtt state string
 */
String mqttState2Str(int state) {
  switch (state) {
    case -4:
      return "MQTT_CONNECTION_TIMEOUT";
    case -3:
      return "MQTT_CONNECTION_LOST";
    case -2:
      return "MQTT_CONNECT_FAILED";
    case -1:
      return "MQTT_DISCONNECTED";
    case 0:
      return "MQTT_CONNECTED";
    case 1:
      return "MQTT_CONNECT_BAD_PROTOCOL";
    case 2:
      return "MQTT_CONNECT_BAD_CLIENT_ID";
    case 3:
      return "MQTT_CONNECT_UNAVAILABLE";
    case 4:
      return "MQTT_CONNECT_BAD_CREDENTIALS";
    case 5:
      return "MQTT_CONNECT_UNAUTHORIZED";
    default:
      return "MQTT_UNKNOWN_STATE";
  }
}

/**
 * @description: (re)connect to MQTT server
 * @param none
 * @return none
 */
void reconnect() {
  // Loop until we're reconnected
  while (!g_pub_sub_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "testClient";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (g_pub_sub_client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      g_pub_sub_client.publish("outTopic", "hello world");
      // ... and resubscribe
      g_pub_sub_client.subscribe("inTopic");
    } else {
      Serial.printf("failed, rc=%d, %s\n", g_pub_sub_client.state(),
                    mqttState2Str(g_pub_sub_client.state()).c_str());
      Serial.println("try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



/**
 * @description: setup and initialize the camera
 * @param none
 * @return none
 */
void setupCamera() {
  const camera_config_t config = {
      .pin_pwdn = kCameraPin_PWDN,
      .pin_reset = kCameraPin_RESET,
      .pin_xclk = kCameraPin_XCLK,
      .pin_sscb_sda = kCameraPin_SIOD,
      .pin_sscb_scl = kCameraPin_SIOC,
      .pin_d7 = kCameraPin_Y9,
      .pin_d6 = kCameraPin_Y8,
      .pin_d5 = kCameraPin_Y7,
      .pin_d4 = kCameraPin_Y6,
      .pin_d3 = kCameraPin_Y5,
      .pin_d2 = kCameraPin_Y4,
      .pin_d1 = kCameraPin_Y3,
      .pin_d0 = kCameraPin_Y2,
      .pin_vsync = kCameraPin_VSYNC,
      .pin_href = kCameraPin_HREF,
      .pin_pclk = kCameraPin_PCLK,
      .xclk_freq_hz = 20000000,
      .ledc_timer = LEDC_TIMER_0,
      .ledc_channel = LEDC_CHANNEL_0,
      .pixel_format = PIXFORMAT_JPEG,
      .frame_size = FRAMESIZE_XGA,
      .jpeg_quality = 10,
      .fb_count = 1,
  };

  esp_err_t err = esp_camera_init(&config);
  ESP_ERROR_CHECK(err);

  Serial.printf("esp_camera_init:%s 0x%x\n", esp_err_to_name(err), err);

  // sensor_t *s = esp_camera_sensor_get();
  // s->set_framesize(s, FRAMESIZE_QVGA);
}

void setupMqtt(const char* server, int port) {
  g_pub_sub_client.setServer(server, port);
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
    setupMqtt(mqtt_server.c_str(), mqtt_port);
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
  reconnect();
  camera_fb_t* frame_buffer = esp_camera_fb_get();

  if (frame_buffer) {
    Serial.printf("width: %d, height: %d, buf: 0x%x, len: %d\n",
                  frame_buffer->width, frame_buffer->height, frame_buffer->buf,
                  frame_buffer->len);
    char data[4104];
    String encoded;
    //      g_pub_sub_client.beginPublish("spottest/", fb->len, true);
    char* input = (char*)frame_buffer->buf;
    char output[base64_enc_len(3)];
    String imageFile = "data:image/jpeg;base64,";
    for (int i = 0; i < frame_buffer->len; i++) {
      base64_encode(output, (input++), 3);
      if (i % 3 == 0) imageFile += urlencode(String(output));
    }
    Serial.println(imageFile);
    esp_camera_fb_return(frame_buffer);
    g_pub_sub_client.beginPublish("spottest/", imageFile.length(), false);
    g_pub_sub_client.print(imageFile.c_str());
    g_pub_sub_client.endPublish();

    // g_pub_sub_client.publish("spottest/", "1");
    // timeCount = 0;
  }
  delay(20000);  // [ms]
  Serial.println("Get it.");
}
