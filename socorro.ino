#include <WiFi.h>

const char* ssid = "TP-LINK_1586";
const char* password = "29270811";

void setup() {
  Serial.begin(115200);

  Serial.println("Conectando ao WiFi...");

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.println("Conectado!");
  Serial.print("IP: ");
  Serial.println(WiFi.localIP());

  Serial.print("MAC: ");
  Serial.println(WiFi.macAddress());
}

void loop() {
}
