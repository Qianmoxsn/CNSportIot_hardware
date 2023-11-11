#pragma once

#include <Arduino.h>
#include <esp_camera.h>

// Pins Declaration
constexpr int kCameraPin_PWDN = -1;
constexpr int kCameraPin_RESET = -1;  // NC
constexpr int kCameraPin_XCLK = -1;
constexpr int kCameraPin_SIOD = 5;
constexpr int kCameraPin_SIOC = 4;
constexpr int kCameraPin_Y9 = 12;
constexpr int kCameraPin_Y8 = 11;
constexpr int kCameraPin_Y7 = 10;
constexpr int kCameraPin_Y6 = 9;
constexpr int kCameraPin_Y5 = 8;
constexpr int kCameraPin_Y4 = 18;
constexpr int kCameraPin_Y3 = 17;
constexpr int kCameraPin_Y2 = 16;
constexpr int kCameraPin_VSYNC = 6;
constexpr int kCameraPin_HREF = 7;
constexpr int kCameraPin_PCLK = 13;

///// End of Configurations /////

void setupCamera();