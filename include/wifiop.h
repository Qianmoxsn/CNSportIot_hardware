#pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

void setupWifi(const char*, const char*);
void scanfWifi();
void reconWifi(const char*, const char*);