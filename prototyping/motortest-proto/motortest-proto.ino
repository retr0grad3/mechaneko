int in1 = 42;
int in2 = 44;
int enA = 40;

int in3 = 46;
int in4 = 48;
int enB = 50;

void setup(){
    
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

}

void loop(){
  
  digitalWrite(in1, HIGH); // move forward for 1.5s
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);

  digitalWrite(in1, LOW); // stop for 0.5s
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 0);
  digitalWrite(enB, 0);
  delay(500);

  digitalWrite(in1, LOW); // move forward for 1.5s
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);

  digitalWrite(in1, LOW); // stop for 0.5s
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  digitalWrite(enA, 0);
  digitalWrite(enB, 0);
  delay(500);

  /*
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);

  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(3000);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);

  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(3000);
  */
}