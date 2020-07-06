#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>

const char ssid[] = SECRET_SSID;    // Network SSID (name)
const char pass[] = SECRET_PASS;    // Network password (use for WPA, or use as key for WEP)
const String discord_webhook = SECRET_WEBHOOK;
const String discord_tts = SECRET_TTS;
//openssl s_client -showcerts -connect discordapp.com:443 (get last certificate)
const char* discordappCertificate = \
//                                    "-----BEGIN CERTIFICATE-----\n" \
//                                    "MIIFdDCCBFygAwIBAgIQJ2buVutJ846r13Ci/ITeIjANBgkqhkiG9w0BAQwFADBv\n" \
//                                    "MQswCQYDVQQGEwJTRTEUMBIGA1UEChMLQWRkVHJ1c3QgQUIxJjAkBgNVBAsTHUFk\n" \
//                                    "ZFRydXN0IEV4dGVybmFsIFRUUCBOZXR3b3JrMSIwIAYDVQQDExlBZGRUcnVzdCBF\n" \
//                                    "eHRlcm5hbCBDQSBSb290MB4XDTAwMDUzMDEwNDgzOFoXDTIwMDUzMDEwNDgzOFow\n" \
//                                    "gYUxCzAJBgNVBAYTAkdCMRswGQYDVQQIExJHcmVhdGVyIE1hbmNoZXN0ZXIxEDAO\n" \
//                                    "BgNVBAcTB1NhbGZvcmQxGjAYBgNVBAoTEUNPTU9ETyBDQSBMaW1pdGVkMSswKQYD\n" \
//                                    "VQQDEyJDT01PRE8gUlNBIENlcnRpZmljYXRpb24gQXV0aG9yaXR5MIICIjANBgkq\n" \
//                                    "hkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAkehUktIKVrGsDSTdxc9EZ3SZKzejfSNw\n" \
//                                    "AHG8U9/E+ioSj0t/EFa9n3Byt2F/yUsPF6c947AEYe7/EZfH9IY+Cvo+XPmT5jR6\n" \
//                                    "2RRr55yzhaCCenavcZDX7P0N+pxs+t+wgvQUfvm+xKYvT3+Zf7X8Z0NyvQwA1onr\n" \
//                                    "ayzT7Y+YHBSrfuXjbvzYqOSSJNpDa2K4Vf3qwbxstovzDo2a5JtsaZn4eEgwRdWt\n" \
//                                    "4Q08RWD8MpZRJ7xnw8outmvqRsfHIKCxH2XeSAi6pE6p8oNGN4Tr6MyBSENnTnIq\n" \
//                                    "m1y9TBsoilwie7SrmNnu4FGDwwlGTm0+mfqVF9p8M1dBPI1R7Qu2XK8sYxrfV8g/\n" \
//                                    "vOldxJuvRZnio1oktLqpVj3Pb6r/SVi+8Kj/9Lit6Tf7urj0Czr56ENCHonYhMsT\n" \
//                                    "8dm74YlguIwoVqwUHZwK53Hrzw7dPamWoUi9PPevtQ0iTMARgexWO/bTouJbt7IE\n" \
//                                    "IlKVgJNp6I5MZfGRAy1wdALqi2cVKWlSArvX31BqVUa/oKMoYX9w0MOiqiwhqkfO\n" \
//                                    "KJwGRXa/ghgntNWutMtQ5mv0TIZxMOmm3xaG4Nj/QN370EKIf6MzOi5cHkERgWPO\n" \
//                                    "GHFrK+ymircxXDpqR+DDeVnWIBqv8mqYqnK8V0rSS527EPywTEHl7R09XiidnMy/\n" \
//                                    "s1Hap0flhFMCAwEAAaOB9DCB8TAfBgNVHSMEGDAWgBStvZh6NLQm9/rEJlTvA73g\n" \
//                                    "JMtUGjAdBgNVHQ4EFgQUu69+Aj36pvE8hI6t7jiY7NkyMtQwDgYDVR0PAQH/BAQD\n" \
//                                    "AgGGMA8GA1UdEwEB/wQFMAMBAf8wEQYDVR0gBAowCDAGBgRVHSAAMEQGA1UdHwQ9\n" \
//                                    "MDswOaA3oDWGM2h0dHA6Ly9jcmwudXNlcnRydXN0LmNvbS9BZGRUcnVzdEV4dGVy\n" \
//                                    "bmFsQ0FSb290LmNybDA1BggrBgEFBQcBAQQpMCcwJQYIKwYBBQUHMAGGGWh0dHA6\n" \
//                                    "Ly9vY3NwLnVzZXJ0cnVzdC5jb20wDQYJKoZIhvcNAQEMBQADggEBAGS/g/FfmoXQ\n" \
//                                    "zbihKVcN6Fr30ek+8nYEbvFScLsePP9NDXRqzIGCJdPDoCpdTPW6i6FtxFQJdcfj\n" \
//                                    "Jw5dhHk3QBN39bSsHNA7qxcS1u80GH4r6XnTq1dFDK8o+tDb5VCViLvfhVdpfZLY\n" \
//                                    "Uspzgb8c8+a4bmYRBbMelC1/kZWSWfFMzqORcUx8Rww7Cxn2obFshj5cqsQugsv5\n" \
//                                    "B5a6SE2Q8pTIqXOi6wZ7I53eovNNVZ96YUWYGGjHXkBrI/V5eu+MtWuLt29G9Hvx\n" \
//                                    "PUsE2JOAWVrgQSQdso8VYFhH2+9uRv0V9dlfmrPb2LjkQLPNlzmuhbsdjrzch5vR\n" \
//                                    "pu/xO28QOG8=\n" \
//                                    "-----END CERTIFICATE-----\n";
                                    "-----BEGIN CERTIFICATE-----\n" \
                                    "MIID0DCCArigAwIBAgIQFuWGeOBwlDlL39tO/KY73zANBgkqhkiG9w0BAQwFADB7\n" \
                                    "MQswCQYDVQQGEwJHQjEbMBkGA1UECAwSR3JlYXRlciBNYW5jaGVzdGVyMRAwDgYD\n" \
                                    "VQQHDAdTYWxmb3JkMRowGAYDVQQKDBFDb21vZG8gQ0EgTGltaXRlZDEhMB8GA1UE\n" \
                                    "AwwYQUFBIENlcnRpZmljYXRlIFNlcnZpY2VzMB4XDTA0MDEwMTAwMDAwMFoXDTI4\n" \
                                    "MTIzMTIzNTk1OVowgYUxCzAJBgNVBAYTAkdCMRswGQYDVQQIExJHcmVhdGVyIE1h\n" \
                                    "bmNoZXN0ZXIxEDAOBgNVBAcTB1NhbGZvcmQxGjAYBgNVBAoTEUNPTU9ETyBDQSBM\n" \
                                    "aW1pdGVkMSswKQYDVQQDEyJDT01PRE8gRUNDIENlcnRpZmljYXRpb24gQXV0aG9y\n" \
                                    "aXR5MHYwEAYHKoZIzj0CAQYFK4EEACIDYgAEA0d7L3XJghWF+3XkkRbUq2KZ9T5S\n" \
                                    "CwbOQQB/l+EKJDwdAQTuPdKNCZcM4HXk+vt3iir1A2BLNosWIxatCXH0SvQoULT+\n" \
                                    "iBxuP2wvLwlZW6VbCzOZ4sM9iflqLO+y0wbpo4HyMIHvMB8GA1UdIwQYMBaAFKAR\n" \
                                    "CiM+lvEH7OKvKe+CpX/QMKS0MB0GA1UdDgQWBBR1cacZSBm8nZ3qQUfflMRId5nT\n" \
                                    "eTAOBgNVHQ8BAf8EBAMCAYYwDwYDVR0TAQH/BAUwAwEB/zARBgNVHSAECjAIMAYG\n" \
                                    "BFUdIAAwQwYDVR0fBDwwOjA4oDagNIYyaHR0cDovL2NybC5jb21vZG9jYS5jb20v\n" \
                                    "QUFBQ2VydGlmaWNhdGVTZXJ2aWNlcy5jcmwwNAYIKwYBBQUHAQEEKDAmMCQGCCsG\n" \
                                    "AQUFBzABhhhodHRwOi8vb2NzcC5jb21vZG9jYS5jb20wDQYJKoZIhvcNAQEMBQAD\n" \
                                    "ggEBAHjsU4nMWJ1jJdsVWxa5HLKxt/Sqib3Q3lS5DHsjKGKRfUDdSFnlAiG3Vll+\n" \
                                    "pX8MHWp4E0PgONUsALAM+7HcSCWDcNnkguU8PovJrH0XMBfXS1Pm3tXpUwBd/sj1\n" \
                                    "aZUekAaDZ9Ww02ZKaCDON9X/jKsRG6j5koYCtWuS4hH/GEvLDPX+VCPCcC+NKMjU\n" \
                                    "VxP8AzvKBA/5CSp+1C3pXY8X4cRyjCWJFScGWOioc+NAaQZtGrJ5pp0WqASWeQYJ\n" \
                                    "b2uQlNzRYBFWgodwJX8Kx7rSAPJHX3LgVsZtL7a+bOzRKQCoeRmtRo9V9jNJH8HJ\n" \
                                    "MppQ/qXxmyYQTzbZCA3K17HKM8w=\n" \
                                    "-----END CERTIFICATE-----\n";


WiFiMulti WiFiMulti;

void connectWIFI() {
  WiFiMulti.addAP(ssid, pass);
  WiFi.mode(WIFI_STA);
  Serial.print("[WiFi] Connecting to: ");
  Serial.println(ssid);
  // wait for WiFi connection
  while ((WiFiMulti.run() != WL_CONNECTED)) {
    Serial.print(".");
  }
  Serial.println("[WiFi] Connected");
}

void sendDiscord(String content) {
  WiFiClientSecure *client = new WiFiClientSecure;
  if (client) {
    client -> setCACert(discordappCertificate);
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

    delete client;
  } else {
    Serial.println("[HTTP] Unable to create client");
  }
}
