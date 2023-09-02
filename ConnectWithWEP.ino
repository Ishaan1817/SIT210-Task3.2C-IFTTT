#include "arduino_secrets.h" 
#include <WiFiNINA.h>
int light;

char ssid[] = SECRET_SSID;

char pass[] = SECRET_PASSWORD;


WiFiClient client;


char   HOST_NAME[] = "maker.ifttt.com";

String PATH_NAME   = "/trigger/ishaan/with/key/hhQqWQMkJkA4Ns1CHfAO_1w4AhwobVxDZFg3a0hiDd4"; // change your EVENT-NAME and YOUR-KEY

String queryString = "?value1=57&value2=25";


void setup() {
  WiFi.begin(ssid, pass);


  Serial.begin(9600);

  while (!Serial);

  if (client.connect(HOST_NAME, 80)) {

    Serial.println("Connected to server");

  }

  else {
    Serial.println("connection failed");
  }

}


void loop() {

  light = analogRead(A5);
  Serial.println(light);
  if (light > 610) {

    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");

    client.println("Host: " + String(HOST_NAME));

    client.println("Connection: close");

    client.println(); 
    while (client.connected()) {

      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }

    }
    client.stop();
    Serial.println();
    Serial.println("Mail sent");

  }

}