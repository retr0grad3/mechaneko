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
    while(true){
        if(upStroke == 0){
            if(motorPos < 1000){
                // lower
                motorPos += 1;

                digitalWrite(in7, HIGH); 
                digitalWrite(in8, LOW);
                digitalWrite(enD, 255); 

                Serial.println("DOWN STROKE, GOING DOWN");

            } else if(motorPos == 1000){
                // stop and wait
                digitalWrite(in7, LOW); 
                digitalWrite(in8, LOW);
                digitalWrite(enD, 0);
                delay(500); 
                upStroke = 1;

                Serial.println("ARRIVED AT LOWER HOME");

            } else if(motorPos > 1000){
                // raise
                motorPos -+ 1;

                digitalWrite(in7, LOW); 
                digitalWrite(in8, HIGH);
                digitalWrite(enD, 255); 

                Serial.println("DOWN STROKE, GOING DOWN");

            }
        } else if(upStroke == 1){
            if(motorPos > 0){
                // raise
                motorPos -+ 1;

                digitalWrite(in7, LOW); 
                digitalWrite(in8, HIGH);
                digitalWrite(enD, 255); 

                Serial.println("UP STROKE, GOING UP");

            } else if(motorPos == 0){
                digitalWrite(in7, LOW); 
                digitalWrite(in8, LOW);
                digitalWrite(enD, 0);
                upStroke = 0;
                Serial.println("ARRIVED AT UPPER HOME");
                break;

            } else if(motorPos < 0){
                motorPos += 1;

                digitalWrite(in7, HIGH); 
                digitalWrite(in8, LOW);
                digitalWrite(enD, 255); 

                Serial.println("UP STROKE, GOING DOWN");
            }
        }
    }
}