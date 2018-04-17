/*
 * Mapping Robot
 * George Oda
 * Cheching the movements of the servo with the sonar attached
 * 
 */
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a;

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // set to middle

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  delay(100);
}

void loop() {
 
    pos=90; 
    myservo.write(pos); // goes to middle
    a=sr04.Distance(); 
   Serial.print(a);
   Serial.println("cm"); // print the distance in cm
    delay(100);
    if (a<20){ // if an object is less than 20 cm closer the servo moves to 180 position
    pos=180;
    myservo.write(pos);
    a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");
    
    delay(2000);
    pos=0;
    myservo.write(pos);
    a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");
   
    delay(2000);
    }
      
      
}




