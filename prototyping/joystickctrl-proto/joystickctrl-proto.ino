/* 

Makes a group of motors move given a joystick's input

*/


// Motor 1 (X axis) pins
int in1 = 42;
int in2 = 44;
int enA = 40; // Speed control, 0-255
// Motor 2 (Y axis) pins
int in3 = 46;
int in4 = 48;
int enB = 50; // Speed control, 0-255

// Joystick pins
int dirDown = 51;
int dirUp = 53;
int dirRight = 49;
int dirLeft = 47;

void setup(){
    
    // Motor 1 pin modes
    pinMode(enA, OUTPUT);
    pinMode(in1, OUTPUT);
    pinMode(in2, OUTPUT);
    // Motor 2 pin modes
    pinMode(enB, OUTPUT);
    pinMode(in3, OUTPUT);
    pinMode(in4, OUTPUT);

    // Joystick pin modes
    pinMode(dirDown, INPUT_PULLUP);
    pinMode(dirUp, INPUT_PULLUP);
    pinMode(dirLeft, INPUT_PULLUP);
    pinMode(dirRight, INPUT_PULLUP);

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
        Serial.println("LEFT");

    } else if(digitalRead(dirRight) == LOW){
        Serial.println("RIGHT");

    } else {
        digitalWrite(in1, LOW); // MOTOR 1/X FORWARD OFF
        digitalWrite(in2, LOW); // REVERSE OFF
        digitalWrite(enA, 0); // SPEED MIN

        digitalWrite(in3, LOW); // MOTOR 2/Y FORWARD OFF
        digitalWrite(in4, LOW); // REVERSE OFF
        digitalWrite(enB, 0); // SPEED MIN

        Serial.println("CENTER");
        delay(100);
        
    }

    /*

    if(digitalRead(dirUp) == LOW){
        digitalWrite(in1, HIGH); // MOTOR 1/X FORWARD ON
        digitalWrite(in2, LOW); // REVERSE OFF
        digitalWrite(enA, 255); // SPEED MAX
        Serial.println("DOWN");

    } else if(digitalRead(dirDown) == LOW){
        digitalWrite(in1, LOW); // MOTOR 1/X FORWARD OFF
        digitalWrite(in2, HIGH); // REVERSE ON
        digitalWrite(enA, 255); // SPEED MAX
        Serial.println("UP");

    } else if(digitalRead(dirLeft) == LOW){
        digitalWrite(in3, HIGH); // MOTOR 2/Y FORWARD ON
        digitalWrite(in4, LOW); // REVERSE OFF
        digitalWrite(enB, 255); // SPEED MAX
        Serial.println("LEFT");

    } else if(digitalRead(dirRight) == LOW){
        digitalWrite(in3, LOW); // MOTOR 2/Y FORWARD OFF
        digitalWrite(in4, HIGH); // REVERSE ON
        digitalWrite(enB, 255); // SPEED MAX
        Serial.println("RIGHT");

    } else {
        digitalWrite(in1, LOW); // MOTOR 1/X FORWARD OFF
        digitalWrite(in2, LOW); // REVERSE OFF
        digitalWrite(enA, 0); // SPEED MIN

        digitalWrite(in3, LOW); // MOTOR 2/Y FORWARD OFF
        digitalWrite(in4, LOW); // REVERSE OFF
        digitalWrite(enB, 0); // SPEED MIN

        Serial.println("CENTER");
        delay(100);
        
    }

    */

}