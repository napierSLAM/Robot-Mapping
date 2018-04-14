import processing.serial.*;

Serial talkingToClyde; //Serial object for bots data
String clydesBabble;   // Bots data
int xPos = 0, yPos = 0;
int cXPos, cYPos;
ArrayList<PVector> coords = new ArrayList<PVector>();
PVector botCoords = new PVector(xPos, yPos);
PImage bot, Rbot, Lbot;

void setup()
{
  frameRate(2);
  size(512,512);
  Rbot = loadImage("robota32red_R.png");
  Lbot = loadImage("robota32red_L.png");
  bot = Rbot;
  talkingToClyde = new Serial(this, Serial.list()[0], 9600);
  talkingToClyde.bufferUntil('\n');
}

void draw() {
  background(0);
  for (int i = 0; i < coords.size(); i++) {
    cXPos = int(coords.get(i).x);
    cYPos = int(coords.get(i).y);
    cover();
    if ((cXPos + cYPos) != 0) {
      if (cXPos == int(coords.get(i-1).y)) {
        if (bot == Rbot) {
          bot = Lbot;
        }  else {
          bot = Rbot;
        }
       }
     }
    moveBot();
  }
}      
      
void cover()  {
  for (int i = 0; i < coords.size(); i++)  {
    int a = int(coords.get(i).x);
    int b = int(coords.get(i).y);
    noStroke();
    fill(255);
    rect(a, b, 64, 32);
  }
}

void moveBot() {
  image(bot, cXPos + 16, cYPos); 
}

void serialEvent(Serial p) {
  clydesBabble = p.readString();  
  populateArray();
}

void populateArray()
{
  clydesBabble = clydesBabble.trim();
  String[] rawBabble = split(clydesBabble,",");
  xPos = int(rawBabble[0]);
  yPos = int(rawBabble[1]); 
  botCoords.set(xPos, yPos);
  coords.add(botCoords);
}
  
