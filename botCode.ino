/*
   15/4/18
   NapierSLAM
   Paddy
   All other code put together
*/

#include <NewPing.h>

#define FSONAR_NUM 3      // Number of sonars in front array
#define SSONAR_NUM 2      // Number of sonars in side array
#define MAX_DISTANCE 350  // Maximum distance (in cm) to ping.
#define PIN_1 11          // Trigger/echo pin for sonar 1
#define PIN_2 12          // Trigger/echo pin for sonar 2
#define PIN_3 13          // Trigger/echo pin for sonar 3
#define PIN_4 3           // Trigger/echo pin for sonar 4
#define PIN_5 4           // Trigger/echo pin for sonar 5

volatile int dist;   // var to hold front pings
int r;      // var to hold right pings
int l;      // var to hold right pings
byte collision = 32; // closest distance in cm that the bot will be to an object

NewPing front_Sonar[FSONAR_NUM] = {    // Front sonar array object
  NewPing(PIN_1, PIN_1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(PIN_2, PIN_2, MAX_DISTANCE),
  NewPing(PIN_3, PIN_3, MAX_DISTANCE)
};

NewPing right_Sonar(PIN_4, PIN_4, MAX_DISTANCE);   // Side sonar objects
NewPing left_Sonar(PIN_5, PIN_5, MAX_DISTANCE);

boolean contact = false;  // handshake flag

byte en1 = 10; // motor one speed pin
byte in1 = 9;  // motor one direction a pin
byte in2 = 8;  // motor one dir direction b pin

byte en2 = 5;  // motor two speed pin
byte in3 = 6;  // motor two direction a pin
byte in4 = 7;  // motor two direction b pin

const byte DIST_PIN = 2;    // Constant for Distance Interrupt Pin
volatile int slotC = 0;     // Volatile int to hold slot counts

const byte rM = 215;    // Constant for right motor speed
const byte lM = 235;    // Constant for left motor speed
const byte tRM = 187;   // Constant for turning right motor speed
const byte tLM = 200;   // Constant for turning left motor speed

const byte tSlots = 13; // Constant for number of slots to turn
byte hand = 0;          // Direction bot facing

int x = 0;              // int for x coord
int y = 0;              // int for y coord

String data;            // string to send down serial
const String sep = "*"; // seperator for serial data

void fDistance()  // Function to get distance to obstacles using 3 sonar array
{
  float sumDist = 0;
  for (uint8_t i = 0; i < FSONAR_NUM; i++) { // Loop through each sensor
    delay(50);                               // 50ms between pings
    int d = front_Sonar[i].ping_cm();        // ping each sonar
    if (d <= collision)  {                   // check if any sonars are reading a collision
      dist = d;
      break;
    }
    else {
      sumDist = sumDist + d;
    }
  }
  dist = sumDist / FSONAR_NUM; // Get mean of distances
}

void sDistance()  // Get side distances
{
  r = right_Sonar.ping_cm();
  delay(50);
  l = left_Sonar.ping_cm();
}

void forward(byte rSpeed, byte lSpeed)  // Function for Forward Travel
{
  digitalWrite(in1, HIGH);  // right motor forward
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);  // left motor forward
  digitalWrite(in4, LOW);
  analogWrite(en1, rSpeed); // set motors speed
  analogWrite(en2, lSpeed);
}

void reverse(byte rSpeed, byte lSpeed)  // Function for Reverse Travel (not used in this implementation)
{
  digitalWrite(in1, LOW);   // right motor reverse
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);   // left motor reverse
  digitalWrite(in4, HIGH);
  analogWrite(en1, rSpeed); // set motors speed
  analogWrite(en2, lSpeed);
}

void right(byte slots, byte rSpeed, byte lSpeed) // Function to Turn Right
{
  // reset slot count
  slotC = 0;
  digitalWrite(in1, LOW);   // right motor reverse
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);  // left motor forward
  digitalWrite(in4, LOW);

  while (slots > slotC) {   // go right number of slots
    analogWrite(en1, rSpeed);
    analogWrite(en2, lSpeed);
  }
  halt();
  slotC = 0;
}

void left(byte slots, byte rSpeed, byte lSpeed)  // Function to Turn Left
{
  slotC = 0;
  digitalWrite(in1, HIGH);   // right motor forward
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);  // left motor reverse
  digitalWrite(in4, HIGH);

  while (slots > slotC) {   // go left number of slots
    analogWrite(en1, rSpeed);
    analogWrite(en2, lSpeed);
  }
  halt();
  slotC = 0;
}

void halt()   // stop :)
{
  analogWrite(en1, 0);
  analogWrite(en2, 0);
}

void turnSide()  // decide which side to turn to
{
  sDistance();   // call side sonars
  if (r >= l)  {
    right(tSlots, tRM, tLM);
    hand = (hand + 5) % 4;
  }
  else if {l > r) {
    left(tSlots, tRM, tLM);
    hand = (hand + 3) % 4;
  }
  slotC = 0;  // reset slots
}

void coordUpdate() // updates coords and sends them down the serial line
{
  if (hand == 0)  {
    x = x + slotC;
  }
  else if (hand == 1)  {
    y = y + slotC;    
  }
  else if (hand == 2)  {
    x = x - slotC;
  }
  else  {
    y = y - slotC;
  }
  data = x + sep + y; // create string
  Serial.println(data); // send down line
}

void ISR_count() // set up interrupt
{
  slotC++;       // increment slot count
}


void setup() {
  // Attach the Interrupt to ISR, increasing count on rising signal
  attachInterrupt(digitalPinToInterrupt (DIST_PIN), ISR_count, RISING);
  Serial.begin(9600);
  establishContact();
}

void loop() {
  if (contact == true)  {
    fDistance();
    if (dist > 32 || slotC < 16)  {
      forward(rM, lM);
    }
    else if (dist <= 32)  {
      halt();
      coordUpdate();
      turnSide();
    }
    else if (slotC >= 16) {
      coordUpdate();
    }
  }
}

void establishContact() {      // handshake with serial device
  while (Serial.available() <= 0) {    // If nothing heard
    Serial.println('A');               // send stream of tokens
    delay(300);
  }
  contact = true; //  set contact flag
  delay(500);     // Give some time to settle
}
// This t00 shall pass
