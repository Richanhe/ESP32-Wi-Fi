#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "TP-LINK_1586";
const char* password = "29270811";

WebServer server(80);

const int LED_PIN = 2;

void ligarLed() {
  digitalWrite(LED_PIN, HIGH);

  server.send(200, "application/json",
              "{\"status\":\"ligado\"}");
}

void desligarLed() {
  digitalWrite(LED_PIN, LOW);

  server.send(200, "application/json",
              "{\"status\":\"desligado\"}");
}

void statusLed() {
  bool estado = digitalRead(LED_PIN);

  server.send(
    200,
    "application/json",
    estado ?
      "{\"led\":\"ligado\"}" :
      "{\"led\":\"desligado\"}"
  );
}

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

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

  // GET /ligar
  server.on("/ligar", HTTP_GET, ligarLed);

  // GET /desligar
  server.on("/desligar", HTTP_GET, desligarLed);

  // GET /status
  server.on("/status", HTTP_GET, statusLed);

  server.begin();

  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}
