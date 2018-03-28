#include <Servo.h> 

Servo myservo;

void setup() 
{ 
  myservo.attach(9);
  myservo.write(90);  // set servo to mid-point
} 

void loop() {} 

// we can use myservo.write(0) and myservo.write(180) for readings
