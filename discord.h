#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecureBearSSL.h>

const char ssid[] = SECRET_SSID;    // Network SSID (name)
const char pass[] = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const String discord_webhook = SECRET_WEBHOOK;
const String discord_tts = SECRET_TTS;
//openssl s_client -showcerts -connect discordapp.com:443 (get last certificate)
const uint8_t discordappFingerprint[] = "b1 18 d2 91 0b 81 82 ee 94 86 6f 3c ee 19 04 93 6f d9 77 d4";//[20] = {0xb1, 0x18, 0xd2, 0x91, 0x0b, 0x81, 0x82, 0xee, 0x94, 0x86, 0x6f, 0x3c, 0xee, 0x19, 0x04, 0x93, 0x6f, 0xd9, 0x77, 0xd4};
ESP8266WiFiMulti WiFiMulti;

void connectWIFI() {
  WiFiMulti.addAP(ssid, pass);
  WiFi.mode(WIFI_STA);
  Serial.print("[WiFi] Connecting to: ");
  Serial.println(ssid);
  // wait for WiFi connection
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
    delay(100);
  }
  Serial.println();
  Serial.println("[WiFi] Connected");
}

void sendDiscord(String content) {
  std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);

  if (client) {
    client->setFingerprint(discordappFingerprint);
    {
      HTTPClient https;
      Serial.println("[HTTP] Connecting to Discord...");
      Serial.println("[HTTP] Message: " + content);
      Serial.println("[HTTP] TTS: " + discord_tts);
      if (https.begin(*client, discord_webhook)) {  // HTTPS
        // start connection and send HTTP header
        https.addHeader("Content-Type", "application/json");
        int httpCode = https.POST("{\"content\":\"" + content + "\",\"tts\":" + discord_tts +"}");

        // httpCode will be negative on error
        if (httpCode > 0) {
          // HTTP header has been send and Server response header has been handled
          Serial.print("[HTTP] Status code: ");
          Serial.println(httpCode);

          // file found at server
          if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
            String payload = https.getString();
            Serial.print("[HTTP] Response: ");
            Serial.println(payload);
          }
        } else {
          Serial.print("[HTTP] Post... failed, error: ");
          Serial.println(https.errorToString(httpCode).c_str());
        }

        https.end();
      } else {
        Serial.printf("[HTTP] Unable to connect\n");
      }

      // End extra scoping block
    }
  } else {
    Serial.println("[HTTP] Unable to create client");
  }
}
