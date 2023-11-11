#include "easylight.h"

/**
 * @brief Initializes the pins for the LEDs.
 *
 */
void setupLights() {
  for (int i = 0; i < 5; i++) {
    pinMode(led_pin_list[i], OUTPUT);
  }
}

/**
 * @brief Flows the LEDs with a delay of 100ms.
 *
 */
void flowlights() { flowlights(100); }

/**
 * @brief Flows the LEDs with a given delay.
 *
 * @param m_sec The delay in milliseconds.
 */

void flowlights(int m_sec) {
  for (int i = 0; i < 5; i++) {
    digitalWrite(led_pin_list[i], LED_ON);
    delay(m_sec);
    digitalWrite(led_pin_list[i], LED_OFF);
    delay(m_sec);
  }
}

/**
 * Turns on all 5 LEDs.
 */
void turnOn() {
  for (int i = 0; i < 5; i++) {
    turnOn(i + 1);
  }
}

/**
 * Turns off all 5 LEDs.
 */
void turnOff() {
  for (int i = 0; i < 5; i++) {
    turnOff(i + 1);
  }
}

/**
 * Turns on a specific LED.
 *
 * @param ledx The index of the LED to turn on (1-5).
 */
void turnOn(int ledx) { digitalWrite(led_pin_list[ledx - 1], LED_ON); }

/**
 * Turns off a specific LED.
 *
 * @param ledx The index of the LED to turn off (1-5).
 */
void turnOff(int ledx) { digitalWrite(led_pin_list[ledx - 1], LED_OFF); }

/**
 * Turns on two specific LEDs.
 *
 * @param ledx1 The index of the first LED to turn on (1-5).
 * @param ledx2 The index of the second LED to turn on (1-5).
 */
void turnOn(int ledx1, int ledx2) {
  turnOn(ledx1);
  turnOn(ledx2);
}

/**
 * Turns off two specific LEDs.
 *
 * @param ledx1 The index of the first LED to turn off (1-5).
 * @param ledx2 The index of the second LED to turn off (1-5).
 */
void turnOff(int ledx1, int ledx2) {
  turnOff(ledx1);
  turnOff(ledx2);
}

/**
 * Turns on three specific LEDs.
 *
 * @param ledx1 The index of the first LED to turn on (1-5).
 * @param ledx2 The index of the second LED to turn on (1-5).
 * @param ledx3 The index of the third LED to turn on (1-5).
 */
void turnOn(int ledx1, int ledx2, int ledx3) {
  turnOn(ledx1);
  turnOn(ledx2);
  turnOn(ledx3);
}

/**
 * Turns off three specific LEDs.
 *
 * @param ledx1 The index of the first LED to turn off (1-5).
 * @param ledx2 The index of the second LED to turn off (1-5).
 * @param ledx3 The index of the third LED to turn off (1-5).
 */
void turnOff(int ledx1, int ledx2, int ledx3) {
  turnOff(ledx1);
  turnOff(ledx2);
  turnOff(ledx3);
}

/**
 * Turns on four specific LEDs.
 *
 * @param ledx1 The index of the first LED to turn on (1-5).
 * @param ledx2 The index of the second LED to turn on (1-5).
 * @param ledx3 The index of the third LED to turn on (1-5).
 * @param ledx4 The index of the fourth LED to turn on (1-5).
 */
void turnOn(int ledx1, int ledx2, int ledx3, int ledx4) {
  turnOn(ledx1);
  turnOn(ledx2);
  turnOn(ledx3);
  turnOn(ledx4);
}

/**
 * Turns off four specific LEDs.
 *
 * @param ledx1 The index of the first LED to turn off (1-5).
 * @param ledx2 The index of the second LED to turn off (1-5).
 * @param ledx3 The index of the third LED to turn off (1-5).
 * @param ledx4 The index of the fourth LED to turn off (1-5).
 */
void turnOff(int ledx1, int ledx2, int ledx3, int ledx4) {
  turnOff(ledx1);
  turnOff(ledx2);
  turnOff(ledx3);
  turnOff(ledx4);
}

void setupcamLights() {
  for (int i = 0; i < 14; i++) {
    pinMode(cam_pin_list[i], OUTPUT);
  }
}

void flowcamlights() {
  for (int i = 0; i < 14; i++) {
    digitalWrite(cam_pin_list[i], LED_ON);
    delay(100);
    digitalWrite(cam_pin_list[i], LED_OFF);
    delay(100);
  }
}

void turnoncamlights() {
  for (int i = 0; i < 14; i++) {
    digitalWrite(cam_pin_list[i], LED_ON);
  }
}

void turnoffcamlights() {
  for (int i = 0; i < 14; i++) {
    digitalWrite(cam_pin_list[i], LED_OFF);
  }
}