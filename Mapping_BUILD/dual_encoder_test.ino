/*
 * Napier SLAM Project
 * Testing Part two opto encoders
 * Counts slots and displays them on serial lone
 * Allows for checking pin placement and the like
 * Change pins as needed etc
 * 3/4/18
 * Paddy
 * George
 */

int en1 = 10; // motor one speed
int in1 = 9;  // motor one direction a
int in2 = 8;  // motor one dir direction b

int en2 = 5;  // motor two speed
int in3 = 6;  // motor two direction  a
int in4 = 7;  // motor two direction b


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


// comment/uncomment as needed
void setup() {
  
  attachInterrupt(digitalPinToInterrupt (RDIST_PIN), ISR_countR, RISING);
  attachInterrupt(digitalPinToInterrupt (LDIST_PIN), ISR_countL, RISING);
  
  Serial.begin(9600);
  delay(1000);

    // motor one forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

    // motor two forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  // set motor speed
  analogWrite(en1, 180);
  analogWrite(en2, 180); 
}

void loop() {
  Serial.print("Right ");
  Serial.println(RslotC);
  Serial.print("Left ");
  Serial.println(LslotC);
}
