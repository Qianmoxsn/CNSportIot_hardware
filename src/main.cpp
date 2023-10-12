#include <WebServer.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include "CRtspSession.h"
#include "OV2640.h"
#include "OV2640Streamer.h"
#include "SimStreamer.h"


OV2640 cam;
WiFiServer rtspServer(8554);
CStreamer *streamer;
CRtspSession *session;
WiFiClient client;  // FIXME, support multiple clients

#include "wifikeys.h"

void setup() {
  Serial.begin(115200);
  while (!Serial) {
  }
  cam.init(esp32cam_aithinker_config);

  IPAddress ip;
  // IPv6Address ip6;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(F("."));
  }
  ip = WiFi.localIP();
  // ip6 = WiFi.localIPv6();
  Serial.println(F("WiFi connected"));
  Serial.println("");
  Serial.println(ip);
  // Serial.println(ip6);

  rtspServer.begin();
}

void loop() {
  uint32_t msecPerFrame = 100;
  static uint32_t lastimage = millis();

  // If we have an active client connection, just service that until gone
  // (FIXME - support multiple simultaneous clients)
  if (session) {
    session->handleRequests(0);  // we don't use a timeout here,
    // instead we send only if we have new enough frames

    uint32_t now = millis();
    if (now > lastimage + msecPerFrame ||
        now < lastimage) {  // handle clock rollover
      session->broadcastCurrentFrame(now);
      lastimage = now;

      // check if we are overrunning our max frame rate
      now = millis();
      if (now > lastimage + msecPerFrame)
        printf("warning exceeding max frame rate of %d ms\n", now - lastimage);
    }

    if (session->m_stopped) {
      delete session;
      delete streamer;
      session = NULL;
      streamer = NULL;
    }
  } else {
    client = rtspServer.accept();

    if (client) {
      // streamer = new SimStreamer(&client, true);             // our streamer
      // for UDP/TCP based RTP transport
      // our streamer for UDP/TCP based RTP transport
      streamer = new OV2640Streamer(&client, cam);
    }
      // our threads RTSP session and state
    session = new CRtspSession(&client, streamer);
  }
}