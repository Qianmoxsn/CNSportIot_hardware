#include <Arduino.h>

#include "cameraop.h"
#include "fileop.h"
#include "wifiop.h"
#include "easylight.h"
#include "ftpop.h"

///// Configurations /////
// Instantiate the netconfig.json from the template and store it in data folder.
String config_file = "/netconfig.json";

// WiFi MQTT Global Variables
String wifi_ssid;
String wifi_password;
String ftp_server;
String ftp_user;
String ftp_pswd;
int court_id;

ESP32_FTPClient ftp((char*)ftp_server.c_str(), (char*)ftp_user.c_str(), (char*)ftp_pswd.c_str(), 10000, 2);

/// @function: Entry point

void setup() {
  // Time for open COM
  delay(4000);
  setupLights();

  Serial.begin(9600);
  Serial.printf("\nInfo ====================\n");
  Serial.printf("CPU freq: %d MHz\n", ESP.getCpuFreqMHz());
  Serial.printf("RAM free size: %.2f K\n", ESP.getFreeHeap()/1024.0);
  Serial.printf("PSRAM free size: %.2f M\n", ESP.getFreePsram()/1024.0/1024.0);
  Serial.printf("FLASH size: %.2f M\n", ESP.getFlashChipSize()/1024.0/1024.0);
  Serial.println("=========================");
  if (loadConfig(config_file, wifi_ssid, wifi_password, ftp_server, ftp_user, ftp_pswd, court_id)) {
    // setup wifi
    scanfWifi();
    setupWifi(wifi_ssid.c_str(), wifi_password.c_str());
    // sync time
    syncTime();
    // setup camera
    setupCamera();
    // setup SUCCESS, turn on led
    turnOn(3);
  }
  else {
    // setup FAILED, turn on led
    turnOn(1);
    delay(1000);
    abort();
  }

}

/// @function: Main loop

void loop() {
  reconWifi(wifi_ssid.c_str(), wifi_password.c_str());
  
  camera_fb_t* frame_buffer = esp_camera_fb_get();
  
  struct tm info;
  String time_str = "ST:AR.Tx";
  while (!getLocalTime(&info)) {
    time_str = "FA:IL.xx";
  }
  time_str = String(info.tm_mday)+":"+String(info.tm_mon)+":"+String(info.tm_year)+":"+String(info.tm_hour) + ":" +String(info.tm_min) + ":" + String(info.tm_sec);
  

  if (frame_buffer) {
    Serial.printf("width: %d, height: %d, buf: 0x%x, len: %d\n", frame_buffer->width, frame_buffer->height, frame_buffer->buf, frame_buffer->len);
    unsigned char* file_header = (unsigned char*)frame_buffer->buf;
    // FTP upload
    //random name img_xxxxx.jpg
    String name = "img_" + time_str +'_'+ time_str + ".jpg";
    ftp.OpenConnection();
    ftp.ChangeWorkDir(("1/"+String(court_id)+"/").c_str());
    ftp.InitFile("Type I");
    ftp.NewFile(name.c_str());
    ftp.WriteData(file_header, frame_buffer->len);
    ftp.CloseFile();
    ftp.CloseConnection();

    // clear camera buffer
    esp_camera_fb_return(frame_buffer);
    Serial.println("Camera buffer cleared");
    Serial.println("");

  }

  delay(60000);  // [ms]
}
