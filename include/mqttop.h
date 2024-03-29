#pragma once

#include <Arduino.h>
#include <PubSubClient.h>

#include "wifiop.h"

void mqttSetup(const char*, int);

String mqttStatetoName(int);

void mqttReconnect();

void mqttPublish(String,String);