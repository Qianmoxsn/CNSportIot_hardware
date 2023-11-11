#pragma once

#include <Arduino.h>
#include <ArduinoJson.h>
#include <SPIFFS.h>

bool loadConfig(String, String&, String&, String&, String&, String&);