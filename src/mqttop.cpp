#include "mqttop.h"

WiFiClient esp_wifi_client;
PubSubClient mqtt_client;

/**
 * @description: setup MQTT server
 * @param const char* server: MQTT server address
 * @param int port: MQTT server port
 * @return none
 */
void mqttSetup(const char* server, int port) {
  mqtt_client.setClient(esp_wifi_client);
  mqtt_client.setServer(server, port);
}

/**
 * @description: return a string of mqtt state number
 * @param int state: mqtt state number
 * @return String: mqtt state name
 */
String mqttStatetoName(int state) {
  switch (state) {
  case -4:
    return "MQTT_CONNECTION_TIMEOUT - 服务器在保持活动时间内没有响应";
  case -3:
    return "MQTT_CONNECTION_LOST - 网络连接中断";
  case -2:
    return "MQTT_CONNECT_FAILED - 网络连接失败";
  case -1:
    return "MQTT_DISCONNECTED - 客户端干净地断开连接";
  case 0:
    return "MQTT_CONNECTED - 客户端已连接";
  case 1:
    return "MQTT_CONNECT_BAD_PROTOCOL - 服务器不支持请求的MQTT版本";
  case 2:
    return "MQTT_CONNECT_BAD_CLIENT_ID - 服务器拒绝了客户端标识符";
  case 3:
    return "MQTT_CONNECT_UNAVAILABLE - 服务器无法接受连接";
  case 4:
    return "MQTT_CONNECT_BAD_CREDENTIALS - 用户名/密码被拒绝";
  case 5:
    return "MQTT_CONNECT_UNAUTHORIZED - 客户端无权连接";
  default:
    return "MQTT_UNKNOWN_STATE";
  }
}

/**
 * @description: (re)connect to MQTT server
 * @param none
 * @return none
 */
void mqttReconnect() {
  Serial.println(" ");
  // Loop until we're reconnected
  // while (mqtt_client.state() != 0) {
  Serial.print("Attempting MQTT connection...");
  // Create a random client ID
  String clientId = "testClient-";
  clientId += String(random(0xffff));
  // Attempt to connect
  if (mqtt_client.connect(clientId.c_str())) {
    Serial.println("connected");
    // Once connected, publish an announcement...
    mqtt_client.publish("outTopic", "hello world");
    // ... and resubscribe
    // mqtt_client.subscribe("inTopic");
  }
  else {
    Serial.printf("failed, rc=%d, %s\n", mqtt_client.state(), mqttStatetoName(mqtt_client.state()).c_str());
    Serial.println("try again in 5 seconds");
    // Wait 5 seconds before retrying
    delay(5000);
  }
  // }
  Serial.printf("<=%d=> MQTT_CONNECTED ::");
  Serial.println(mqttStatetoName(mqtt_client.state()).c_str());
}

/**
 * @description: publish a image(string) to MQTT server
 * @param String imageFile: image file in base64 format
 * @return none
 */
int mqttPublish(String topic, String imageFile) {
  int base64_len = imageFile.length();

  // beginPublish return 0 --> failed
  int begin_flag = mqtt_client.beginPublish(topic.c_str(), base64_len, true);
  if (begin_flag == 0) {
    return 1;
  }

  // Large payload, split into 256 bytes packages
  int pack_size = 256;
  mqtt_client.setBufferSize(pack_size);
  int pack_cnt = base64_len / pack_size;
  // Sending packages
  for (int i = 0; i < (pack_cnt - 1); i++) {
    mqtt_client.print(imageFile.substring(i * pack_size, (i + 1) * pack_size).c_str());
  }
  mqtt_client.print(imageFile.substring((pack_cnt - 1) * pack_size).c_str());

  Serial.printf("%dB in %d packs, All away!\n", base64_len, pack_cnt);

  // endPublish return 0 --> failed
  int end_flag = mqtt_client.endPublish();
  if (end_flag == 0) {
    return 2;
  }

  return 0;
}

/**
 * @description: loop for MQTT client
 * @param none
 * @return bool: true if loop() success
 * @comment: 神奇函数，具有一定的指示功能
 */
bool mqttLoop() {
  return mqtt_client.loop();
}