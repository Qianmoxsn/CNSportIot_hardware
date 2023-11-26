#pragma once

#include <Arduino.h>
#include <esp_camera.h>

// Pins Declaration
constexpr int espCamPin_PWDN = -1;
constexpr int espCamPin_RESET = -1;  // NC
constexpr int espCamPin_XCLK = -1;
constexpr int espCamPin_SDA = 5;
constexpr int espCamPin_SCL = 4;
constexpr int espCamPin_D7 = 12;
constexpr int espCamPin_D6 = 11;
constexpr int espCamPin_D5 = 10;
constexpr int espCamPin_D4 = 9;
constexpr int espCamPin_D3 = 8;
constexpr int espCamPin_D2 = 18;
constexpr int espCamPin_D1 = 17;
constexpr int espCamPin_D0 = 16;
constexpr int espCamPin_VS = 6;
constexpr int espCamPin_HS = 7;
constexpr int espCamPin_PCLK = 13;

// Camera Configurations
constexpr int espCamQuality = FRAMESIZE_UXGA;
/*
    FRAMESIZE_96X96,    // 96x96
    FRAMESIZE_QQVGA,    // 160x120
    FRAMESIZE_QCIF,     // 176x144
    FRAMESIZE_HQVGA,    // 240x176
    FRAMESIZE_240X240,  // 240x240
    FRAMESIZE_QVGA,     // 320x240
    FRAMESIZE_CIF,      // 400x296
    FRAMESIZE_HVGA,     // 480x320
    FRAMESIZE_VGA,      // 640x480
    FRAMESIZE_SVGA,     // 800x600
    FRAMESIZE_XGA,      // 1024x768
    FRAMESIZE_HD,       // 1280x720
    FRAMESIZE_SXGA,     // 1280x1024
    FRAMESIZE_UXGA,     // 1600x1200
    // 3MP Sensors
    FRAMESIZE_FHD,      // 1920x1080
    FRAMESIZE_P_HD,     //  720x1280
    FRAMESIZE_P_3MP,    //  864x1536
    FRAMESIZE_QXGA,     // 2048x1536
    // 5MP Sensors
    FRAMESIZE_QHD,      // 2560x1440
    FRAMESIZE_WQXGA,    // 2560x1600
    FRAMESIZE_P_FHD,    // 1080x1920
    FRAMESIZE_QSXGA,    // 2560x1920
*/

///// End of Configurations /////

void setupCamera();