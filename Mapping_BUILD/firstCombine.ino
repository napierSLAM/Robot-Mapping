/*
   15/4/18
   NapierSLAM
   Paddy
   All other code put together
*/

#include <NewPing.h>
// set up sonar objects
#define FSONAR_NUM 3      // Num sensors in front array
#define SSONAR_NUM 2      // Num sensors in side array
#define MAX_DISTANCE 350  // Maximum distance (in cm) to ping.
#define PIN_1 11          // Trigger/echo pin for sonar 1
#define PIN_2 12          // Trigger/echo pin for sonar 2
#define PIN_3 13          // Trigger/echo pin for sonar 3
#define PIN_4 3           // Trigger/echo pin for sonar 4
#define PIN_5 4           // Trigger/echo pin for sonar 5

volatile int dist;   // var to hold pings
volatile int dist;   // var to hold pings
byte collision = 32; // closest distance in cm that the bot will be to an object

NewPing front_Sonar[FSONAR_NUM] = {   // Front sonar array object
  NewPing(PIN_1, PIN_1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(PIN_2, PIN_2, MAX_DISTANCE),
  NewPing(PIN_3, PIN_3, MAX_DISTANCE)
};

// Side sonar objects
NewPing right_Sonar(PIN_4, PIN_4, MAX_DISTANCE);
NewPing left_Sonar(PIN_5, PIN_5, MAX_DISTANCE);


// Function to get distance to obstacles using 3 sonar array
void fDistance() {
  float sumDist = 0;
  for (uint8_t i = 0; i < FSONAR_NUM; i++) { // Loop through each sensor
    delay(50); // Wait 50ms between pings (about 20 pings/sec)
    int d = front_Sonar[i].ping_cm(); // ping each sonar
    if (d <= collision)  { // check if any sonars are reading seeing a collision
      dist = d;
      break;
    }
    else {
      sumDist = sumDist + d;
    }
  }
  dist = sumDist / FSONAR_NUM; // Get mean of distances
  Serial.println(dist); // error check
}

// Get side distances
int sDistance() {
  int r = right_Sonar.ping_cm();
  delay(50);
  int l = left_Sonar.ping_cm();
  Serial.print("right ");
  Serial.println(r);
  Serial.print("left ");
  Serial.println();
  return l;
  return r;
}

void setup() {
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

}
