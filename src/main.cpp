#include <Arduino.h>

#include "easylight.h"
#include "wifiop.h"



/// @function: Entry point

void setup() {
  setupLights();

  Serial.begin(9600);
  Serial.println("Start");
  turnOn();
  delay(400);
  turnOff();
  delay(400);
  turnOn(1);
  delay(400);
  turnOff(1);
  delay(400);
  turnOn(2, 4, 5);
  delay(400);
  turnOff(2, 4);
  delay(400);
  turnOn(1, 2, 3);
  delay(400);
  turnOff();

  scanfWifi();
}

/// @function: Main loop

void loop() { flowlights(); }
