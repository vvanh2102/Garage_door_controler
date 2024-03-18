
#include <Servo.h>
#include <IRObstacleSensor.h>
#include <UltrasonicSensor.h>


IRObstacleSensor irSensor1(7);
IRObstacleSensor irSensor2(8);
UltrasonicSensor usSensor1(2, 3);
UltrasonicSensor usSensor2(4, 5);
Servo remoteControl;
int crankAngle;

void setup()
{
  Serial.begin(9600);
  remoteControl.attach(6);
  remoteControl.write(110);
}  
void pushOpen()
{
  remoteControl.write(110);
  for (crankAngle = 110; crankAngle <= 130; crankAngle += 1)
  {
    remoteControl.write(crankAngle);
    delay(20);
    remoteControl.write(110);
  }
}

void pushClose()
{
  remoteControl.write(110);
  for (crankAngle = 110; crankAngle >= 90; crankAngle -= 1)
  {
    remoteControl.write(crankAngle);
    delay(20);
    remoteControl.write(110);
  }
}

void loop()
{
  int obsIF;

  if (usSensor1.calculateDistance(10) <= 10 || usSensor2.calculateDistance(10) <= 10)
  {
    obsIF = 0;
  }
  else
  {
    obsIF = 1;
  }
  float dis = usSensor1.calculateDistance(10);
  float dis2 = usSensor2.calculateDistance(10);
  String statusString = String(irSensor1.readDigitalValue()) + "," + String(irSensor2.readDigitalValue()) + "," + String(obsIF) + ", " + String(dis) + ", " + String(dis2);
  Serial.println(statusString);
  Serial.flush();
  delay(500);

  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');

    if (command == "pushOpen")
    {
      pushOpen();
    }
    else if (command == "pushClose")
    {
      pushClose();
    }
  }
}