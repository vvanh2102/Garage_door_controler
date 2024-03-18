// IRObstacleSensor.h //

#ifndef IRObstacleSensor_h
#define IRObstacleSensor_h

#include <Arduino.h>

class IRObstacleSensor { public:
    IRObstacleSensor(int pin);
    bool detectObstacle();
    int readDigitalValue();
private:
    int irPin;
};

#endif
