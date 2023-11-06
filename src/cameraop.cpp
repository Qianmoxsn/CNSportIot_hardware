#include "cameraop.h"

/**
 * @description: setup and initialize the camera
 * @param none
 * @return none
 */
void setupCamera() {
  const camera_config_t config = {
      .pin_pwdn = kCameraPin_PWDN,
      .pin_reset = kCameraPin_RESET,
      .pin_xclk = kCameraPin_XCLK,
      .pin_sscb_sda = kCameraPin_SIOD,
      .pin_sscb_scl = kCameraPin_SIOC,
      .pin_d7 = kCameraPin_Y9,
      .pin_d6 = kCameraPin_Y8,
      .pin_d5 = kCameraPin_Y7,
      .pin_d4 = kCameraPin_Y6,
      .pin_d3 = kCameraPin_Y5,
      .pin_d2 = kCameraPin_Y4,
      .pin_d1 = kCameraPin_Y3,
      .pin_d0 = kCameraPin_Y2,
      .pin_vsync = kCameraPin_VSYNC,
      .pin_href = kCameraPin_HREF,
      .pin_pclk = kCameraPin_PCLK,
      .xclk_freq_hz = 20000000,
      .ledc_timer = LEDC_TIMER_0,
      .ledc_channel = LEDC_CHANNEL_0,
      .pixel_format = PIXFORMAT_JPEG,
      .frame_size = FRAMESIZE_VGA,
      .jpeg_quality = 10,
      .fb_count = 1,
  };

  esp_err_t err = esp_camera_init(&config);
  ESP_ERROR_CHECK(err);

  Serial.printf("esp_camera_init:%s 0x%x\n", esp_err_to_name(err), err);
}
/**
FRAMESIZE_UXGA (1600 x 1200)
FRAMESIZE_QVGA (320 x 240)
FRAMESIZE_CIF (352 x 288)
FRAMESIZE_VGA (640 x 480)
FRAMESIZE_SVGA (800 x 600)
FRAMESIZE_XGA (1024 x 768)
FRAMESIZE_SXGA (1280 x 1024)
*/