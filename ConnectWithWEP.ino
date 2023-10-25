#include "arduino_secrets.h" 
#include <WiFiNINA.h>
int light;

char ssid[] = SECRET_SSID; //Wi-Fi network SSID

char pass[] = SECRET_PASSWORD; //Wi-Fi network password


WiFiClient client;


char   HOST_NAME[] = "maker.ifttt.com";  //// IFTTT server hostname

String PATH_NAME   = "/trigger/ishaan/with/key/hhQqWQMkJkA4Ns1CHfAO_1w4AhwobVxDZFg3a0hiDd4"; // change EVENT-NAME and KEY generated

String queryString = "?value1=57&value2=25";


void setup() {
  WiFi.begin(ssid, pass);


  Serial.begin(9600); //Initialize serial communication with the computer

  while (!Serial); //Wait for the serial connection to be established


  if (client.connect(HOST_NAME, 80)) {

    Serial.println("Connected to server");

  }

  else {
    Serial.println("connection failed");
  }

}


void loop() {

  light = analogRead(A5); // Read the analog value from pin A5
  Serial.println(light);  //  Print the light reading to the serial monitor
  if (light > 610) {

    client.println("GET " + PATH_NAME + queryString + " HTTP/1.1");

    client.println("Host: " + String(HOST_NAME));

    client.println("Connection: close");

    client.println(); // Read and print the response from the server
    while (client.connected()) {

      if (client.available()) {
        char c = client.read();
        Serial.print(c);
      }

    }
    client.stop();  // Close the connection to the server
    Serial.println();
    Serial.println("Disconnected");

  }

}
