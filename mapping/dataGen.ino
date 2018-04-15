int x;
int y;
String data;
String sep = "*";
int count = 0;
int go = 0;


void setup() {
  Serial.begin(9600);
  establishContact();

}

void loop() {
  if (count < 1) {
    for (int i = 32; i <= 320; i = i + 32) {
      y = i; 
      for (int c = 64; c <= 320; c = c + 64) {
        x = c;
        data = x + sep + y;
        Serial.println(data);
      }
      count = count + 1;
    }
  }
}


void establishContact() {
  while (Serial.available() <= 0) {
    Serial.println('A');   // send a capital A
    delay(300);
  }
  go = 1;
  delay(500);
}




