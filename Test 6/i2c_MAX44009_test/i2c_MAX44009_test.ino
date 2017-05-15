#include <Wire.h>
#include "i2c.h"
#include "i2c_MAX44009.h"
MAX44009 max44009;
static uint8_t I2C_ADDRESS_1 = (0x4A);
static uint8_t I2C_ADDRESS_2 = (0x4B);
static unsigned long mLux_value_1;
static unsigned long mLux_value_2;

void setup()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT);

    Serial.println("Probe MAX44009: ");
    if (max44009.initialize(I2C_ADDRESS_1)) Serial.println("Sensor found at 0x4A on I2C bus !");
    if (max44009.initialize(I2C_ADDRESS_2)) Serial.println("Sensor found at 0x4B on I2C bus !");
    else
    {
        Serial.println("Sensor missing");
        while (1) { };
    }
}

void loop()
{
    max44009.getMeasurement(I2C_ADDRESS_1 , mLux_value_1);
    //Serial.print((String)"mLUX: " + mLux_value_1 + " from 0x4A !!! "); // debug

    max44009.getMeasurement(I2C_ADDRESS_2 , mLux_value_2);
    //Serial.println((String)"mLUX: " + mLux_value_2 + " from 0x4B !!! "); // debug

    if((mLux_value_1 < 10000) || (mLux_value_2 < 10000)) digitalWrite(13, HIGH);
    else digitalWrite(13, LOW);
    
    //delay(1000);
}
