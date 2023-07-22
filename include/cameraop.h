#pragma once

#include <Arduino.h>
#include <esp_camera.h>

// Pins Declaration
constexpr int kCameraPin_PWDN = 32;
constexpr int kCameraPin_RESET = -1;  // NC
constexpr int kCameraPin_XCLK = 0;
constexpr int kCameraPin_SIOD = 26;
constexpr int kCameraPin_SIOC = 27;
constexpr int kCameraPin_Y9 = 35;
constexpr int kCameraPin_Y8 = 34;
constexpr int kCameraPin_Y7 = 39;
constexpr int kCameraPin_Y6 = 36;
constexpr int kCameraPin_Y5 = 21;
constexpr int kCameraPin_Y4 = 19;
constexpr int kCameraPin_Y3 = 18;
constexpr int kCameraPin_Y2 = 5;
constexpr int kCameraPin_VSYNC = 25;
constexpr int kCameraPin_HREF = 23;
constexpr int kCameraPin_PCLK = 22;

///// End of Configurations /////

void setupCamera();