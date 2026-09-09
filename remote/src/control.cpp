#include "Common.h"
#include "ArduinoJson.h"

// Information to connect to robot via POST (legacy).
/*
WiFiClient client;
HTTPClient http;
const char* serverName = "http://192.168.0.226/servo";
*/
const char* serverIP = "192.168.0.226";
int port = 5005;

WiFiUDP udp;

void sendStickCommand(AnalogStick stick)
{
    // Establish UDP connection.
    udp.beginPacket(serverIP, port);

    // Scale joystick data into servo angles.
    float scale = (177.0/256.0);
    int x_scaled = (float)(stick.getX() + 128) * scale;
    int y_scaled = (float)(stick.getY() + 128) * scale;
    int clickCom = stick.getClick() ? 90 : 0;

    // Add commands into JSON.
    JsonDocument doc;
    doc["A0"] = x_scaled;
    doc["A1"] = y_scaled;
    doc["A2"] = 90; // 3rd servo is continuously rotating. 90 stops motion.

    // Serialize into UDP output directly.
    serializeJson(doc, udp);
    udp.endPacket();
}

// Sends command of current stick via POST
/*

LEGACY. UDP is now being used instead.

*/
/*
void sendStickCommand(AnalogStick stick)
{
    // If connection was already established,
    // then there is no need to reconnect.
    if (!http.connected())
    {
        http.begin(client, serverName);
        http.addHeader("Content-Type", "application/json");
    }

    // Scale joystick data into servo angles.
    float scale = (177.0/256.0);
    int x_scaled = (float)(stick.getX() + 128) * scale;
    int y_scaled = (float)(stick.getY() + 128) * scale;
    int clickCom = stick.getClick() ? 90 : 0;

    // Add commands into JSON.
    JsonDocument doc;
    doc["A0"] = x_scaled;
    doc["A0"] = y_scaled;
    doc["A0"] = 90;

    // Serialize into string.
    String data;
    serializeJson(doc, data);
    //String data = "{\"A0\":\"" + (String)x_scaled + "\",\"A1\":\"" + (String)y_scaled + "\",\"A2\":\"" + (String)(90) + "\"}";

    Serial.println(data);

    // POST and print out HTTP response.
    int response = http.POST(data);
    Serial.println(response);
}*/