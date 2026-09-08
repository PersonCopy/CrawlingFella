#include "Common.h"

// Takes the instructions in JSON document and
// converts them into servo output.
void jsonToServoControl(JsonDocument &doc, Servo *servo)
{
    // Cast into JSON object.
    JsonObjectConst jsonObj = doc.as<JsonObjectConst>();

    for (JsonPairConst row : jsonObj)
    {
        // Separate into key value pair.
        String key = row.key().c_str();
        byte value = row.value().as<int>();

        // Separate key into command and servo index.
        char command = key.charAt(0);
        byte servoIndex = key.substring(1).toInt();

        // Execite command.
        commandServo(command, &servo[servoIndex], value);
    }
}

// Function to command servo motor.
// command  :   A for absolute angle
//              R for relative angle
// *servo   :   Servo that is to be commanded.
// value    :   Angle value in case of absolute angle "A"
//              or in case of "R", change in angle.
void commandServo(char command, Servo *servo, byte value)
{
    byte angle = 0;
    // Set absolute angle.
    if (command == 'A')
        angle = value % MAX_ANGLE;
    
    // Change relative angle.
    else if (command == 'R')
        angle = servo->read() + value % MAX_ANGLE;
    
    servo->write(angle);
}