#include <Arduino.h>
#include <Arduino_LED_Matrix.h>
#include "WiFiS3.h"
#include "secrets.h" // You'll want to make your own "secrets.h" file with 
//                      #define SECRET_SSID "yourNetworkName"
//                      #define SECRET_PASS "yourNetworkPasw"

/*
⠀⠀⠀⠀⠀⠀⣀⡠⠄⠒⠠⢄⠀⣀⠤⠒⠂⠤⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⠀⠀⢀⣠⠤⠐⠒⠤⡀⢀⡠⠔⠂⠠⢄⣀⠀⠀⠀⠀⠀⠀        Arduino LED Reciever
⠀⠀⠀⠀⣠⠞⠂⢀⣀⣀⠀⠀⠉⠁⠀⣀⣀⣀⠀⠑⣤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⠀⣴⠋⠀⣀⣀⣀⠀⠈⠉⠀⢀⣀⣀⠀⠈⠲⡀⠀⠀⠀⠀        By MetroTS
⠀⠀⠀⣸⡏⠀⣴⢋⠤⢌⠙⠆⠀⢠⠎⢁⠤⠍⢧⠀⠀⣷⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⢀⡿⠁⢠⡞⡡⠤⡉⠳⠀⠀⡴⠉⡠⠬⡹⡄⠀⢸⡄⠀⠀⠀
⠀⠀⢀⣽⡁⠀⣿⡀⢀⡘⡄⡇⠀⢸⢢⠇⢀⢢⣺⠀⠀⣿⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⠀⣨⣇⠀⢸⣏⠀⡐⢣⢸⠀⠀⡗⡜⢀⠐⣄⣧⠀⢸⣇⠀⠀⠀
⠀⣰⠉⠙⠷⠀⢛⣟⣦⣄⣣⡇⠀⠘⣎⣰⣤⣾⡿⠁⠴⠋⠈⠱⡀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡎⠉⠻⠆⠈⣿⣳⣤⣙⣼⠂⠀⢻⣁⣦⣼⣿⠇⠠⠞⠁⠙⣆⠀
⣺⠁⠀⣠⠒⠶⣄⠉⠓⢚⣣⡠⠤⢤⣈⡓⠛⠋⢠⠖⠲⢤⡀⠀⢷⠀⠀⠀⠀⠀⠀⠀⢐⡟⠀⢀⠔⠲⢦⡈⠑⠛⣋⣡⠤⠤⣄⣙⠚⠛⢁⡴⠒⠦⣄⠀⠨⡆
⣽⠀⢸⠄⠣⡐⢹⠀⡤⠏⢁⢀⢀⠠⢀⠉⢦⡀⢹⡁⠔⡁⣗⠀⢸⡅⠀⠀⠀⠀⠀⠀⢸⡇⠀⡗⠘⢄⢈⡇⢠⠖⠉⡀⣀⠠⠄⡈⠳⣄⠈⣟⠠⢈⢸⠀⠀⣿
⠹⣄⠸⣷⣤⣧⠞⣾⢁⠐⢀⠀⠠⠄⣀⠑⠄⢱⡸⣧⣴⣶⡟⢠⡟⠁⠀⠀⠀⠀⠀⠀⠈⢷⡀⢿⣦⣾⡼⢳⡏⡠⠁⡀⠠⠠⢄⠈⠢⠈⣆⢿⣤⢶⣾⠃⣼⠃
⠀⡸⢷⠈⠉⠉⢸⡟⣆⠀⢂⠌⣁⠒⡈⠢⢈⣾⣧⠈⠉⠉⢴⢏⡀⠀⠀⠀⠀ ⠀⠀⠀⠀⢀⠿⡆⠉⠉⠁⣾⣳⠀⡀⠆⡑⠄⢂⠙⠄⣱⣿⠀⠉⠉⠡⡾⡅⠀
⠐⡇⠀⠀⠀⠀⠘⣿⡞⣦⣅⣂⣄⣂⣰⣵⣻⣽⠏⠀⠀⠀⠀⢰⡆⠀⠀⠀⠀⠀⠀⠀     ⠀⢺⠀⠀⠀⠀⠀⢻⣷⢳⣴⣈⣐⣈⣄⣮⣞⣯⡿⠂⠀⠀⠀⠀⣸⠀
⠀⠘⢄⠀⠀⠀⠀⠈⠻⠶⣝⣮⣳⣭⣳⣧⠟⠋⠀⠀⠀⠀⣠⠟⠀⠀⠀⠀⠀⠀⠀⠀      ⠀⠀⠣⡀⠀⠀⠀⠀⠙⠷⢮⣽⣭⣻⣜⣷⠾⠛⠁⠀⠀⠀⠀⡼⠃⠀
⠀⠀⠈⡗⢠⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠀⠀⠀⠀⡠⢾⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀          ⠀⢻⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠀⠀⠀⠀⢀⠴⣟⠁⠀⠀
⠀⠀⠀⢸⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀           ⠀⠨⡷⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⠇⠀⠀⠀
⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀  ⠀         ⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⡅⠀⠀⠀
⠀⠀⠀⢽⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣾⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀           ⢨⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢰⡇⠀⠀⠀
*/

char ssid[] = SECRET_SSID;
char pasw[] = SECRET_PASS;

int led = LED_BUILTIN;
int status = WL_IDLE_STATUS;
int id = 0;

int row = id /12;
int col = id %12;

uint8_t one[8][12] = {};

ArduinoLEDMatrix matrix;
WiFiServer server(8888);

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
  // wifi listener
  server.begin();
  Serial.println("Waiting for packets...");
  // matrix init
  matrix.begin();
}

void loop() {
  // check if wifi connection dropped and reastablish
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Wifi dropped... trying to reconnect.");
    WiFi.begin(ssid, pasw);
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.print(".");
    }
    Serial.println("\nConnected!");
  }

  WiFiClient client = server.available();
  if (client) {
    String request = "";
    while (client.connected() && client.available()) {
      char c = client.read();
      request += c;
    }

    Serial.println("Request:" + request);

      //parse setid val x and y from first line

    int id = -1; int val= -1;
    int idIdX = request.indexOf("id=");
    int valIdX = request.indexOf("val=");
    
    if (idIdX != -1 && valIdX != -1) {
        id = request.substring(idIdX + 3).toInt();
        val = request.substring(valIdX + 4).toInt();
    }

    if (id >= 0 && id <96 && (val == 0 ||val == 1)) {
      int row = id / 12;
      int col = id % 12;
      one[row][col] = val;
      matrix.renderBitmap(one, 8, 12);
      Serial.print("LED "); Serial.print(id);
      Serial.print(" --> "); Serial.println(val);
    }
    // actually freaking respond dipshit

    client.println("HTTP/1.1 200 OK");
    client.println("Access-Control-Allow-Origin: *");
    client.println();
    client.stop();

  }
  
}
