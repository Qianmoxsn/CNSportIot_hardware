#include "fileop.h"

/**
 * @description: process the JSON config file
 * @param none
 * @return bool: true if config file is loaded successfully
 */
bool loadConfig(String config_file, String& wifi_ssid, String& wifi_password,
                String& mqtt_server, String& mqtt_topic,int& mqtt_port) {
  // Read the configuration file and parse the JSON
  // Make sure you have the "config.json" file uploaded to your Arduino board's
  // filesystem
  StaticJsonDocument<200> doc;

  if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return false;
  }

  File configFile = SPIFFS.open(config_file, "r");

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
  mqtt_topic = doc["mqtt"]["topic"].as<String>();
  mqtt_port = doc["mqtt"]["port"].as<int>();

  Serial.println("Config loaded successfully");
  return true;
}