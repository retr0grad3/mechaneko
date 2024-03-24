void setup() {
  // put your setup code here, to run once:
  pinMode(7,INPUT);
  pinMode(13,OUTPUT);

  digitalWrite(13,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(7)==LOW) {
    digitalWrite(13,HIGH);
  } else {
    digitalWrite(13,LOW);
  }
}
