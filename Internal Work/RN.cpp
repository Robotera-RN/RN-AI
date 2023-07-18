#include "Arduino.h"
#include "RN.h"

RN::RN(int motorPin1, int motorPin2, int speedPin)
{
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);
  pinMode(speedPin, OUTPUT);
  _motorPin1 = motorPin1;
  _motorPin2 = motorPin2;
  _speedPin = speedPin;
}

RN::RN(int trigPin, int echoPin) {
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    _trigPin = trigPin;
    _echoPin = echoPin;
}

RN::RN(int s0, int s1, int s2, int s3, int out) {
  S0 = s0;
  S1 = s1;
  S2 = s2;
  S3 = s3;
  sensorOut = out;
}

RN::RN(int pin) {
  servoPin = pin;
}

void RN::Servobegin() {
  servoMotor.attach(servoPin);
}

void RN::setServoSpeed(int speed) {
  servoSpeed = speed;
}

void RN::setServoPosition(int position) {
  if (position < 0) {
    position = 0;
  } else if (position > 180) {
    position = 180;
  }
  
  if (servoSpeed > 0) {
    int currentPosition = servoMotor.read();
    if (position > currentPosition) {
      for (int i = currentPosition; i <= position; i++) {
        servoMotor.write(i);
        delay(servoSpeed);
      }
    } else {
      for (int i = currentPosition; i >= position; i--) {
        servoMotor.write(i);
        delay(servoSpeed);
      }
    }
  } else {
    servoMotor.write(position);
  }
}


void RN::begin() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
}

unsigned int RN::getIntensityR() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  unsigned int red = pulseIn(sensorOut, LOW);
  return red;
}
unsigned int RN::getIntensityG() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  unsigned int green = pulseIn(sensorOut, LOW);
  return green;
}

unsigned int RN::getIntensityB() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  unsigned int blue = pulseIn(sensorOut, LOW);
  return blue;
}

float RN::getDistance() {
    digitalWrite(_trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(_trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(_trigPin, LOW);
    float duration = pulseIn(_echoPin, HIGH);
    float distance = duration * 0.034 / 2;
    return distance;
}

void RN::setMotorSpeed(int speed)
{
  analogWrite(_speedPin, speed);
}

void RN::setMotorDirection(int direction)
{
  if (direction == 1) {
    digitalWrite(_motorPin1, HIGH);
    digitalWrite(_motorPin2, LOW);
  } else if (direction == -1) {
    digitalWrite(_motorPin1, LOW);
    digitalWrite(_motorPin2, HIGH);
  } else {
    stopMotor();
  }
}

void RN::stopMotor()
{
  analogWrite(_speedPin, 0);
  digitalWrite(_motorPin1, LOW);
  digitalWrite(_motorPin2, LOW);
}
