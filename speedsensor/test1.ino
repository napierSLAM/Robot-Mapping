/*
  Napier SLAM
  24/3/18
  Pat
  Single encoder test
  */



// Constant for Distance Interrupt Pin
const byte DIST_PIN = 2;

// Volatile int to hold slot counts
volatile int slotC = 0;



// Interrupt Service Routine for counting slots
void ISR_count()
{
  slotC++;  // increment slot count
}



void setup()
{
  // Attach the Interrupt to ISR, increasing count on high sensor
  attachInterrupt(digitalPinToInterrupt (DIST_PIN), ISR_count, RISING);
  Serial.begin(9600);
  delay(2000);
  Serial.println(slotC);

  
}


void loop()


}
