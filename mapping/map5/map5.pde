/*
 * 2/4/18
 * Napier Slam
 * Rough Look at Mapping Display
 * Paddy
*/


int [] [] readings = {  
                        {64,64},{128,64},{192,64},{256,64},{320,64},
                        {320,96},{256,96},{192,96},{128,96},{64,96},
                        {64,128},{128,128},{192,128},{256,128},{320,128},
                        {320,160},{256,160},{192,160},{128,160},
                        {128,192},{192,192},{256,192},{320,192},{384,192},
                        {384,224},{320,224},{256,224},{192,224},{128,224},
                        {128,256},{192,256},{256,256},{320,256},{384,256},
                        {384,288},{320,288},{256,288},{192,288},{128,288},{64,288},
                        {64,320},{128,320},{192,320},{256,320},{320,320},{384,320},
                        {384,352},{320,352},{256,352},{192,352},{128,352},{64,352},
                        {64,384},{128,384},{192,384},{256,384},{320,384},{384,384},
                        {384,416},{320,416},{256,416},{192,416},{128,416},
                        {128,448},{192,448},{256,448},{320,448},{384,448},                        
                      };

PImage bot, Rbot, Lbot;
int x, y;
int arrayI = 0;

void setup() {
  //println(readings[1].length);
  //for (int[] val : readings) {
  //println(val);
  //}
  frameRate(2);
  size(512,512);
  Rbot = loadImage("robota32red_R.png");
  Lbot = loadImage("robota32red_L.png");
  bot = Rbot;

}

void draw() {
  if (arrayI < readings.length)  {     
    background(0);      
    x = readings[arrayI][0];
    y = readings[arrayI][1];   
    cover();
    if (arrayI != 0) {
      if (readings[arrayI][0] == readings[arrayI-1][0])  {
        if (bot == Rbot)  {
          bot = Lbot;
        }  else {
          bot = Rbot;
            }
       }
     }
    moveBot();
    arrayI++;
  }
}

void cover()  {
  int i = 0;
  while (i < arrayI + 1)  {
    int a = readings[i][0];
    int b = readings[i][1];
    i++;
    noStroke();
    fill(255);
    rect(a, b, 64, 32);
  }
}

void moveBot() {
  image(bot, x + 16, y); 
}
