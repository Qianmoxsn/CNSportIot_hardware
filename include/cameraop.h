#pragma once

#include <Arduino.h>
#include <esp_camera.h>

// Pins Declaration
constexpr int kCameraPin_PWDN = -1;
constexpr int kCameraPin_RESET = -1;  // NC
constexpr int kCameraPin_XCLK = -1;
constexpr int kCameraPin_SIOD = 4;
constexpr int kCameraPin_SIOC = 5;
constexpr int kCameraPin_Y9 = 35;
constexpr int kCameraPin_Y8 = 36;
constexpr int kCameraPin_Y7 = 37;
constexpr int kCameraPin_Y6 = 38;
constexpr int kCameraPin_Y5 = 39;
constexpr int kCameraPin_Y4 = 40;
constexpr int kCameraPin_Y3 = 41;
constexpr int kCameraPin_Y2 = 42;
constexpr int kCameraPin_VSYNC = 6;
constexpr int kCameraPin_HREF = 7;
constexpr int kCameraPin_PCLK = 13;

///// End of Configurations /////

void setupCamera();