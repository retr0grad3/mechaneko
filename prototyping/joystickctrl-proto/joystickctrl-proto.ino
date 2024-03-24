/* 

Makes a group of motors move given a joystick's input

*/

// Motor 4 (Y axis) pins
int in7 = 29;
int in8 = 30;
int enD = 31; // Speed control, 0-255
// Motor 1 (X axis) pins
int in1 = 32;
int in2 = 33;
int enA = 34; // Speed control, 0-255
// Motor 2 (Z axis) pins
int in3 = 35;
int in4 = 36;
int enB = 37; // Speed control, 0-255
// Motor 3 (Z axis) pins
int in5 = 38;
int in6 = 39;
int enC = 40; // Speed control, 0-255

// Joystick pins
int dirDown = 23;
int dirUp = 22;
int dirRight = 24;
int dirLeft = 25;

/*
// Button/claw controls
const int servoPower = 6;
const int multiButton = 49;
int multiButton = HIGH;
bool upStroke = 0;
unsigned int motorPos = 0;
Servo clawServo;
int pos;
*/

void setup(){
    
    // Motor 1 pin modes
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    // Motor 2 pin modes
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);
    // Motor 3 pin modes
    pinMode(enC, OUTPUT);
    pinMode(in5, OUTPUT);
    pinMode(in6, OUTPUT);
    // Motor 4 pin modes
    pinMode(enD, OUTPUT);
    pinMode(in7, OUTPUT);
    pinMode(in8, OUTPUT);

    // Joystick pin modes
    pinMode(dirDown, INPUT_PULLUP);
    pinMode(dirUp, INPUT_PULLUP);
    pinMode(dirLeft, INPUT_PULLUP);
    pinMode(dirRight, INPUT_PULLUP);

    /*
    // Button/claw pin modes
    pinMode(servoPower, OUTPUT);
    pinMode(multiButton, INPUT);
    digitalWrite(multiButton, INPUT_PULLUP);
    digitalWrite(servoPower, HIGH);

    clawServo.attach(6);
    */

    // Set up serial output
    Serial.begin(9600);

}

void loop(){
  
    // Motor 1 (in1, in2, enA) = X axis
    // Motor 2 (in3, in4, enB) = Y axis

    if(digitalRead(dirUp) == LOW){
        digitalWrite(in1, HIGH); // MOTOR 1 FORWARD ON
        digitalWrite(in2, LOW); // REVERSE OFF
        digitalWrite(enA, 255); // SPEED MAX
        digitalWrite(in3, LOW); // MOTOR 2 FORWARD OFF (must be opposite)
        digitalWrite(in4, HIGH); // REVERSE OFF
        digitalWrite(enB, 255); // SPEED MAX
        Serial.println("DOWN");

    } else if(digitalRead(dirDown) == LOW){
        digitalWrite(in1, LOW); // MOTOR 1 FORWARD OFF
        digitalWrite(in2, HIGH); // REVERSE ON
        digitalWrite(enA, 255); // SPEED MAX
        digitalWrite(in3, HIGH); // MOTOR 2 FORWARD ON
        digitalWrite(in4, LOW); // REVERSE OFF
        digitalWrite(enB, 255); // SPEED MAX
        Serial.println("UP");

    } else if(digitalRead(dirLeft) == LOW){
        digitalWrite(in5, HIGH); // MOTOR 2 FORWARD ON
        digitalWrite(in6, LOW); // REVERSE OFF
        digitalWrite(enC, 255); // SPEED MAX
        Serial.println("LEFT");

    } else if(digitalRead(dirRight) == LOW){
        digitalWrite(in5, LOW); // MOTOR 2 FORWARD ON
        digitalWrite(in6, HIGH); // REVERSE OFF
        digitalWrite(enC, 255); // SPEED MAX
        Serial.println("RIGHT");

    } else {
        digitalWrite(in1, LOW); // MOTOR 1/X FORWARD OFF
        digitalWrite(in2, LOW); // REVERSE OFF
        digitalWrite(enA, 0); // SPEED MIN

        digitalWrite(in3, LOW); // MOTOR 2/Y FORWARD OFF
        digitalWrite(in4, LOW); // REVERSE OFF
        digitalWrite(enB, 0); // SPEED MIN

        digitalWrite(in5, LOW); // MOTOR 2/Y FORWARD OFF
        digitalWrite(in6, LOW); // REVERSE OFF
        digitalWrite(enC, 0); // SPEED MIN

        Serial.println("CENTER");
        delay(100);
        
    }

    /*
    if(digitalRead(multiButton) == LOW){
        lowerClaw();
    }
    */

}

/*
void lowerClaw(){
    while(true){
        if(upStroke == 0){
            if(motorPos < 1000){
                // lower
                motorPos += 1;

                digitalWrite(in7, HIGH); 
                digitalWrite(in8, LOW);
                digitalWrite(enD, 255); 

            } else if(motorPos == 1000){
                // stop and wait
                digitalWrite(in7, LOW); 
                digitalWrite(in8, LOW);
                digitalWrite(enD, 0);
                delay(500); 
                upStroke = 1;

            } else if(motorPos > 1000){
                // raise
                motorPos -+ 1;

                digitalWrite(in7, LOW); 
                digitalWrite(in8, HIGH);
                digitalWrite(enD, 255); 

            }
        } else if(upStroke == 1){
            if(motorPos > 0){
                // raise
                motorPos -+ 1;

                digitalWrite(in7, LOW); 
                digitalWrite(in8, HIGH);
                digitalWrite(enD, 255); 

            } else if(motorPos == 0){
                digitalWrite(in7, LOW); 
                digitalWrite(in8, LOW);
                digitalWrite(enD, 0);
                upStroke = 0;
                break;

            } else if(motorPos < 0){
                motorPos += 1;

                digitalWrite(in7, HIGH); 
                digitalWrite(in8, LOW);
                digitalWrite(enD, 255); 
            }
        }
    }
}
*/