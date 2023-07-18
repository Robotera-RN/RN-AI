#include <RN.h>

RN ultraSensorF(14, 15); // create an instance of RN class with trig pin 2 and echo pin 3
RN ultraSensorL(16, 17); // create an instance of RN class with trig pin 2 and echo pin 3
RN ultraSensorR(18, 19); // create an instance of RN class with trig pin 2 and echo pin 3
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
  float f = ultraSensorF.getDistance();
  float r = ultraSensorR.getDistance();
  float l = ultraSensorL.getDistance();
  /*Serial.print("Distance Front: ");
  Serial.print(f);
  Serial.print(" cm");
  Serial.print("  Distance Right: ");
  Serial.print(r);
  Serial.print(" cm");
  Serial.print("  Distance Left: ");
  Serial.println(l);*/
  
  bool condition = false;
  
  switch(i){
    case 1:
      Serial.print(" Case: 1");
      condition = f < 40 || r < 20 || l < 20;
      Serial.print("condition: ");
      Serial.println(condition);
      return condition;
      break;
    case 2:
      Serial.print(" Case: 2");
      condition = l >= 20 && l <= 40;
      Serial.print("condition: ");
      Serial.println(condition);
      return condition;
      break;
    case 3:
      Serial.print(" Case: 3");
      condition = r >= 20 && r <= 40;
      Serial.print("condition: ");
      Serial.println(condition);
      return condition;
      break;
    case 4:
      Serial.print(" Case: 4");
      condition = f >= 40 && f <= 80 && r > 40 && l > 40;
      Serial.print("condition: ");
      Serial.println(condition);
      return condition;
      break;
      case 5:
      Serial.print(" Case: 5");
      condition = f > 80 && r > 40 && l > 40;
      Serial.print("condition: ");
      Serial.println(condition);
      return condition;
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
              Serial.println("Left2");

      move(200,1,50);
      
  
}
  else if(check_distance(5)){
              Serial.println("Forward");

      move(200,1,80);
      
  
}
  else{
    motor.stopMotor();
    Serial.println("Stop2");
    delay(1000);
  }


}