/*
  13/04/18
  Paddy
  Napier Robot SLAM
  To test 2 sonars
*/

#include <NewPing.h>

#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define PIN_1 3 // trigger/echo pin for sonar 1
#define PIN_2 4 // trigger/echo pin for sonar 2

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(PIN_1, PIN_1, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(PIN_2, PIN_2, MAX_DISTANCE),
};

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);
  distance();
}

float distance() {
  Serial.print("right ");
  Serial.println(sonar[0].ping_cm());
  delay(500);
  Serial.print("left ");
  Serial.println(sonar[1].ping_cm());
  delay(500);

}
