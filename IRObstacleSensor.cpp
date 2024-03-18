// IRObstacleSensor.cpp //

#include "IRObstacleSensor.h"

IRObstacleSensor::IRObstacleSensor(int pin)
{   irPin = pin;
    pinMode(irPin, INPUT);
}
bool IRObstacleSensor::detectObstacle()
{
    return digitalRead(irPin) == HIGH;
}
int IRObstacleSensor::readDigitalValue()
{
    return digitalRead(irPin);
}
