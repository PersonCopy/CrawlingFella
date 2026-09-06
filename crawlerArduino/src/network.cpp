#include "Common.h"
#include "WiFiS3.h"

// Added in gitignore in case my dumbass accidentally
// uploads my wifi credentials on here :')
// Not relevant when connecting to the remote's AP tho.
#include "secrets.h"

// Network to connect to.
char ssid[] = SECRET_SSID;
char password[] = SECRET_PASS;
int keyIndex = 0;

WiFiServer server(80);

void connectWiFi()
{
    WiFi.begin(ssid, password);
    
    // Loop attempts.
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {

        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED){
        Serial.println(WiFi.status());
        Serial.println(WiFi.localIP());}
    else
        Serial.println("Connection failed.");
}

// Taken from example code under:
// https://github.com/arduino/ArduinoCore-renesas/blob/main/libraries/WiFiS3/examples/AP_SimpleWebServer/AP_SimpleWebServer.ino

void printWiFiStatus()
{
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print where to go in a browser:
    Serial.print("To see this page in action, open a browser to http://");
    Serial.println(ip);
}