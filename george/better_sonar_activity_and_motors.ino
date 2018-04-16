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

int pos = 0;    // variable to store the servo position
int maxDist = 0;
int maxAngle = 0;
int maxRight = 0;
int maxLeft = 0;
int maxFront = 0;
int course = 0;
int curDist = 0;
String motorSet = "";
int speedSet = 0;
int fail = 0;

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(90);
  
  pinMode(MRSPEED,OUTPUT);
  pinMode(MRDIRA,OUTPUT);
  pinMode(MRDIRB,OUTPUT);
  pinMode(MLSPEED,OUTPUT);
  pinMode(MLDIRA,OUTPUT);
  pinMode(MLDIRB,OUTPUT);
  Serial.begin(9600);  
  delay(2000);
}

void loop() {
   pos=90;
   myservo.write(pos); 
   a=sr04.Distance();
   Serial.print(a);
   Serial.println("cm");
   delay(100); 
   if (a==0){a=fail;}
   
  
    
   if ((a<=20)&&(pos=90)&&(a!=fail)){
    STOP();
    pos=160;
    myservo.write(pos);
   long a1=sr04.Distance();
   delay(100);
   Serial.print(a1);
   Serial.println("cm");    
  long a2=sr04.Distance();
  delay(100);
   Serial.print(a2);
   Serial.println("cm");
  long a3=sr04.Distance();
  delay(100);
   Serial.print(a3);
   Serial.println("cm");
   long avra = (a1+a2+a3)/3;           
   delay(2000);
    pos=20;
    myservo.write(pos);
   long b1=sr04.Distance();
   delay(100);
   Serial.print(b1);
   Serial.println("cm");   
   long b2=sr04.Distance();
   delay(100);
   Serial.print(b2);
   Serial.println("cm");   
   long b3=sr04.Distance();
   delay(100);
   Serial.print(b3);
   Serial.println("cm");
   long avrb = (b1+b2+b3)/3;   
    delay(2000);
    if ((avra>=avrb)&&(avra>20)){
      TURNLEFT();
      STOP();
      }
     else if ((avrb>avra)&&(avrb>20)) {
      TURNRIGHT();
      STOP();}    
     else {TURNAROUND();
     STOP();
     
     delay(500);}
}else {FORWARD();}

}

void FORWARD(){
    Serial.println("Forward");
    analogWrite(MRSPEED,50); // enable on
    analogWrite(MLSPEED,50); // enable on
    digitalWrite(MRDIRA,HIGH); //one way
    digitalWrite(MLDIRA,HIGH); //one way
    digitalWrite(MRDIRB,LOW);    
    digitalWrite(MLDIRB,LOW);
    delay(500);
    }

void STOP(){
    Serial.println("Stop");    
    digitalWrite(MRSPEED,LOW); //one way
    digitalWrite(MLSPEED,LOW); //one way   
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

