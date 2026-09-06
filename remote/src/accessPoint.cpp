#include "Common.h"

// Code sourced from futechiot @ github:
// https://gist.github.com/futechiot/ee0223dd269cbe7d8605ce97d120d7d2
// Thanks for that :D

// Access point ID and password.
const char *Apssid = "CrawlerRemote";
const char *Appassword = "ez2connect";

// Configures and starts access point / hotspot.
void setupHotspot()
{
    WiFi.mode(WIFI_AP);

    WiFi.softAP(Apssid, Appassword);
    IPAddress myIP = WiFi.softAPIP();

    // Output IP on setup.
    Serial.println(myIP);
}