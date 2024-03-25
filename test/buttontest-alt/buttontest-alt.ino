#include <Servo.h>

void lowerClaw();

// Motor 4 (Y axis) pins
int in7 = 29;
int in8 = 30;
int enD = 31; // Speed control, 0-255

// Button/claw controls
const int servoPower = 6;
const int multiButton = 49;
int motorPos = 0;
bool upStroke = 0;
Servo clawServo;
int pos;

const int lowerHome = 1 * 1000;
const int upperHome = 0;

void setup(){
    // Motor 4 pin modes
    pinMode(enD, OUTPUT);
    pinMode(in7, OUTPUT);
    pinMode(in8, OUTPUT);

    // Button/claw pin modes
    pinMode(servoPower, OUTPUT);
    pinMode(multiButton, INPUT);
    digitalWrite(multiButton, INPUT_PULLUP);
    digitalWrite(servoPower, HIGH);

    Serial.begin(9600);
}

void loop(){
    if(digitalRead(multiButton) == LOW){
        Serial.println("BUTTON PRESSED");
        lowerClaw();
        
    } else{
        // Serial.println("WAITING");
    }
}

void lowerClaw(){
    Serial.println("CLAW OPENING");
    clawServo.write(25);
    Serial.println("GOING DOWN");
    digitalWrite(in7, HIGH); 
    digitalWrite(in8, LOW);
    digitalWrite(enD, 255); 
    delay(3000);

    Serial.println("CLAW CLOSING");
    clawServo.write(160);
    delay(750);
    Serial.println("GOING UP");
    digitalWrite(in7, LOW); 
    digitalWrite(in8, HIGH);
    digitalWrite(enD, 255); 
    delay(3000);
}