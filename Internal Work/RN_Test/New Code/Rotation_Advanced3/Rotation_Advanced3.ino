#include <RN.h>

RN ultraSensorF(14, 15); // create an instance of RN class with trig pin 2 and echo pin 3
RN ultraSensorR(16, 17); // create an instance of RN class with trig pin 2 and echo pin 3
RN ultraSensorL(18, 19); // create an instance of RN class with trig pin 2 and echo pin 3
RN motor( 8, 11, 12); // create a new instance of the RN class

// Define the pin connected to the servo motor
const int servoPin = 2;
int degStraight = 80;
int degRange = 50;
int rCount = 0;
int wallDist = 80;
int stopDist = 40;
int rightDist=40;
float f = 0;
float r = 0;
float l = 0;

// Create an instance of the RN library
RN servoController(servoPin);
// A function that checks the distance read by a sensor and returns a boolean value indicating whether it is within the required range

  
  


// A function that sets the motor speed and direction and moves the servo motor to the desired angle
void move(int s,int d,int p){
   motor.setMotorDirection(d); // rotate the motor in one direction
    motor.setMotorSpeed(s); // set the motor speed to maximum
    // Move the servo to a specific position
    servoController.setServoPosition(p);  // Adjust the value as desired
    
}

void delay_move(int dm , float fm , float rm , float lm){
for (int i = 0; i <= dm; i++) {
    if((fm > 0 && fm <= 30) || (rm > 0 && rm <= 5) || (lm > 0 && lm <= 5) ){
    move(0,1,85);
    Serial.println("Stop");
    delay(500);
    break;
      }
    else if(f == 0 || r == 0 || l == 0 ){
      Serial.println("Sensor Zero Value");
   }
   delay(1);
}}
void setup() {
  Serial.begin(9600);
  servoController.Servobegin();
 
}

void loop() {

  f = ultraSensorF.getDistance();
  r = ultraSensorR.getDistance();
  l = ultraSensorL.getDistance();
  Serial.print("Distance Front: ");
  Serial.print(f);
  Serial.print(" cm");
  Serial.print("  Distance Right: ");
  Serial.print(r);
  Serial.print(" cm");
  Serial.print("  Distance Left: ");
  Serial.println(l);

/* if(f > 100 && (r > 5 && r <= 30) && (l > 5 && l <= 80)){
    Serial.println("Left");
    move(200,1,60);
    delay_move(10,f,r,l);
   
  }
  else if(f > 100 && ( r > 5 && r <= 80) && (l > 5 && l <= 30)){
    Serial.println("Right");
    move(200,1,105);
    delay_move(10,f,r,l);
  }*/
move(200,1,87);
delay(1700);
//delay_move(1200,f,r,l);
move(200,1,50);
delay(1500);
//delay_move(750,f,r,l);


}