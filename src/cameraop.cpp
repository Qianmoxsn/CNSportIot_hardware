#include "cameraop.h"

/**
 * @description: setup and initialize the camera
 * @param none
 * @return none
 */
void setupCamera() {
  const camera_config_t config = {
      .pin_pwdn = espCamPin_PWDN,
      .pin_reset = espCamPin_RESET,
      .pin_xclk = espCamPin_XCLK,
      .pin_sscb_sda = espCamPin_SDA,
      .pin_sscb_scl = espCamPin_SCL,
      .pin_d7 = espCamPin_D7,
      .pin_d6 = espCamPin_D6,
      .pin_d5 = espCamPin_D5,
      .pin_d4 = espCamPin_D4,
      .pin_d3 = espCamPin_D3,
      .pin_d2 = espCamPin_D2,
      .pin_d1 = espCamPin_D1,
      .pin_d0 = espCamPin_D0,
      .pin_vsync = espCamPin_VS,
      .pin_href = espCamPin_HS,
      .pin_pclk = espCamPin_PCLK,
      .xclk_freq_hz = 24000000,
      .ledc_timer = LEDC_TIMER_0,
      .ledc_channel = LEDC_CHANNEL_0,
      .pixel_format = PIXFORMAT_JPEG,
      .frame_size = espCamQuality,
      .jpeg_quality = 10,
      .fb_count = 1,
  };

  esp_err_t err = esp_camera_init(&config);
  //ESP_ERROR_CHECK(err);

  Serial.printf("esp_camera_init:%s 0x%x\n", esp_err_to_name(err), err);
}