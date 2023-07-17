#ifndef RN_h
#define RN_h

#include "Arduino.h"
#include <Servo.h>
#include "HUSKYLENS.h"//---------------
#include "SoftwareSerial.h"//---------------





class RN {
  public:
    RN(int motorPin1, int motorPin2, int speedPin);
    RN(int trigPin, int echoPin);
    RN(int s0, int s1, int s2, int s3, int out);
    RN(int pin);
    void setMotorSpeed(int speed);
    void setMotorDirection(int direction);
    void stopMotor();
    float getDistance();
    void begin();
    unsigned int getIntensityR();
    unsigned int getIntensityG();
    unsigned int getIntensityB();
    void Servobegin();
    void setServoSpeed(int speed);
    void setServoPosition(int position);
  private:
    int _trigPin, _echoPin, _motorPin1, _motorPin2, _speedPin;
    int S0;
    int S1;
    int S2;
    int S3;
    int sensorOut;
    Servo servoMotor;
    int servoPin;
    int servoSpeed;
    
   
};

class RNCam { //--------------
  public:
    RNCam(int TCamPin, int RCamPin);
    int getCamColorID();
    void cambegin();
  private:
    int _TCamPin,_RCamPin,camColorID;

  };

#endif

