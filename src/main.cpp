#include <Arduino.h>
#include <Arduino_LED_Matrix.h>
#include "WiFiS3.h"
#include "secrets.h"

char ssid[] = SECRET_SSID;
char pasw[] = SECRET_PASS;

int led = LED_BUILTIN;
int status = WL_IDLE_STATUS;

ArduinoLEDMatrix matrix;

uint8_t one[8][12] = {
  {1,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0,0,0}
};

void setup() {
  Serial.begin(9600);

  while (!Serial) {
    ;
  }
  if (WiFi.status() == WL_NO_MODULE) {
    Serial.println("Connection with WiFi Module failed.");
    while(true);
  }
  // cool
  WiFi.begin(ssid, pasw);
  Serial.println("Connecting...");

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());
  matrix.begin();

}

void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi dropped... trying to reconnect.");
    WiFi.begin(ssid, pasw);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nConnected!");
  }
  matrix.renderBitmap(one, 8, 12);
  
}
