#include <RN.h>

const int servoPin = 2;
const int S0 = 3;
const int S1 = 4;
const int S2 = 5;
const int S3 = 6;
const int sensorOut = 7;

RN ultraSensorF(14, 15); 
RN ultraSensorL(16, 17);
RN ultraSensorR(18, 19); 
RN motor( 8, 9, 10);


RN colorSensor(S0, S1, S2, S3, sensorOut);
RN servoController(servoPin);


int color=0;
const int CRange = 300;
int degStraight = 75;
int degRange = 50;
int rCount = 0;
int wallDist = 100;
int stopDist = 40;
int rightDist=30;



  bool inRange(int val, int minimum, int maximum)
{
  return ((minimum <= val) && (val <= maximum));
}

int detect_color() {

  unsigned int redValue = colorSensor.getIntensityR();
  unsigned int greenValue = colorSensor.getIntensityG();
  unsigned int blueValue = colorSensor.getIntensityB();
  
  Serial.print("R: ");
  Serial.print(redValue);
  Serial.print(" G: ");
  Serial.print(greenValue);
  Serial.print(" B: ");
  Serial.println(blueValue);



 if ( inRange(redValue, 502, 2000) && inRange(greenValue, 552, 2000) && inRange(blueValue, 401, 2000)){
   
    color=1;
    Serial.println("Color 1");

    }


    else {
   
   color=2;
   Serial.println("Other");

    }

  return(color);

}

void setup() {
  Serial.begin(9600);
  colorSensor.begin();
  servoController.Servobegin();
  rCount = 0;
  pinMode(11, OUTPUT);
}

void loop() {


  float distanceF = ultraSensorF.getDistance();
  float distanceR = ultraSensorR.getDistance();
  float distanceL = ultraSensorL.getDistance();

  Serial.print("Distance Front: ");
  Serial.print(distanceF);
  Serial.print(" cm");
  Serial.print("  Distance Right: ");
  Serial.print(distanceR);
  Serial.print(" cm");
  Serial.print("  Distance Left: ");
  Serial.println(distanceL);

  color=detect_color();
  Serial.print("Color: ");
  Serial.println(color);
  



 if (color==1){

    servoController.setServoPosition(degStraight);
    motor.setMotorDirection(-1);
    motor.setMotorSpeed(255);
    delay(400);
    digitalWrite(11,HIGH);
    motor.setMotorSpeed(0);
    delay(1000);

  
 }else{

    servoController.setServoPosition(degStraight);
    motor.setMotorDirection(1);
    motor.setMotorSpeed(255);
    digitalWrite(11,LOW);
    delayMicroseconds(1);

 }



  

}



