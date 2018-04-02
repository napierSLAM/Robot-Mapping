/*
  Napier SLAM
  26/3/18
  Pat
  Start
*/

#include <Servo.h>              
#include <NewPing.h> 
#include <Wire.h>
#include <MechaQMC5883.h>


Servo myServo; // set up servo object
MechaQMC5883 compass; // set up compass object

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 300 // Maximum distance (in cm) to ping.
#define PIN_1 11 // trigger/echo pin for sonar 1
#define PIN_2 12 // trigger/echo pin for sonar 2
#define PIN_3 13 // trigger/echo pin for sonar 3
#define COLL_DIST 32 // Collision Distance

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(PIN_1, PIN_1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(PIN_2, PIN_2, MAX_DISTANCE), 
  NewPing(PIN_3, PIN_3, MAX_DISTANCE)
};

volatile int currentD = 0; // var to hold ping distance
volatile int leftD; // left distance to obstacle
volatile int rightD; // right distance to obstacle

volatile int currentB = 0; // var to hold bearing

/*
    BELOW IS FOR OUR BOT
    CHANGE AS NEEDED
    Wheel is 66.10 millimeters Diameter
    Circumference in mm is therefore (66.10 * pi) / 10
    = 208mm
    There are 20 slots in disk
    mm per step is therefore 208 / 20
    = 10.4
    As near as dammit 1cm
    so 10mm will be used
*/
// Constant for mm per slot (see above)
const float MM_SLOT = 10.0;

// Volatile int to hold slot counts
volatile int slotC = 0;

const byte DIST_PIN = 2;// Distance Interrupt Pin

// Pins for Right Motor
const byte en1 = 10;
const byte in1 = 9;
const byte in2 = 8;

// Pins for Left Motor
const byte en2 = 5;
const byte in3 = 6;
const byte in4 = 7;


// Interrupt Service Routine for counting slots
void ISR_count()
{
  slotC++;  // increment slot count
}

/*
   All the various functions
   Motion Etc
*/

// Function for getting distance to objects
float distance() { 
  int d = 0;
  float dist;
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor
    delay(50); // Wait 50ms between pings (about 20 pings/sec)
    d = d + sonar[i].ping_cm(); // sum 3 distances
  }
  dist = d/SONAR_NUM; //Get mean of distances
  return dist;
}


// Function for Forward Travel
void forward(int mSpeed)
{
  // reset slot count
  slotC = 0;

  // right motor forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // left motor forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // set motors speed
  analogWrite(en1, mSpeed);
  analogWrite(en2, mSpeed);
}

// Function for Reverse Travel
void reverse(int slots, int mSpeed)
{
  // reset slot count
  slotC = 0;

  // right motor reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // left motor reverse
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // go in reverse number of slots
  while (slots > slotC) {
    analogWrite(en1, mSpeed);
    analogWrite(en2, mSpeed);
  }

  // and stop :)
  mStop();
}

// Function to Turn Right
void right(int slots, int mSpeed)
{
  // reset slot count
  slotC = 0;

  // right motor reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // left motor forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // go right number of slots
  while (slots > slotC) {
    analogWrite(en1, mSpeed);
    analogWrite(en2, mSpeed);
  }

  // and stop :)
  mStop();
}

// Function to Turn Left
void left(int slots, int mSpeed)
{
  // right motor reverse
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // left motor forward
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // go left number of slots
  while (slots > slotC) {
    analogWrite(en1, mSpeed);
    analogWrite(en2, mSpeed);
  }
  
  // and stop :)
  mStop();
}

void mStop () {
  analogWrite(en1, 0);
  analogWrite(en2, 0);
}

// Function to check for direction to turn
void changePath() {
  mStop();   
  myServo.write(0);  
  delay(200);
  leftD = distance(); 
  delay(100);
  myServo.write(180);  
  delay(400);
  rightD = distance(); 
  delay(100);
  myServo.write(90); 
  delay(200);
  compareDistance();
}

// Function to change direction
void compareDistance() {
  if (leftD > rightD) {
    left(20, 190);}
  else  {
    right(20, 190);}
} 

// Function to get bearing
int bearing() {
  int x, y;
  int azimuth;
  azimuth = compass.azimuth(&y,&x);
  return azimuth;  
}

/*
   And we begin
*/
void setup()
{
  // Attach the Interrupt to ISR, increasing count on high sensor
  attachInterrupt(digitalPinToInterrupt (DIST_PIN), ISR_count, RISING);
  
  myServo.attach(4); //attach servo to pin 4 
  myServo.write(90); //center servo
  delay(100); // give it some time to get ready
  
  compass.init(); // initialise magnometer 
  
  Serial.begin(9600);

  // Bit of a breath before starting
  delay(3000);
}

void loop()
{
  currentD = distance();
  Serial.println(currentD);
  Serial.println("cm");
  Serial.println();
  currentB = bearing();
  Serial.println(currentB);
  Serial.println("degrees");
  Serial.println();
    
  if (currentD < COLL_DIST) {
    changePath();
    }  
  forward(200);
}
