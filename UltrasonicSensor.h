// UltrasonicSensor.h //

#ifndef UltrasonicSensor_h
#define UltrasonicSensor_h

#include <Arduino.h>

class UltrasonicSensor {
public:
    UltrasonicSensor(int triggerPin, int echoPin);
    float calculateDistance(int delayMicros);
private:
    int trigPin;
    int echoPin;
};

#endif
