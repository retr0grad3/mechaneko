# 1 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\prototyping\\joystickctrl-proto\\joystickctrl-proto.ino"
/* 



Makes a group of motors move given a joystick's input



*/
# 8 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\prototyping\\joystickctrl-proto\\joystickctrl-proto.ino"
// Motor 1 (X axis) pins
int in1 = 42;
int in2 = 44;
int enA = 40; // Speed control, 0-255
// Motor 2 (Y axis) pins
int in3 = 46;
int in4 = 48;
int enB = 50; // Speed control, 0-255
// Motor 3 (Y axis) pins
int in5 = 29;
int in6 = 31;
int enC = 27; // Speed control, 0-255

// Joystick pins
int dirDown = 51;
int dirUp = 53;
int dirRight = 49;
int dirLeft = 47;

void setup(){

    // Motor 1 pin modes
    pinMode(enA, 0x1);
    pinMode(in1, 0x1);
    pinMode(in2, 0x1);
    // Motor 2 pin modes
    pinMode(enB, 0x1);
    pinMode(in3, 0x1);
    pinMode(in4, 0x1);

    // Joystick pin modes
    pinMode(dirDown, 0x2);
    pinMode(dirUp, 0x2);
    pinMode(dirLeft, 0x2);
    pinMode(dirRight, 0x2);

    // Set up serial output
    Serial.begin(9600);

}

void loop(){

    // Motor 1 (in1, in2, enA) = X axis
    // Motor 2 (in3, in4, enB) = Y axis

    if(digitalRead(dirUp) == 0x0){
        digitalWrite(in1, 0x1); // MOTOR 1 FORWARD ON
        digitalWrite(in2, 0x0); // REVERSE OFF
        digitalWrite(enA, 255); // SPEED MAX
        digitalWrite(in3, 0x0); // MOTOR 2 FORWARD OFF (must be opposite)
        digitalWrite(in4, 0x1); // REVERSE OFF
        digitalWrite(enB, 255); // SPEED MAX
        Serial.println("DOWN");

    } else if(digitalRead(dirDown) == 0x0){
        digitalWrite(in1, 0x0); // MOTOR 1 FORWARD OFF
        digitalWrite(in2, 0x1); // REVERSE ON
        digitalWrite(enA, 255); // SPEED MAX
        digitalWrite(in3, 0x1); // MOTOR 2 FORWARD ON
        digitalWrite(in4, 0x0); // REVERSE OFF
        digitalWrite(enB, 255); // SPEED MAX
        Serial.println("UP");

    } else if(digitalRead(dirLeft) == 0x0){
        digitalWrite(in5, 0x1); // MOTOR 2 FORWARD ON
        digitalWrite(in6, 0x0); // REVERSE OFF
        digitalWrite(enC, 255); // SPEED MAX
        Serial.println("LEFT");

    } else if(digitalRead(dirRight) == 0x0){
        digitalWrite(in5, 0x0); // MOTOR 2 FORWARD ON
        digitalWrite(in6, 0x1); // REVERSE OFF
        digitalWrite(enC, 255); // SPEED MAX
        Serial.println("RIGHT");

    } else {
        digitalWrite(in1, 0x0); // MOTOR 1/X FORWARD OFF
        digitalWrite(in2, 0x0); // REVERSE OFF
        digitalWrite(enA, 0); // SPEED MIN

        digitalWrite(in3, 0x0); // MOTOR 2/Y FORWARD OFF
        digitalWrite(in4, 0x0); // REVERSE OFF
        digitalWrite(enB, 0); // SPEED MIN

        digitalWrite(in5, 0x0); // MOTOR 2/Y FORWARD OFF
        digitalWrite(in6, 0x0); // REVERSE OFF
        digitalWrite(enC, 0); // SPEED MIN

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
# 144 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\prototyping\\joystickctrl-proto\\joystickctrl-proto.ino"
}
