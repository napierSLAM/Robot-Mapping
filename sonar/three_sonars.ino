/*
  02/04/18
  Paddy
  Napier Robot SLAM
*/

#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PIN_1 11 // trigger/echo pin for sonar 1
#define PIN_2 12 // trigger/echo pin for sonar 2
#define PIN_3 13 // trigger/echo pin for sonar 3

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(PIN_1, PIN_1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(PIN_2, PIN_2, MAX_DISTANCE), 
  NewPing(PIN_3, PIN_3, MAX_DISTANCE)
};

void setup() {
  Serial.begin(9600); 
}

void loop() {
  distance();
}

float distance() { 
  int d = 0;
  float dist;
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor
    delay(50); // Wait 50ms between pings (about 20 pings/sec)
    d = d + sonar[i].ping_cm(); // sum 3 distances
  }
  dist = d/SONAR_NUM; //Get mean of distances
  Serial.println(dist);
}
