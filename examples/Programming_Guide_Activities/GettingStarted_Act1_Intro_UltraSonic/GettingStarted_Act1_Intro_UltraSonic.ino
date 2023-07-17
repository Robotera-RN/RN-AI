#include <RN.h>

RN sensor(14, 15); // create an instance of RN class with trig pin 2 and echo pin 3

void setup() { 
  Serial.begin(9600);
}

void loop() {
  float distance = sensor.getDistance();
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  delay(1000);
}
