/*
  Napier SLAM
  10/04/18
  Pat
  2 optoencoders
*/


/*
    BELOW IS FOR OUR BOT
    CHANGE AS NEEDED
    Wheel is 66.10 millimeters Diameter
    Circumference in mm is therefore (66.10 * pi) / 10
    = 208mm
    There are 20 slots in disk
    mm per step is therefore 208 / 20
    = 10.4 mm
    1.04 cm
    As near as dammit 10mm
    So 10 will be used for distance travelled
*/

// Constant for mm per slot (see above)
const float MM_SLOT = 10;

// Constant for Right Motor INT 0 Pin
const byte RDIST_PIN = 2;
// Constant for Left Motor INT 1 Pin
const byte LDIST_PIN = 3;

// Volatile int to hold right slot count
volatile int RslotC = 0;
// Volatile int to hold right slot count
volatile int LslotC = 0;
//Volatile int to hold total forward slot count
volatile int TslotC = 0;
// Volatile int to hold distance to travel for each loop
volatile int steps = 0;

// Pins for Right Motor
// pwm
int en1 = 10;
int in1 = 9;
int in2 = 8;

// Pins for Left Motor
int en2 = 5;
int in3 = 6;
int in4 = 7;


// Interrupt Service Routines for counting slots
void ISR_countR()
{
  RslotC++;  // increment right slot count
}

void ISR_countL()
{
  LslotC++;  // increment left slot count
}


/*
   All the various functions
   Motion Etc
*/

// Function for Forward Travel
void forward(int mSpeed)
{
  // right motor forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  // left motor forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // reset slot count
  RslotC = 0;
  LslotC = 0;
  while (steps > RslotC && steps > LslotC) {
    if (steps > RslotC) {
      analogWrite(en1, mSpeed);
      Serial.println(RslotC);
    } else {
      analogWrite(en1, 0);
    }
    if (steps > LslotC) {
      analogWrite(en2, mSpeed);
      Serial.println(LslotC);
    } else {
      analogWrite(en2, 0);
    }
  }
  TslotC += RslotC; // store total forward slots
}

// Function for Reverse  Not currently used in bot program
void reverse(int mSpeed)
{
  int reverseSteps = 5;
  // right motor reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // left motor reverse
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  // reset slot count
  RslotC = 0;
  LslotC = 0;
  while (reverseSteps > RslotC && reverseSteps > LslotC) {
    if (reverseSteps > RslotC) {
      analogWrite(en1, mSpeed);
    } else {
      analogWrite(en1, 0);
    }
    if (steps > LslotC) {
      analogWrite(en2, mSpeed);
    } else {
      analogWrite(en2, 0);
    }
  }
  TslotC -= RslotC; // minus slot from forward
}

// Function to Turn Right
void right(int slots, int mSpeed)
{
  // right motor reverse
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  // left motor forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // go right number of slots
  // reset slot count
  RslotC = 0;
  LslotC = 0;
  while (steps > RslotC && steps > LslotC) {
    if (steps > RslotC) {
      analogWrite(en1, mSpeed);
    } else {
      analogWrite(en1, 0);
    }
    if (steps > LslotC) {
      analogWrite(en2, mSpeed);
    } else {
      analogWrite(en2, 0);
    }
  }
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
  RslotC = 0;
  LslotC = 0;
  while (steps > RslotC && steps > LslotC) {
    if (steps > RslotC) {
      analogWrite(en1, mSpeed);
    } else {
      analogWrite(en1, 0);
    }
    if (steps > LslotC) {
      analogWrite(en2, mSpeed);
    } else {
      analogWrite(en2, 0);
    }
  }
}

void mStop () {
  analogWrite(en1, 0);
  analogWrite(en2, 0);
}

/*
   And we begin
*/

void setup()
{
  // Attach the Interrupts to ISRs, increasing count on high sensor
  attachInterrupt(digitalPinToInterrupt (RDIST_PIN), ISR_countR, RISING);
  attachInterrupt(digitalPinToInterrupt (LDIST_PIN), ISR_countL, RISING);

  Serial.begin(9600);
  delay(2000);

}


void loop()
{
  forward(180);  // Forward at 255 speed
  delay(1000);  // Wait one second
  Serial.println(TslotC);
    //mStop();
  //  reverse(255);  // Reverse 10 steps at 255 speed
  //  delay(1000);  // Wait one second
  //  forward(150);
  //  delay(1000);  // Wait one second
  //  reverse(200);
  //  delay(1000);  // Wait one second
  //  right(12, 175);  // Spin right 12 steps at 175 speed
  //  delay(1000);  // Wait one second
  //  left(12, 175);  // Spin left 12 steps at 175 speed
}
