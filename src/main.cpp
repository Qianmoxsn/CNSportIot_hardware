#include <Arduino.h>

#include "easylight.h"
#include "wifiop.h"



/// @function: Entry point

void setup() {
  setupLights();

  Serial.begin(9600);
  Serial.println("Start");
  turnoncamlights();

  turnOn();
  delay(400);
  turnOff();
  turnOn(1, 3, 5);
  delay(400);
  turnOff();
  delay(400);
  turnOn(2, 4);
  delay(400);
  turnOff();


  turnoffcamlights();

  scanfWifi();
}

/// @function: Main loop

void loop() {
  flowlights();
  delay(500);
  flowcamlights();
  delay(500);
}
