#pragma once

#include <Arduino.h>

#define LED_1_PIN 2
#define LED_2_PIN 15
#define LED_3_PIN 16
#define LED_4_PIN 11
#define LED_5_PIN 10

// creat a list of led_pin_list
constexpr int led_pin_list[5] = {LED_1_PIN, LED_2_PIN, LED_3_PIN, LED_4_PIN, LED_5_PIN};

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