#include <Arduino.h>
#include <BLAKE2s.h>

#include "HardwareSerial.h"
#include "Mybase64.h"
#include "cameraop.h"
// #include "fileop.h"
// #include "mqttop.h"
// #include "wifiop.h"

///// Configurations /////
// Instantiate the netconfig.json from the template and store it in data folder.
String config_file = "/netconfig.json";

// WiFi MQTT Global Variables
String mqtt_server;
int mqtt_port;

// Pins Declaration
const int ledOnBoard = 33;
HardwareSerial myserial(1);  // use UART1

/// @function: Entry point

void setup() {
  pinMode(ledOnBoard, OUTPUT);
  digitalWrite(ledOnBoard, HIGH);
  Serial.begin(115200);
  // RX TX
  myserial.begin(115200, SERIAL_8N1, 14, 15);

  setupCamera();
  // setup done, turn on the led
  digitalWrite(ledOnBoard, LOW);
  delay(10000);
}

/// @function: Main loop

void loop() {
  camera_fb_t *frame_buffer = esp_camera_fb_get();

  if (frame_buffer) {
    myserial.printf("width: %d, height: %d, buf: 0x%x, len: %d\r\n",
                    frame_buffer->width, frame_buffer->height,
                    frame_buffer->buf, frame_buffer->len);
    char *input = (char *)frame_buffer->buf;
    char output[base64_enc_len(3)];
    String imageFile = "data:image/jpeg;base64,";
    for (int i = 0; i < frame_buffer->len; i++) {
      base64_encode(output, (input++), 3);
      if (i % 3 == 0) imageFile += urlencode(String(output));
    }
    esp_camera_fb_return(frame_buffer);
    int segmentSize = 1024;
    int stringLength = imageFile.length();
    for (int i = 0; i < stringLength; i += segmentSize) {
      String segment;
      if (i + segmentSize < stringLength) {
        segment = imageFile.substring(i, i + segmentSize);
      } else {
        segment = imageFile.substring(i);
      }

      // 发送串口消息说明是第几段和片段长度
      int segmentNumber = i / segmentSize + 1;
      int segmentLength = segment.length();
      myserial.print("Segment ");
      myserial.print(segmentNumber);
      myserial.print(" (Length: ");
      myserial.print(segmentLength);
      myserial.print("):");
      myserial.print("\r\n");

      Serial.print(segmentNumber);
      Serial.print(segmentLength);
      Serial.print("\r\n");

      delay(100);
      myserial.print(segment);
      myserial.print("\r\n");
      delay(100);
    }
    //  myserial.print("\r\n");
  }
  delay(120000);  // [ms]
}
