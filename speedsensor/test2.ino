/*
  Napier SLAM
  9/4/18
  Paddy
  Two encoder test
  */


// Constant for Right Motor INT 0 Pin
const byte RDIST_PIN = 2;
// Constant for Left Motor INT 1 Pin
const byte LDIST_PIN = 3;

// Volatile ints to hold slot counts
volatile int RslotC = 0;

// Volatile ints to hold slot counts
volatile int LslotC = 0;

// Interrupt Service Routines for counting slots
void ISR_countR()
{
  RslotC++;  // increment right slot count
}

void ISR_countL()
{
  LslotC++;  // increment left slot count
}

void setup()
{
  attachInterrupt(digitalPinToInterrupt (RDIST_PIN), ISR_countR, RISING);
  attachInterrupt(digitalPinToInterrupt (LDIST_PIN), ISR_countL, RISING);
  Serial.begin(9600);
  delay(1000);
}

void loop(){
  Serial.print("Right ");
  Serial.println(RslotC);
  Serial.print("Left ");
  Serial.println(LslotC);
}
