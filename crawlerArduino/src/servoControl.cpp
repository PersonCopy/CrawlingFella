#include "Common.h"

void jsonToServoControl(JsonDocument &doc, Servo *servos)
{
    // Cast document into JSON object.
    JsonObjectConst jsonObj = doc.as<JsonObjectConst>();

    // Take every command and parse it as "AB" : C, where
    // A: either 'A' or 'R',
    // B: Index of servo to move,
    // C: Value to send to command.
    for (JsonPairConst row : jsonObj)
    {
        // Separate into key value pair.
        String key = row.key().c_str();
        byte value = row.value().as<int>();

        // Separate key into command and servo index.
        char command = key.charAt(0);
        byte servoIndex = key.substring(1).toInt();

        // Execute command.
        commandServo(command, &servos[servoIndex], value);
    }
}

int parseAngle(int angle)
{
    // Wrap safety to prevent overshoot.
    angle %= 360;
    if (angle > MAX_ANGLE)
        angle = MAX_ANGLE;

    // Since the specific REELY servos used are nonlinear
    // after 135-180 deg (wrapping to 180 at input 165),
    // The output has to be mapped to match the real angle.
    if (angle > 135)
         angle = map(angle, 135, 180, 135, 165);
    return angle;
}

void commandServo(char command, Servo *servo, byte value)
{
    byte angle = 0;

    // Set servo to absolute angle if command is 'A'.
    if (command == 'A'){
    Serial.println(value);
        angle = parseAngle(value);}
    
    // Change servo angle by relative amount if command is 'R'.
    else if (command == 'R')
        angle = parseAngle(servo->read() + value);
    
    // Send servo command.
    servo->write(angle);
}