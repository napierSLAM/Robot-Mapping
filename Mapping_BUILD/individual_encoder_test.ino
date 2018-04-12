/*
 * Napier SLAM Project
 * Testing opto encoders
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


// Constant for Distance Interrupt Pin
const byte DIST_PIN = 2;
// const byte DIST_PIN = 3; // uncomment to check left

// Volatile int to hold slot counts
volatile int slotC = 0;

void ISR_count()
{
  slotC++;  // increment slot count
}

// comment/uncomment as needed
void setup() {
  
   // Attach the Interrupt to ISR, increasing count on high sensor
  attachInterrupt(digitalPinToInterrupt (DIST_PIN), ISR_count, RISING);
  
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
    Serial.println(slotC);
}
