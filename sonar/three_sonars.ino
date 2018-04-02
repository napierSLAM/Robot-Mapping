// ---------------------------------------------------------------------------
// Example NewPing library sketch that pings 3 sensors 20 times a second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PIN_1 11 // trigger/echo pin for sonar 1
#define PIN_2 12 // trigger/echo pin for sonar 2
#define PIN_3 13 // trigger/echo pin for sonar 3

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(4, 5, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(6, 7, MAX_DISTANCE), 
  NewPing(8, 9, MAX_DISTANCE)
};

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

float distance() { 
  int d = 0
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    d = d + sonar[i].ping_cm();
    float distance = d/SONAR_NUM;
  }
  Serial.println(distance);
}
