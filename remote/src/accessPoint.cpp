#include "Common.h"
#include "../../crawlerArduino/include/secrets.h"

// Code sourced from futechiot @ github:
// https://gist.github.com/futechiot/ee0223dd269cbe7d8605ce97d120d7d2
// Thanks for that :D

// Access point ID and password.
const char *Apssid = "CrawlerRemote";
const char *Appassword = "ez2connect";

// Fixed WiFi config data.
IPAddress local_IP(192, 168, 0, 225);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);


// Configures and starts access point / hotspot.
void setupHotspot()
{
    WiFi.softAPConfig(local_IP, gateway, subnet);
    WiFi.mode(WIFI_AP);

    WiFi.softAP(Apssid, Appassword);
    IPAddress myIP = WiFi.softAPIP();

    // Output IP on setup.
    Serial.println(myIP);
}

void connectToWiFi()
{
    // Set IP and the likes.
    WiFi.config(local_IP, gateway, subnet);

    // Make connection attempt.
    char ssid[] = SECRET_SSID;
    char password[] = SECRET_PASS;
    WiFi.begin(ssid, password);

    // Loop attempts.
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {

        delay(500);
        Serial.print(".");
        attempts++;
    }

    // Output result.
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println(WiFi.status());
        Serial.println(WiFi.localIP());
    }
    else
        Serial.println("Connection failed.");
}