void returnToHome();

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

// PWM input: Limit switches
const int xLimit = 3;
const int zLimit = 4;

void setup(){
    // Motor 2 (X axis; claw gantry) pins
    pinMode(motor2Out1, OUTPUT);
    pinMode(motor2Out2, OUTPUT);
    pinMode(motor2Speed, OUTPUT); // Speed control, 0-255
    // Motor 3 (Z axis; lower gantry) pins
    pinMode(motor3Out1, OUTPUT);
    pinMode(motor3Out2, OUTPUT);
    pinMode(motor3Speed, OUTPUT); // Speed control, 0-255
    // Motor 4 (Z axis; lower gantry) pins
    pinMode(motor4Out1, OUTPUT);
    pinMode(motor4Out2, OUTPUT);
    pinMode(motor4Speed, OUTPUT); // Speed control, 0-255

    pinMode(xLimit, INPUT);
    pinMode(zLimit, INPUT);
}

void loop(){
    returnToHome();
}

void returnToHome(){
    while(digitalRead(xLimit) == HIGH || digitalRead(zLimit) == HIGH){
        if(digitalRead(xLimit) == HIGH){
            digitalWrite(motor3Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor3Out2, HIGH); // REVERSE ON
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, HIGH); // MOTOR 2 FORWARD ON
            digitalWrite(motor4Out2, LOW); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX
            Serial.println("RETURNING TO Z HOME");
        }
        if(digitalRead(zLimit) == HIGH){
            digitalWrite(motor2Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, HIGH); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("RETURNING TO X HOME");
        }
    }

    Serial.println("WELCOME HOME");
}