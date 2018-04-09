/*
  Napier SLAM
  26/3/18
  Pat
  Start
*/


/*
    BELOW IS FOR OUR BOT
    CHANGE AS NEEDED
    Wheel is 66.10 millimeters Diameter
    Circumference in mm is therefore (66.10 * pi) / 10
    = 208mm
    There are 20 slots in disk
    mm per step is therefore 208 / 20
    = 10.4
    So this will be used for distance travelled
*/

// Constant for mm per slot (see above)
const float MM_SLOT = 10.4;

// Constant for Distance Interrupt Pin
const byte DIST_PIN = 2;

// Volatile int to hold slot counts
volatile int slotC = 0;

// Pins for Right Motor
// pwm
int en1 = 10;
int in1 = 9;
int in2 = 8;

// Pins for Left Motor
int en2 = 5;
int in3 = 6;
int in4 = 7;


// Interrupt Service Routine for counting slots
void ISR_count()
{
  slotC++;  // increment slot count
}

/*
   All the various functions
   Motion Etc
*/

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

  // stop :)
  analogWrite(en1, 0);
  analogWrite(en2, 0);
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

  // stop :)
  analogWrite(en1, 0);
  analogWrite(en2, 0);
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

  // stop :)
  analogWrite(en1, 0);
  analogWrite(en2, 0);
}


/*
   And we begin
*/

void setup()
{
  // Attach the Interrupt to ISR, increasing count on high sensor
  attachInterrupt(digitalPinToInterrupt (DIST_PIN), ISR_count, RISING);

  // testing below
  forward(255);  // Forward at 255 speed
  delay(1000);  // Wait one second
  reverse(10, 255);  // Reverse 10 steps at 255 speed
  delay(1000);  // Wait one second
  forward(150);  // Forward 10 steps at 150 speed
  delay(1000);  // Wait one second
  reverse(10, 200);  // Reverse 25.4 cm at 200 speed
  delay(1000);  // Wait one second
  right(12, 175);  // Spin right 20 steps at 255 speed
  delay(1000);  // Wait one second
  left(12, 175);  // Spin left 60 steps at 175 speed
}


void loop()
{

}
