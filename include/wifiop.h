#pragma once

#include <Arduino.h>
#include <WiFi.h>

void setupWifi(const char*, const char*);
void scanfWifi();
void reconWifi(const char*, const char*);
void syncTime();