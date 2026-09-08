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

WiFiServer server(80);

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
    server.begin();
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

// Running webserver function.
// We will use POST to send angle commands per indexed servo.
// The *servo parameter is expected to be an array.
void webServer(Servo *servo)
{
    // listen for incoming clients.
    WiFiClient client = server.available();

    // End function if no client.
    if (!client) return;

    Serial.println("new client");
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected())              // loop while the client's connected
    {
        if (client.available())
        {             // if there's bytes to read from the client,
            char c = client.read();             // read a byte, then
            Serial.write(c);                    // print it out the serial monitor
            if (c == '\n') {                    // if the byte is a newline character

                // if the current line is blank, you got two newline characters in a row.
                // that's the end of the client HTTP request, so send a response:
                if (currentLine.length() == 0)
                {
                    // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                    // and a content-type so the client knows what's coming, then a blank line:
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println();

                    // the content of the HTTP response follows the header:
                    client.print("Click <a href=\"/1/H\">here</a> turn the servo +10deg<br>");
                    client.print("Click <a href=\"/1/L\">here</a> turn the servo -10deg<br>");

                    // The HTTP response ends with another blank line:
                    client.println();
                    // break out of the while loop:
                    break;
                }
                else
                {    // if you got a newline, then clear currentLine:
                    currentLine = "";
                }
            }
            else if (c != '\r')
            {  // if you got anything else but a carriage return character,
                currentLine += c;      // add it to the end of the currentLine
            }

            int angle = servo[0].read();
            // Check to see if the client request was "GET /H" or "GET /L":
            if (currentLine.endsWith("GET /1/H"))
            {
                servo[0].write(angle + 10 % 180);
            }
            if (currentLine.endsWith("GET /1/L"))
            {
                servo[0].write(angle - 10 % 180);
            }
        }
    }
    // close the connection:
    client.stop();
    Serial.println("client disconnected");
}