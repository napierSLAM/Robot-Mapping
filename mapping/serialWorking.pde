/*
  15/04/18
  NapierSLAM
  Paddy 
  A basic script that listens for a token on the serial line
  If it recieves one, responds and then starts taking data of the line
  Data is in form of a string which is added into coords
  Coords then used to display a realtime map of location
  Needs a 32 x 32 image
  NO ERROR CHECKING
  NO REAL SANITY CHECKS
  IF MORE THAN ONE COM PORT IS IN USE ON YOUR DEVICE CHANGE LINE 32
  new Serial(this, Serial.list()[*], 9600)
  To get com ports - printArray(Serial.list())
*/


import processing.serial.*;

Serial talkingToClyde; //Serial object for bots data
String clydesBabble;   // Bots data
StringList coords = new StringList(); //StringList for bots data
boolean firstContact = false;  // Flag for comms state
PImage bot;   


void setup()
{
  background(0);
  size(544,544);
  bot = loadImage("robota32red.png");
  talkingToClyde = new Serial(this, Serial.list()[0], 9600); // com port may need changing
  talkingToClyde.bufferUntil('\n'); // Wait till newline before reading serial 
}

void draw() {
  if (firstContact == true)  { // wait for data
    cover();   // cover redraws all coords from coords
    moveBot(); // movebot draws bot at location of last coords recieved
  }
}


void cover()  {
  for (int i = 0; i < coords.size(); i++)  { // iterate through all strings
    String[] rawBabble = split(coords.get(i),"*"); // split strings on *
    int a = int(rawBabble[0]); // assign to temp cords
    int b = int(rawBabble[1]); 
    noStroke();
    fill(255); // white
    rect(a, b, 64, 32); // draw rectangle
  }
}

void moveBot() {
  if (coords.size() > 0)  { // legacy sanity check 
    String[] botCords = split(coords.get(coords.size() - 1),"*"); // current coords
    int bX = int(botCords[0]); 
    int bY = int(botCords[1]);
    image(bot, bX + 16, bY); // Draw bot image, the 16 is to position bot slightly better
  }
}

void serialEvent(Serial p) {
  if (firstContact == false) {   // Comms not established 
    if (p.read() == 'A') {       // Check for token
      talkingToClyde.write('A'); // Respond to token
      talkingToClyde.clear();    // Clear line ready to start
      firstContact = true;       // Change comms state flag
    }
  }
   else {        // Comms established
    clydesBabble = p.readString().trim(); // Take data off serial
    // println("clydesBabble = " + clydesBabble);  
    coords.append(clydesBabble); // Add data to string list 
    talkingToClyde.clear();  // Clear serial ready for next set of coords
   }
}
