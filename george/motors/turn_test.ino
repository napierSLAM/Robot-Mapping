/*
 * Mapping Robot
 * George Oda
 * Test turning
 * 
 */
 
#define MRSPEED 5 // motor right speed
#define MRDIRA 3 // motor right direction a
#define MRDIRB 4 // motor right dir b

#define MLSPEED 8 // motor left speed
#define MLDIRA 6 // motor left dir a
#define MLDIRB 7 // motor left dir b







void setup() {
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
  TURNLEFT();
delay(400);
  STOP();
  delay(3000);
}


void TURNLEFT(){
    Serial.println("Turn Left");    
    analogWrite(MRSPEED,160); // enable on
    analogWrite(MLSPEED,160); // enable on
    digitalWrite(MRDIRA,HIGH); //one way
    digitalWrite(MLDIRA,LOW); //one way
    digitalWrite(MRDIRB,LOW);    
    digitalWrite(MLDIRB,HIGH);    
  }
  
void STOP(){
    Serial.println("Stop");    
    digitalWrite(MRSPEED,LOW); //one way
    digitalWrite(MLSPEED,LOW); //one way   
    
  }
