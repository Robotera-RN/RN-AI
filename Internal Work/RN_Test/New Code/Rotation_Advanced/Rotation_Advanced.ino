#include <RN.h>
#include <NewPing.h>

NewPing ultraSensorF(14, 15); // create an instance of RN class with trig pin 2 and echo pin 3
NewPing ultraSensorL(16, 17); // create an instance of RN class with trig pin 2 and echo pin 3
NewPing ultraSensorR(18, 19); // create an instance of RN class with trig pin 2 and echo pin 3
RN motor( 8, 9, 10); // create a new instance of the RN class

// Define the pin connected to the servo motor
const int servoPin = 2;
int degStraight = 80;
int degRange = 50;
int rCount = 0;
int wallDist = 80;
int stopDist = 40;
int rightDist=40;


// Create an instance of the RN library
RN servoController(servoPin);
// A function that checks the distance read by a sensor and returns a boolean value indicating whether it is within the required range
bool check_distance(int i){
 float f = ultraSensorF.ping_cm();
 float r = ultraSensorR.ping_cm();
 float l = ultraSensorL.ping_cm();
    Serial.print("Distance Front: ");
  Serial.print(f);
  Serial.print(" cm");
  Serial.print("  Distance Right: ");
  Serial.print(r);
  Serial.print(" cm");
  Serial.print("  Distance Left: ");
  Serial.println(l);
  switch(i){
    case 1:
      return f < 40 || r < 20 || l < 20;
      break;
    case 2:
      return l >= 20 && l < 40;
      break;
    case 3:
      return r >= 20 && r < 40;
      break;
    default:
      Serial.println("Forward");
      return f >= 40 && f < 80;
      break;
  }
}
// A function that sets the motor speed and direction and moves the servo motor to the desired angle
void move(int s,int d,int p){
   motor.setMotorDirection(d); // rotate the motor in one direction
    motor.setMotorSpeed(s); // set the motor speed to maximum
    // Move the servo to a specific position
    servoController.setServoPosition(p);  // Adjust the value as desired
    for (int i = 0; i <= 50; i++) {
      /* if (check_distance(1)) {
       break;
        } */
        delay(1); // wait for one second
         }

}
void setup() {
  Serial.begin(9600);
  servoController.Servobegin();
  rCount = 0;

}

void loop() {


  if(check_distance(1)){
    motor.stopMotor();
    Serial.println("Stop");
        servoController.setServoPosition(80);  // Adjust the value as desired

    delay(1000);
  }
  else if(check_distance(2)){
          Serial.println("Left");
  move(200,1,50);
   
  }
  else if(check_distance(3)){
              Serial.println("Right");

    move(200,1,110);
  }
   else if(check_distance(4)){
              Serial.println("Forward");

    move(200,1,80);
  
}
delay(1000);
}