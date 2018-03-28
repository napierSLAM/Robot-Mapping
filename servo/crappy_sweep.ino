#include <NewPing.h>
#include <Servo.h>

#define PING_PIN   12 // trigger/echo pin on ping sensor.
#define MAX_DISTANCE 200 
#define WAIT 400    // delay for turn, maybe use a while loop with magnetomer?
#define leftForward  4  // motor pins
#define leftBackward  5
#define rightForward  6
#define rightBackward  7

NewPing sonar(PING_PIN, PING_PIN, MAX_DISTANCE); 
const int minDist = 20;
int dist = minDist + 5;

Servo myServo;
const int servoMin = 80;
const int servoMax = 100;
int servPos = 90;   
int posDir = 0;     // servo direction flag
int sweepHalt = 0;  // halt sweep till finish turn

void setup() {

  pinMode(leftForward , OUTPUT);
  pinMode(leftBackward , OUTPUT);
  pinMode(rightForward , OUTPUT);
  pinMode(rightBackward , OUTPUT);
  myServo.attach(9);
  //Give sometime to get the battery in !
  delay(3000);
  NewPing::timer_ms(200, sweep); //Timer2 interrupt calls sweep every 100ms
  Serial.begin(9600);
}

void loop() {
  Serial.println(dist);
  //check distance for obstacle avoidance, 0 = nothing in range
  if ((dist > 0) && (dist < minDist)) {
    sweepHalt = 1; // stop sweeping
    moHalt();
    change();
  }
  forward();
}
void sweep () {
  if (sweepHalt == 0) {
    myServo.write(servPos);
    if (posDir == 0)  {
      servPos += 5;
    }
    else {
      servPos -= 5;
    }
    if (servPos == servoMax)  {
      dist = sonar.ping_cm();
      posDir = 1;
    }
    else if (servPos == 90)  {
      dist = sonar.ping_cm(); // needs 40ms, time for sweep may need tweaking
    }
    else if (servPos == servoMin) {
      dist = sonar.ping_cm();
      posDir = 0;
    }
  }
}

void change() {
  myServo.write(180);
  delay(200);
  int leftDist = sonar.ping_cm();
  delay(40);
  myServo.write(0);
  delay(400);
  int rightDist = sonar.ping_cm();
  delay(40);
  myServo.write(90);
  delay(200);
  //int frontDist = sonar.ping_cm();
  compareDistance(leftDist, rightDist);
}

void compareDistance(int leftDist, int rightDist)  {
  if (leftDist >= rightDist) {
    left();
  }
  else if (rightDist > leftDist) {
    right();
  }
}

// forward motion
void forward() {
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);
}

//turn left
void left() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, HIGH);
  digitalWrite(rightForward, HIGH);
  digitalWrite(rightBackward, LOW);
  delay(WAIT);  // when magnetomer set will use while != 90 degrees
  sweepHalt = 0; // start sweeping again
}

//turn right
void right() {
  digitalWrite(leftForward, HIGH);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, HIGH);
  delay(WAIT);
  sweepHalt = 0;
}

//Stopping the motors
void moHalt() {
  digitalWrite(leftForward, LOW);
  digitalWrite(leftBackward, LOW);
  digitalWrite(rightForward, LOW);
  digitalWrite(rightBackward, LOW);
}
