/*
   Napier SLAM Project
   Testing opto encoders
   Counts slots and displays them on serial lone
   Allows for checking pin placement and the like
   Change pins as needed etc
   3/4/18
   Paddy
   George
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
  delay(300);

}

void loop() {
  if (slotC < 200) {
    // motors forward
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    analogWrite(en1, 186);
    analogWrite(en2, 200);
    Serial.println(slotC);
  }
  else if (slotC < 400) {
    // motors reverse
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    analogWrite(en1, 186);
    analogWrite(en2, 200);
    Serial.println(slotC);
  }
  analogWrite(en1, 0);
  analogWrite(en2, 0);
}

