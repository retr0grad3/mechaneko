int dirDown = 53;
int dirUp = 51;
int dirRight = 49;
int dirLeft = 47;
// u51 d53 r49 l47
void setup() {
  // put your setup code here, to run once:

  pinMode(dirDown, INPUT_PULLUP);
  pinMode(dirUp, INPUT_PULLUP);
  pinMode(dirLeft, INPUT_PULLUP);
  pinMode(dirRight, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:

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
