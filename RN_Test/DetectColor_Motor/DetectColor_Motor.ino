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
const int CRange = 40;
int degStraight = 80;
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



 if ( inRange(redValue, 370-CRange, 400+CRange) && inRange(greenValue, 370-CRange, 400+CRange) && inRange(blueValue, 370-CRange, 300+CRange)){
   
   Serial.print("White Color");
    color=1;

    }
    else if ( inRange(redValue, 950-CRange, 950+CRange) && inRange(greenValue, 1020-CRange, 1040+CRange) && inRange(blueValue,750-CRange, 800+CRange)){
   
   Serial.print("Playfield Borders");
   color=2;

    }

    else if ( inRange(redValue, 410-CRange, 410+CRange) && inRange(greenValue, 600-CRange, 600+CRange) && inRange(blueValue, 510-CRange, 510+CRange)){
   
   Serial.print("Orange Color");
    color=3;

    }

    else if ( inRange(redValue, 670-CRange, 670+CRange) && inRange(greenValue, 670-CRange, 670+CRange) && inRange(blueValue, 470-CRange, 470+CRange)){
   
   Serial.print("Blue Color");
   color=4;

    }

    else {
   
   Serial.print("Other Color");
   color=6;

    }

  return(color);

}

void setup() {
  Serial.begin(9600);
  colorSensor.begin();
  servoController.Servobegin();
  rCount = 0;
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
    Serial.println("case 1");
    servoController.setServoPosition(degStraight);
    motor.setMotorDirection(1);
    motor.setMotorSpeed(200);
    Serial.println("case 1");
    delay(1);


 } else if (color==3){
    Serial.println("case 2");
    motor.stopMotor();
    delay(1000); 
    servoController.setServoPosition(degStraight+degRange);
    motor.setMotorDirection(-1);
    motor.setMotorSpeed(255);
    delay(1000); 

  } else if (color==4){

    Serial.println("case 3");
    servoController.setServoPosition(degStraight);
    motor.setMotorDirection(1);
    motor.setMotorSpeed(255);
    delay(1000); 

 }else{
    motor.stopMotor();
    delay(2000); 
    Serial.println("case  Stop");

 }

  

  /*if (distanceF < stopDist ) {
    // Stop the motor immediately
    motor.stopMotor();
    Serial.println("Distance Front is less than stop distance, stopping motor.");
    delay(2000);
  }

  else if (distanceF < wallDist) {
    rCount = rCount + 1;
    Serial.print("Rotation: ");
    Serial.println(rCount);

    motor.setMotorDirection(1); // rotate the motor in one direction
    motor.setMotorSpeed(200); // set the motor speed to maximum

    // Set the servo speed to control the movement speed
    servoController.setServoSpeed(10);  // Adjust the value as desired

    // Move the servo to a specific position
    servoController.setServoPosition(degStraight - degRange);  // Adjust the value as desired
    for (int i = 0; i <= 100; i++) {
        distanceF = ultraSensorF.getDistance();
       if (distanceF < stopDist ) {
       break;
        }
        delay(1); // wait for one second
         }
    
    servoController.setServoPosition(degStraight);  // Adjust the value as desired

       for (int i = 0; i <= 100; i++) {
        distanceF = ultraSensorF.getDistance();
        if (distanceF < stopDist ) {
       break;
        }
        delay(1); // wait for one second
         }

   Serial.println("case Left");

  } else if (distanceF > wallDist) {
    motor.setMotorDirection(1); // rotate the motor in one direction
    motor.setMotorSpeed(255); // set the motor speed to maximum
    // Set the servo speed to control the movement speed
    servoController.setServoSpeed(10);  // Adjust the value as desired
    // Move the servo to a specific position


 float deg=degStraight-degRange+distanceR*degRange/rightDist;

 if (deg >= degStraight + degRange){
  deg = degStraight + degRange;

 }

  // Move the servo to a specific position
  servoController.setServoPosition(deg);  // Adjust the value as desired

  Serial.print("deg: ");
  Serial.println(deg);
  Serial.println("case Forward");

   // Serial.println(deg);
    Serial.println("case Forward");
    delay(1); // wait for one second
  } else {
    motor.stopMotor(); // stop the motor
    delay(2000); // wait for one second
    Serial.println("case  Stop");

  }*/





}



