#include "Common.h"
#include "WiFiS3.h"

// Added in gitignore in case my dumbass accidentally
// uploads my wifi credentials on here :')
// Not relevant when connecting to the remote's AP tho.
#include "secrets.h"

// AP of remote to connect to.
char ap_ssid[] = AP_SSID;
char ap_password[] = AP_PASS;

// Fallback Network.
char w_ssid[] = WIFI_SSID;
char w_password[] = WIFI_PASS;

// Set fixed IP & UDP port.
IPAddress local_IP(192, 168, 0, 226);
int8_t PORT = 5005;

// Declare UDP object.
WiFiUDP udp;

// Expected packet size = 3 bytes.
char packetBuffer[255];

void connectWiFi()
{
    // Start connection with AP of remote control.
    WiFi.config(local_IP);
    WiFi.begin(ap_ssid, ap_password);
    
    // Loop through 20 delays if the WiFi hasn't connected yet.
    int8_t attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {
        delay(500);
        Serial.print(".");
        attempts++;
    }

    // Print WiFi data to serial if connection was successful.
    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println(WiFi.status());
        Serial.println(WiFi.localIP());
    }

    // Connect to fallback network if connection failed.
    else
    {
        Serial.println("Connection failed. Connecting to fallback WiFi.");
        WiFi.begin(w_ssid, w_password);
        delay(1000);
    }
    
    // Start UDP server at PORT.
    udp.begin(PORT);
}

void printWiFiStatus()
{
    // print the SSID of the connected network.
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print IP address of robot.
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);
}

void UDPServer(Servo *servo)
{
    // Catch packet.
    int packetSize = udp.parsePacket();

    if (packetSize)
    {
        Serial.print(" Received packet from : ");
        Serial.println(udp.remoteIP());

        // Read packet into buffer expecting 256 elements.
        int len = udp.read(packetBuffer, 255);

        // Put "terminating" 0 at end to treat as char* array.
        if (len >= 0 && len < 255)
            packetBuffer[len] = 0;
        
        // Parse recieved data as string.
        String data = (String)packetBuffer;
        Serial.println("Data : %s\n" + data);
        udp.endPacket();

        // Parse as JSON.
        JsonDocument doc;
        DeserializationError err = deserializeJson(doc, data);
        if (err)
            Serial.println("JSON parse failed");
            
        // Parse JSON body now.
        Serial.println("Received Payload:");
        Serial.println(data);
        jsonToServoControl(doc, servo);
    }
}