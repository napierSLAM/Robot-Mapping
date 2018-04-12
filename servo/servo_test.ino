/*
 * Napier SLAM Robot
 * 10/04/18
 * Paddy
 * Very simple servo function check
 */
#include <Servo.h> 

Servo myservo;

void setup() 
{ 
  myservo.attach(4);
  myservo.write(90);  // set servo to mid-point
} 

void loop() {} 

// we can use myservo.write(0) and myservo.write(180) for readings
