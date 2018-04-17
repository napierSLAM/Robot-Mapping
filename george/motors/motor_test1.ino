/*
 * Mapping Robot
 * George Oda
 * Testing motors
 * 
 */

#define ENABLE 5
#define DIRA 3
#define DIRB 4

#define ENABLE1 8
#define DIRA1 6
#define DIRB1 7

int i;
 
void setup() {
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
  pinMode(ENABLE1,OUTPUT);
  pinMode(DIRA1,OUTPUT);
  pinMode(DIRB1,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  //---back and forth example
    Serial.println("One way, then reverse");
    digitalWrite(ENABLE,50); // enable on
    digitalWrite(ENABLE1,HIGH); // enable on
    
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRA1,LOW); //one way
    digitalWrite(DIRB,LOW);    
    digitalWrite(DIRB1,HIGH);
}
  
