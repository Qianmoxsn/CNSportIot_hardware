#include "mqttop.h"

WiFiClient esp_wifi_client;
PubSubClient mqtt_client(esp_wifi_client);

/**
 * @description: setup MQTT server
 * @param const char* server: MQTT server address
 * @param int port: MQTT server port
 * @return none
 */
void mqttSetup(const char* server, int port) {
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
void mqttReconnect() {
  // Loop until we're reconnected
  while (!mqtt_client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Create a random client ID
    String clientId = "testClient";
    clientId += String(random(0xffff), HEX);
    // Attempt to connect
    if (mqtt_client.connect(clientId.c_str())) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      mqtt_client.publish("outTopic", "hello world");
      // ... and resubscribe
      mqtt_client.subscribe("inTopic");
    } else {
      Serial.printf("failed, rc=%d, %s\n", mqtt_client.state(),
                    mqttStatetoName(mqtt_client.state()).c_str());
      Serial.println("try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

/**
 * @description: publish a image(string) to MQTT server
 * @param String imageFile: image file in base64 format
 * @return none
*/
void mqttPublish(String topic, String imageFile) {
  mqtt_client.beginPublish(topic.c_str(), imageFile.length(), false);
  mqtt_client.print(imageFile.c_str());
  mqtt_client.endPublish();
}
