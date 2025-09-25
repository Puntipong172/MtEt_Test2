#include <WiFi.h>
#include <HTTPClient.h>

// à¸à¸³à¸«à¸™à¸” Wi-Fi
const char* ssid = "Mi";
const char* password = "puntipong";

// à¸à¸³à¸«à¸™à¸” Telegram
String botToken = "8325211367:AAFEudogCuUd69Wq8tVEJfXjUTAEsopr83I";  // BotFather à¹ƒà¸«à¹‰à¸¡à¸²
String chatID = "8283458197";                                        // à¸ˆà¸²à¸ @userinfobot

void setup() {
  Serial.begin(115200);

  // à¹€à¸Šà¸·à¹ˆà¸­à¸¡à¸•à¹ˆà¸­ WiFi
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");

  // à¸—à¸”à¸ªà¸­à¸šà¸ªà¹ˆà¸‡à¸‚à¹‰à¸­à¸„à¸§à¸²à¸¡
  sendMessage("ESP32 temp humi pressure");
}

void loop() {
  int pressure = random(100, 241);
  int temp = random(1, 25);
  int humi = random(20,80);
  String msg = "temp = " + String(temp)+"Humi ="+String(humi)+"Prssure = "+String(pressure);
  sendMessage(msg);

  delay(10000);
}

// à¸Ÿà¸±à¸‡à¸à¹Œà¸Šà¸±à¸™à¸ªà¹ˆà¸‡à¸‚à¹‰à¸­à¸„à¸§à¸²à¸¡à¹„à¸›à¸—à¸µà¹ˆ Telegram
void sendMessage(String text) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    String url = "https://api.telegram.org/bot" + botToken + "/sendMessage?chat_id=" + chatID + "&text=" + urlencode(text);

    http.begin(url);
    int httpCode = http.GET();
    if (httpCode > 0) {
      Serial.println("à¸ªà¹ˆà¸‡à¸‚à¹‰à¸­à¸„à¸§à¸²à¸¡à¸ªà¸³à¹€à¸£à¹‡à¸ˆ: " + text);
    } else {
      Serial.println("à¸ªà¹ˆà¸‡à¹„à¸¡à¹ˆà¸ªà¸³à¹€à¸£à¹‡à¸ˆ: " + http.errorToString(httpCode));
    }
    http.end();
  }
}

// à¸Ÿà¸±à¸‡à¸à¹Œà¸Šà¸±à¸™à¹€à¸‚à¹‰à¸²à¸£à¸«à¸±à¸ªà¸‚à¹‰à¸­à¸„à¸§à¸²à¸¡à¹ƒà¸«à¹‰à¸–à¸¹à¸à¸•à¹‰à¸­à¸‡ (URL Encode)
String urlencode(String str) {
  String encodedString = "";
  char c;
  char code0;
  char code1;
  char code2;
  for (int i = 0; i < str.length(); i++) {
    c = str.charAt(i);
    if (isalnum(c)) {
      encodedString += c;
    } else {
      code1 = (c & 0xf) + '0';
      if ((c & 0xf) > 9) {
        code1 = (c & 0xf) - 10 + 'A';
      }
      c = (c >> 4) & 0xf;
      code0 = c + '0';
      if (c > 9) {
        code0 = c - 10 + 'A';
      }
      code2 = '\0';
      encodedString += '%';
      encodedString += code0;
      encodedString += code1;
    }
  }
  return encodedString;
}