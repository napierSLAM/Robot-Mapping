/*
 * Napier SLAM Project
 * Testing each dc motor
 * Using an L239D IC driver
 * Nothing more than does it run in each direction
 * Can the speed be varied etc
 * Allows for checking pin placement and the like
 * Change pins as needed etc
 * 3/4/18
 * Paddy
 * George
 */

int en1 = 10; // motor one speed
int in1 = 9;  // motor one direction a
int in2 = 8;  // motor one dir direction b

//int en2 = 5;  // motor two speed
//int in3 = 6;  // motor two direction  a
//int in4 = 7;  // motor two direction b


// comment/uncomment as needed
void setup() {

  // motor one forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  //  motor two forward
//  digitalWrite(in3, HIGH);
//  digitalWrite(in4, LOW);

//  // motor one reverse
//  digitalWrite(in1, LOW);
//  digitalWrite(in2, HIGH);
//
//  //  motor two reverse
//  digitalWrite(in3, LOW);
//  digitalWrite(in4, HIGH);

  // set motors speed
  analogWrite(en1, 255);  // MAX
//  analogWrite(en2, 255);  // MAX
//  analogWrite(en1, 120);  // LOW
//  analogWrite(en2, 120);  // LOW
//  analogWrite(en1, 180);  // MID
//  analogWrite(en2, 180);  // MID

}

void loop() {
  // put your main code here, to run repeatedly:

}
