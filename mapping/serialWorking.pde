import processing.serial.*;

Serial talkingToClyde; //Serial object for bots data
String clydesBabble;   // Bots data
StringList coords = new StringList();
boolean firstContact = false;
PImage bot;

void setup()
{
  background(0);
  size(544,544);
  bot = loadImage("robota32red.png");
  println("coords start = " + coords);
  talkingToClyde = new Serial(this, Serial.list()[0], 9600);
  talkingToClyde.bufferUntil('\n');
  
}

void draw() {
  if (firstContact == true)  {
    cover();
    moveBot();
  }
}

void cover()  {
  for (int i = 0; i < coords.size(); i++)  {
    String[] rawBabble = split(coords.get(i),"*");
    int a = int(rawBabble[0]);
    int b = int(rawBabble[1]); 
    noStroke();
    fill(255);
    rect(a, b, 64, 32);
  }
}

void moveBot() {
  if (coords.size() > 0)  {
    String[] botCords = split(coords.get(coords.size() - 1),"*");
    int bX = int(botCords[0]);
    int bY = int(botCords[1]);
    image(bot, bX + 16, bY); 
  }
}


void serialEvent(Serial p) {
  if (firstContact == false) {
    if (p.read() == 'A') {
      talkingToClyde.write('A');
      talkingToClyde.clear();
      firstContact = true;
    }
      }
   else {    
    clydesBabble = p.readString().trim();
    println("clydesBabble = " + clydesBabble);  
    coords.append(clydesBabble);
    talkingToClyde.clear();
   }
}
