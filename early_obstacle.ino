#include <Servo.h>              
#include <NewPing.h> 

#define PING_PIN   12
#define MAX_DISTANCE 200
#define COLL_DIST 20
#define WAIT 350

NewPing sonar(PING_PIN, PING_PIN, MAX_DISTANCE);
int curDist = 0;
int leftDistance, rightDistance;

Servo myservo; 

//set vars for motor pins
const int leftForward = 4;
const int leftBackward = 5;
const int rightForward = 6;
const int rightBackward = 7;

void setup() {
  myservo.attach(9);   
  myservo.write(90); 
  
  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);
  Serial.begin(9600);
  //Give sometime to get the battery in !
  delay(3000);
}

void loop() {
  myservo.write(90);  
  delay(90);
  curDist = readPing();  
  if (curDist < COLL_DIST) {changePath();}  
  forward();
  delay(200);
}

int readPing() { 
  delay(70);   
  unsigned int cm = sonar.ping_cm();
  return cm;
}

void changePath() {
  moStop();   
  myservo.write(0);  
  delay(200);
  leftDistance = readPing(); 
  delay(100);
  myservo.write(180);  
  delay(400);
  rightDistance = readPing(); 
  delay(100);
  myservo.write(90); 
  delay(100);
  compareDistance();
}

void compareDistance()  {
  if (leftDistance>rightDistance) {
    left();}
  else if (rightDistance>leftDistance) {
    right();}
} 

void forward(){
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);}


//turn left
void left(){
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);
  delay(WAIT);
}
 
//turn right
void right(){
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);
  delay(WAIT);
}

//Stopping the motors
void moStop(){
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);
}
