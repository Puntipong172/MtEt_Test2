#include <WiFi.h>
#include <PubSubClient.h>

// กำหนดข้อมูล Wi-Fi
const char* ssid = "POCO";
const char* password = "puntipong";
// กำหนดข้อมูล MQTT
const char* mqttServer = "mqtt3.thingspeak.com";
const int mqttPort = 1883;
const char* clientID = "Ng0QIAUTASABAScRERYgDTM";        
const char* username = "Ng0QIAUTASABAScRERYgDTM";         
const char* mqttPassword = "+CuaWQzw5tSIIAHSWqlz9hmh";
const char* topic = "channels/3021737/publish"; 

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  Serial.print("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" connected");

  client.setServer(mqttServer, mqttPort);
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(clientID, username, mqttPassword)) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      delay(5000);
    }
  }
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  int value1 = random(100, 200);
  int value2 = random(0, 100);
  String payload = "field1=" + String(value1) + "&field2=" + String(value2);
  Serial.println("Sending payload: " + payload);
  client.publish(topic, payload.c_str());
  delay(5000);
}


