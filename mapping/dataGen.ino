/*
 * 15/4/18
 * NapierSLAM
 * Paddy
 * Coord generator
 * Sends a stream of tokens down serial until a rsponse is recieved
 * Then generates and sends x,y coords down the serial with * as a seperator
 * To be safer, should change a flag on contact but meh
 */


int x;
int y;
String data;
String sep = "*";
int count = 0;

void setup() {
  Serial.begin(9600);
  establishContact();
}

void loop() {
  if (count < 1) { // One set of data
    for (int i = 32; i <= 320; i = i + 32) { 
      y = i; 
      for (int c = 64; c <= 320; c = c + 64) {
        x = c;
        data = x + sep + y; // create string
        Serial.println(data); // send down line
      }
      count = count + 1;
    }
  }
}

void establishContact() {
  while (Serial.available() <= 0) { // If nothing heard
    Serial.println('A');   // send stream of tokens
    delay(300);
  }
  delay(500); // Give some time to settle
}
// This to shall pass
