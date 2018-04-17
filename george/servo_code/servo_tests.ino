/*
 * Mapping Robot
 * George Oda
 * Cheching the movements of the servo 
 * 
 */

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  delay(100);
}

void loop() {
 
   myservo.write(pos); // goes to the left

   delay(3000); // wait 3sec
   pos=180;
   myservo.write(pos);
   
   delay(3000);
   pos=90;
   myservo.write(pos);
   
   delay(3000);
    }
      
      
}




