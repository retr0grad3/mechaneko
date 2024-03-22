# 1 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\prototyping\\motortest-proto\\motortest-proto.ino"
int in1 = 42;
int in2 = 44;
int enA = 40;

int in3 = 46;
int in4 = 48;
int enB = 50;

void setup(){

  pinMode(enA, 0x1);
  pinMode(in1, 0x1);
  pinMode(in2, 0x1);
  pinMode(enB, 0x1);
  pinMode(in3, 0x1);
  pinMode(in4, 0x1);

}

void loop(){

  digitalWrite(in1, 0x1); // move forward for 1.5s
  digitalWrite(in2, 0x0);
  digitalWrite(in3, 0x0);
  digitalWrite(in4, 0x1);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);

  digitalWrite(in1, 0x0); // stop for 0.5s
  digitalWrite(in2, 0x0);
  digitalWrite(in3, 0x0);
  digitalWrite(in4, 0x0);
  digitalWrite(enA, 0);
  digitalWrite(enB, 0);
  delay(500);

  digitalWrite(in1, 0x0); // move forward for 1.5s
  digitalWrite(in2, 0x1);
  digitalWrite(in3, 0x1);
  digitalWrite(in4, 0x0);
  digitalWrite(enA, 255);
  digitalWrite(enB, 255);
  delay(1500);

  digitalWrite(in1, 0x0); // stop for 0.5s
  digitalWrite(in2, 0x0);
  digitalWrite(in3, 0x0);
  digitalWrite(in4, 0x0);
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
# 69 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\prototyping\\motortest-proto\\motortest-proto.ino"
}
