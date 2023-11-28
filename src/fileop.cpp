#include "fileop.h"

/**
 * @description: process the JSON config file
 * @param none
 * @return bool: true if config file is loaded successfully
 */
bool loadConfig(String config_file, String& wifi_ssid, String& wifi_password, String& ftp_server, String& ftp_username, String& ftp_password,uint32_t* court_id) {
  // Read the configuration file and parse the JSON
  // Make sure you have the "config.json" file uploaded to your Arduino board's filesystem
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
  ftp_server = doc["ftp"]["server"].as<String>();
  ftp_username = doc["ftp"]["username"].as<String>();
  ftp_password = doc["ftp"]["password"].as<String>();
  *court_id = doc["identity"]["court_id"];

  Serial.println("Config loaded successfully");
  return true;
}