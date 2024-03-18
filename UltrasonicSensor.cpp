// UltrasonicSensor.cpp //

#include "UltrasonicSensor.h"

UltrasonicSensor::UltrasonicSensor(int triggerPin, int echoPin)
{   this->trigPin = triggerPin;
    this->echoPin = echoPin;
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}
float UltrasonicSensor::calculateDistance(int delayMicros)
{   digitalWrite(trigPin, HIGH);
    delayMicroseconds(delayMicros);
    digitalWrite(trigPin, LOW);
    float duration = pulseIn(echoPin, HIGH);
    float distance = duration * 0.034 / 2.0;
    return distance;
}
