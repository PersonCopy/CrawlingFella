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

// IP Address of device.
// Set your Static IP address
IPAddress local_IP(192, 168, 0, 226);
int PORT = 5005;

//WiFiServer server(80);
WiFiUDP udp;

// Expected packet size = 3 bytes.
char packetBuffer[255];

// Connect to hard coded wifi.
void connectWiFi()
{
    WiFi.config(local_IP);
    WiFi.begin(ssid, password);
    
    // Loop attempts.
    int attempts = 0;
    while (WiFi.status() != WL_CONNECTED && attempts < 20)
    {

        delay(500);
        Serial.print(".");
        attempts++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println(WiFi.status());
        Serial.println(WiFi.localIP());
    }
    else
        Serial.println("Connection failed.");
    
    // Start webserver.
    //server.begin();

    // Start UDP server.
    udp.begin(PORT);
}

// Both printWiFiStatus() and a good chunk of webServer(...)
// are taken from example code under:
// https://github.com/arduino/ArduinoCore-renesas/blob/main/libraries/WiFiS3/examples/AP_SimpleWebServer/AP_SimpleWebServer.ino

// Serial prints IP and status of connection.
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

void UDPServer(Servo *servo)
{
    int packetSize = udp.parsePacket();

    if (packetSize)
    {
        Serial.print(" Received packet from : ");
        Serial.println(udp.remoteIP());

        int len = udp.read(packetBuffer, 255);

        // Put "terminating" 0 at end to treat as char* array.
        if (len >= 0 && len < 255)
        packetBuffer[len] = 0;

        // Recieved data.
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

// Running webserver function.
// We will use POST to send angle commands per indexed servo.
// The *servo parameter is expected to be an array.
/*

LEGACY. Now, UDP is used for faster latency.

*/
/*
void webServer(Servo *servo)
{
    // listen for incoming clients.
    WiFiClient client = server.available();

    // End function if no client.
    if (!client) return;

    Serial.println("new client");
    
    // Declare HTTP POST header & body.
    String reqHeader = "";
    String reqBody = "";
    int contentLength = 0;

    // Checks whether we've left the header.
    bool isBody = false;

    // Loop while client is connected.
    while (client.connected())
    {
        if (client.available())
        {
            char c = client.read();

            // Forming the request header first.
            if (!isBody)
            {
                reqHeader += c;

                // Check if POST request in header.
                if (reqHeader.endsWith("\r\n\r\n")) 
                {
                if (reqHeader.startsWith("POST /servo"))
                {
                    // Toggle body reading.
                    isBody = true;

                    // Find and define context length
                    // to properly read body later.
                    int index = reqHeader.indexOf("Content-Length: ");
                    if (index != -1)
                        contentLength = reqHeader.substring(index + 16).toInt();
                    // Exit loop if GET response.
                    else
                    {
                        client.println("HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\nReady");
                        break;
                    }
                }
                }
            }

            // Reading request body now.
            else
            {
                // Append body.
                reqBody += c;
                
                // Once context size is reached, parse JSON.
                if (reqBody.length() >= contentLength)
                {
                    // Deserialize JSON.
                    // Bad request will be returned if deserialization
                    // was unsuccessful.
                    JsonDocument doc;
                    DeserializationError err = deserializeJson(doc, reqBody);
                    if (err)
                    {
                        client.println("HTTP/1.1 400 Bad Request\r\n\r\n");
                        break;
                    }

                    // Parse JSON body now.
                    Serial.println("Received Payload:");
                    jsonToServoControl(doc, servo);

                    // Success response.
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type: application/json");
                    client.println("Connection: close\r\n");
                    client.println("{\"status\":\"success\"}");

                    // Exit loop.
                    break;
                }
            }
        }
    }

    // close the connection.
    client.stop();
    Serial.println("client disconnected");
}
*/