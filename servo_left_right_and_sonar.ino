#include <SR04.h>
#include <Servo.h>

#define TRIG_PIN 12
#define ECHO_PIN 11
#define MRSPEED 5 // motor right speed
#define MRDIRA 3 // motor right direction a
#define MRDIRB 4 // motor right dir b

#define MLSPEED 8 // motor left speed
#define MLDIRA 6 // motor left dir a
#define MLDIRB 7 // motor left dir b


SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long a; // a value for sonar reading
long b; // b value for sonar reading


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 90;    // variable to store the servo position
int maxDist = 0;
int maxAngle = 0;
int maxRight = 0;
int maxLeft = 0;
int maxFront = 0;
int course = 0;
int curDist = 0;
String motorSet = "";
int speedSet = 0;


void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(pos);
  
  pinMode(MRSPEED,OUTPUT);
  pinMode(MRDIRA,OUTPUT);
  pinMode(MRDIRB,OUTPUT);
  pinMode(MLSPEED,OUTPUT);
  pinMode(MLDIRA,OUTPUT);
  pinMode(MLDIRB,OUTPUT);
  Serial.begin(9600);  
}

void loop() {
   myservo.write(90); 
   a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");
   //delay(100);
  
    FORWARD();
  
    
   if (a<=20){
    STOP();
    pos=160;
    myservo.write(pos);
    a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");    
   delay(2000);
    pos=20;
    myservo.write(pos);
    b=sr04.Distance();
   Serial.print(b);
   Serial.println("cm");   
    delay(2000);
    if (a>=b){
      TURNLEFT();
      }
     else if (b>a) {
      TURNRIGHT();}    
     else if ((a<=20)||(b<=20)){TURNAROUND();
     
     delay(500);}
}}

void FORWARD(){
    Serial.println("Forward");
    analogWrite(MRSPEED,160); // enable on
    analogWrite(MLSPEED,160); // enable on
    digitalWrite(MRDIRA,HIGH); //one way
    digitalWrite(MLDIRA,HIGH); //one way
    digitalWrite(MRDIRB,LOW);    
    digitalWrite(MLDIRB,LOW);
    delay(500);
  }

void STOP(){
    Serial.println("Stop");    
    digitalWrite(MRDIRA,LOW); //one way
    digitalWrite(MLDIRA,LOW); //one way   
    delay(500);
  }

void TURNLEFT(){
    Serial.println("Turn Left");    
    analogWrite(MRSPEED,160); // enable on
    analogWrite(MLSPEED,160); // enable on
    digitalWrite(MRDIRA,HIGH); //one way
    digitalWrite(MLDIRA,LOW); //one way
    digitalWrite(MRDIRB,LOW);    
    digitalWrite(MLDIRB,HIGH);
    delay(600);
  }

void TURNRIGHT(){
    Serial.println("Turn Right");    
    analogWrite(MRSPEED,160); // enable on
    analogWrite(MLSPEED,160); // enable on
    digitalWrite(MRDIRA,LOW); //one way
    digitalWrite(MLDIRA,HIGH); //one way
    digitalWrite(MRDIRB,HIGH);    
    digitalWrite(MLDIRB,LOW);
    delay(600);
  }
  
void TURNAROUND(){
    Serial.println("Turnaround");    
    analogWrite(MRSPEED,160); // enable on
    analogWrite(MLSPEED,160); // enable on
    digitalWrite(MRDIRA,LOW); //one way
    digitalWrite(MLDIRA,HIGH); //one way
    digitalWrite(MRDIRB,HIGH);    
    digitalWrite(MLDIRB,LOW);
    delay(1200);
  }

