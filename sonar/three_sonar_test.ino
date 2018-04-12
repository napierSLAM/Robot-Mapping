/*
  11/04/18
  Paddy
  Napier Robot SLAM
  Testing each sonar gives data
*/

#include <NewPing.h>

#define SONAR_NUM 3      // Number of sensors.
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
  delay(50);
  distance();
}

float distance() {
  Serial.print("left ");
  Serial.println(sonar[0].ping_cm());
  delay(50);
  Serial.print("middle ");
  Serial.println(sonar[1].ping_cm());
  delay(50);
  Serial.print("right ");
  Serial.println(sonar[2].ping_cm());
  delay(50);

}
