#include <RN.h>
#include <NewPing.h>

RN ultraSensorF(14, 15); // create an instance of RN class with trig pin 2 and echo pin 3
RN ultraSensorL(16, 17); // create an instance of RN class with trig pin 2 and echo pin 3
RN ultraSensorR(18, 19); // create an instance of RN class with trig pin 2 and echo pin 3




void setup() {
  Serial.begin(9600);



}

void loop() {


  float f = ultraSensorF.getDistance();
  float r = ultraSensorR.getDistance();
  float l = ultraSensorL.getDistance();
  Serial.print("Distance Front: ");
  Serial.print(f);
  Serial.print(" cm");
  Serial.print("  Distance Right: ");
  Serial.print(r);
  Serial.print(" cm");
  Serial.print("  Distance Left: ");
  Serial.println(l);
 

}