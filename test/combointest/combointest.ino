#include <Servo.h>

void lowerClaw();

// Button/claw controls
const int servoPower = 6;
const int multiButton = 49;
int motorPos = 0;
bool upStroke = 0;
Servo clawServo;
int pos = 0;

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

// Joystick pins
int joystickBck = 23;
int joystickFwd = 22;
int joystickRight = 24;
int joystickLeft = 25;

void setup(){
    // Motor 1 pin modes
    pinMode(motor1Speed, OUTPUT);
    pinMode(motor1Out1, OUTPUT);
    pinMode(motor1Out2, OUTPUT);
    // Motor 2 pin modes
    pinMode(motor2Speed, OUTPUT);
    pinMode(motor2Out1, OUTPUT);
    pinMode(motor2Out2, OUTPUT);
    // Motor 3 pin modes
    pinMode(motor3Speed, OUTPUT);
    pinMode(motor3Out1, OUTPUT);
    pinMode(motor3Out2, OUTPUT);
    // Motor 4 pin modes
    pinMode(motor4Speed, OUTPUT);
    pinMode(motor4Out1, OUTPUT);
    pinMode(motor4Out2, OUTPUT);

    // Joystick pin modes
    pinMode(joystickBck, INPUT_PULLUP);
    pinMode(joystickFwd, INPUT_PULLUP);
    pinMode(joystickLeft, INPUT_PULLUP);
    pinMode(joystickRight, INPUT_PULLUP);

    // Button/claw pin modes
    pinMode(servoPower, OUTPUT);
    pinMode(multiButton, INPUT);
    digitalWrite(multiButton, INPUT_PULLUP);
    digitalWrite(servoPower, HIGH);

    clawServo.attach(6);
    clawServo.write(105);

    Serial.begin(9600);

}

void loop(){
if(digitalRead(joystickFwd) == LOW){
        digitalWrite(motor3Out1, HIGH); // MOTOR 1 FORWARD ON
        digitalWrite(motor3Out2, LOW); // REVERSE OFF
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, LOW); // MOTOR 2 FORWARD OFF (must be opposite)
        digitalWrite(motor4Out2, HIGH); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX
        Serial.println("DOWN");

    } else if(digitalRead(joystickBck) == LOW){
        digitalWrite(motor3Out1, LOW); // MOTOR 1 FORWARD OFF
        digitalWrite(motor3Out2, HIGH); // REVERSE ON
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, HIGH); // MOTOR 2 FORWARD ON
        digitalWrite(motor4Out2, LOW); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX
        Serial.println("UP");

    } else if(digitalRead(joystickLeft) == LOW){
        digitalWrite(motor2Out1, LOW); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, HIGH); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("LEFT");

    } else if(digitalRead(joystickRight) == LOW){
        digitalWrite(motor2Out1, HIGH); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, LOW); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("RIGHT");

    } else if(digitalRead(joystickFwd) == LOW && digitalRead(joystickLeft) == LOW){
        digitalWrite(motor3Out1, HIGH); // MOTOR 1 FORWARD ON
        digitalWrite(motor3Out2, LOW); // REVERSE OFF
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, LOW); // MOTOR 2 FORWARD OFF (must be opposite)
        digitalWrite(motor4Out2, HIGH); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX

        digitalWrite(motor2Out1, LOW); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, HIGH); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("UP LEFT");

    } else if(digitalRead(joystickFwd) == LOW && digitalRead(joystickRight) == LOW){
        digitalWrite(motor3Out1, HIGH); // MOTOR 1 FORWARD ON
        digitalWrite(motor3Out2, LOW); // REVERSE OFF
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, LOW); // MOTOR 2 FORWARD OFF (must be opposite)
        digitalWrite(motor4Out2, HIGH); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX

        digitalWrite(motor2Out1, HIGH); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, LOW); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("UP RIGHT");

    } else if(digitalRead(joystickBck) == LOW && digitalRead(joystickLeft) == LOW){
        digitalWrite(motor3Out1, LOW); // MOTOR 1 FORWARD OFF
        digitalWrite(motor3Out2, HIGH); // REVERSE ON
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, HIGH); // MOTOR 2 FORWARD ON
        digitalWrite(motor4Out2, LOW); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX

        digitalWrite(motor2Out1, LOW); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, HIGH); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("UP LEFT");

    } else if(digitalRead(joystickBck) == LOW && digitalRead(joystickRight) == LOW){
        digitalWrite(motor3Out1, LOW); // MOTOR 1 FORWARD OFF
        digitalWrite(motor3Out2, HIGH); // REVERSE ON
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, HIGH); // MOTOR 2 FORWARD ON
        digitalWrite(motor4Out2, LOW); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX

        digitalWrite(motor2Out1, HIGH); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, LOW); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("UP RIGHT");

    } else {
        digitalWrite(motor2Out1, LOW); // MOTOR 1/X FORWARD OFF
        digitalWrite(motor2Out2, LOW); // REVERSE OFF
        digitalWrite(motor2Speed, 0); // SPEED MIN

        digitalWrite(motor3Out1, LOW); // MOTOR 2/Y FORWARD OFF
        digitalWrite(motor3Out2, LOW); // REVERSE OFF
        digitalWrite(motor3Speed, 0); // SPEED MIN

        digitalWrite(motor4Out1, LOW); // MOTOR 2/Y FORWARD OFF
        digitalWrite(motor4Out2, LOW); // REVERSE OFF
        digitalWrite(motor4Speed, 0); // SPEED MIN

        Serial.println("CENTER");
        delay(100);

    }

    if(digitalRead(multiButton) == LOW){
        Serial.println("BUTTON PRESSED");
        lowerClaw();
        
    } else{
        // Serial.println("WAITING");
    }
}

void lowerClaw(){
    Serial.println("CLAW OPENING");
    clawServo.write(55);
    Serial.println("GOING DOWN");
    digitalWrite(motor1Out1, HIGH); 
    digitalWrite(motor1Out2, LOW);
    digitalWrite(motor1Speed, 255); 
    delay(2200);

    Serial.println("STOPPING AT BOTTOM");
    digitalWrite(motor1Out1, LOW); 
    digitalWrite(motor1Out2, LOW);
    digitalWrite(motor1Speed, 0); 
    delay(1000);

    Serial.println("CLAW CLOSING");
    clawServo.write(105);
    delay(1000);

    Serial.println("GOING UP");
    digitalWrite(motor1Out1, LOW); 
    digitalWrite(motor1Out2, HIGH);
    digitalWrite(motor1Speed, 255); 
    delay(2500);

    Serial.println("STOPPING AT TOP");
    digitalWrite(motor1Out1, LOW); 
    digitalWrite(motor1Out2, LOW);
    digitalWrite(motor1Speed, 0); 
}