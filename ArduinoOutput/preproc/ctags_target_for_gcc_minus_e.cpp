# 1 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\test\\motortest\\motortest.ino"
// Digital output: Motors
// Motor 1 (Y axis; claw lift) pins
int motor1Out1 = 29;
int motor1Out2 = 30;
int motor1Speed = 31; // Speed control, 0-255
// Motor 2 (X axis; claw gantry) pins
int motor2Out1 = 32;
int motor2Out2 = 33;
int motor2Speed = 34; // Speed control, 0-255
// Motor 3 (Z axis; lower gantry) pins
int motor3Out1 = 35;
int motor3Out2 = 36;
int motor3Speed = 37; // Speed control, 0-255
// Motor 4 (Z axis; lower gantry) pins
int motor4Out1 = 38;
int motor4Out2 = 39;
int motor4Speed = 40; // Speed control, 0-255

void setup(){

  // Motor 1 (Y axis; claw lift) pins
  pinMode(motor1Out1, 0x1);
  pinMode(motor1Out2, 0x1);
  pinMode(motor1Speed, 0x1); // Speed control, 0-255
  // Motor 2 (X axis; claw gantry) pins
  pinMode(motor2Out1, 0x1);
  pinMode(motor2Out2, 0x1);
  pinMode(motor2Speed, 0x1); // Speed control, 0-255
  // Motor 3 (Z axis; lower gantry) pins
  pinMode(motor3Out1, 0x1);
  pinMode(motor3Out2, 0x1);
  pinMode(motor3Speed, 0x1); // Speed control, 0-255
  // Motor 4 (Z axis; lower gantry) pins
  pinMode(motor4Out1, 0x1);
  pinMode(motor4Out2, 0x1);
  pinMode(motor4Speed, 0x1); // Speed control, 0-255

}

void loop(){

  digitalWrite(motor1Out1, 0x1); // move forward for 1.5s
  digitalWrite(motor1Out2, 0x0);
  digitalWrite(motor2Out1, 0x0);
  digitalWrite(motor2Out2, 0x1);
  digitalWrite(motor1Speed, 255);
  digitalWrite(motor2Speed, 255);

  digitalWrite(motor3Out1, 0x1);
  digitalWrite(motor3Out2, 0x0);
  digitalWrite(motor4Out1, 0x1);
  digitalWrite(motor4Out2, 0x0);
  digitalWrite(motor3Speed, 255);
  digitalWrite(motor4Speed, 255);
  delay(1500);

  digitalWrite(motor1Out1, 0x0); // stop for 0.5s
  digitalWrite(motor1Out2, 0x0);
  digitalWrite(motor2Out1, 0x0);
  digitalWrite(motor2Out2, 0x0);
  digitalWrite(motor1Speed, 0);
  digitalWrite(motor2Speed, 0);

  digitalWrite(motor3Out1, 0x0);
  digitalWrite(motor3Out2, 0x0);
  digitalWrite(motor4Out1, 0x0);
  digitalWrite(motor4Out2, 0x0);
  digitalWrite(motor3Speed, 0);
  digitalWrite(motor4Speed, 0);
  delay(500);

  digitalWrite(motor1Out1, 0x0); // move reverse for 1.5s
  digitalWrite(motor1Out2, 0x1);
  digitalWrite(motor2Out1, 0x1);
  digitalWrite(motor2Out2, 0x0);
  digitalWrite(motor1Speed, 255);
  digitalWrite(motor2Speed, 255);

  digitalWrite(motor3Out1, 0x0);
  digitalWrite(motor3Out2, 0x1);
  digitalWrite(motor4Out1, 0x0);
  digitalWrite(motor4Out2, 0x1);
  digitalWrite(motor3Speed, 255);
  digitalWrite(motor4Speed, 255);
  delay(1500);

  digitalWrite(motor1Out1, 0x0); // stop for 0.5s
  digitalWrite(motor1Out2, 0x0);
  digitalWrite(motor2Out1, 0x0);
  digitalWrite(motor2Out2, 0x0);
  digitalWrite(motor1Speed, 0);
  digitalWrite(motor2Speed, 0);

  digitalWrite(motor3Out1, 0x0);
  digitalWrite(motor3Out2, 0x0);
  digitalWrite(motor4Out1, 0x0);
  digitalWrite(motor4Out2, 0x0);
  digitalWrite(motor3Speed, 0);
  digitalWrite(motor4Speed, 0);
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
# 117 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\test\\motortest\\motortest.ino"
}
