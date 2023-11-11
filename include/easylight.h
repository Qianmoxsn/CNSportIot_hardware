#pragma once

#include <Arduino.h>

#define LED_1_PIN 42
#define LED_2_PIN 41
#define LED_3_PIN 40
#define LED_4_PIN 39
#define LED_5_PIN 21

#define CAM_1 4
#define CAM_2 5
#define CAM_3 6
#define CAM_4 7
#define CAM_5 15
#define CAM_6 16
#define CAM_7 17
#define CAM_8 18
#define CAM_9 8
#define CAM_10 9
#define CAM_11 10
#define CAM_12 11
#define CAM_13 12
#define CAM_14 13

// creat a list of led_pin_list
constexpr int led_pin_list[5] = {LED_1_PIN, LED_2_PIN, LED_3_PIN, LED_4_PIN, LED_5_PIN};
constexpr int cam_pin_list[14] = {CAM_1, CAM_2, CAM_3, CAM_4, CAM_5, CAM_6, CAM_7, CAM_8, CAM_9, CAM_10, CAM_11, CAM_12, CAM_13, CAM_14};

#define LED_ON HIGH
#define LED_OFF LOW

void setupLights();
void flowlights();
void flowlights(int);
void turnOn();
void turnOff();
void turnOn(int);
void turnOff(int);
void turnOn(int, int);
void turnOff(int, int);
void turnOn(int, int, int);
void turnOff(int, int, int);
void turnOn(int, int, int, int);
void turnOff(int, int, int, int);

void setupcamLights();
void flowcamlights();
void turnoncamlights();
void turnoffcamlights();