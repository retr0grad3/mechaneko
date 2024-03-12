/* 

Credit to Maker Tutor on Youtube

Simple serial output of joystick position

*/

// u51 d53 r49 l47
int dirDown = 53;
int dirUp = 51;
int dirRight = 49;
int dirLeft = 47;

void setup() {
  
  pinMode(dirDown, INPUT_PULLUP);
  pinMode(dirUp, INPUT_PULLUP);
  pinMode(dirLeft, INPUT_PULLUP);
  pinMode(dirRight, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  
  if(digitalRead(dirDown) == LOW){
    Serial.println("DOWN");
  } else if(digitalRead(dirUp) == LOW){
    Serial.println("UP");
  } else if(digitalRead(dirLeft) == LOW){
    Serial.println("LEFT");
  } else if(digitalRead(dirRight) == LOW){
    Serial.println("RIGHT");
  } else {
    Serial.println("CENTER");

    delay(100);
  }

}
