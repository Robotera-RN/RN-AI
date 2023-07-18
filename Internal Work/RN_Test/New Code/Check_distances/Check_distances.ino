#include <RN.h>
#include <NewPing.h>

NewPing ultraSensorF(14, 15); // create an instance of RN class with trig pin 2 and echo pin 3
NewPing ultraSensorL(16, 17); // create an instance of RN class with trig pin 2 and echo pin 3
NewPing ultraSensorR(18, 19); // create an instance of RN class with trig pin 2 and echo pin 3




void setup() {
  Serial.begin(9600);



}

void loop() {


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


}