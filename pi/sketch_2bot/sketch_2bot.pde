PImage bot;
float y;
float x;
float speed = 1;

void setup() {
  size(500, 500);
  y = height;
  x = width;
  bot = loadImage("robota32red.png");
}

void draw() {
  background(0);
  move();
  display();

}

void move() {
  y = y - speed;
  if (y == 0) {
    y = height;
  }
}

void display() {
  imageMode(CENTER);
  image(bot, x/2, y);
}
