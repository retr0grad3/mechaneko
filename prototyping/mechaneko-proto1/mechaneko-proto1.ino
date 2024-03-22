
/*

Claw machine designed by MECHANEKO.
6-axis movement, no diagonal movement of the gantry (which uses "yellow gearbox" motors).
Uses RFID cards in lieu of coins. 

(c) 2024 Kevin Takamura, MECHANEKO
mechaneko.carrd.co

*/


// Include header files
#include <Time.h>
#include <Servo.h>

/* 
 * Set pinout values
 * -----------------------------------------------------------------------------------------
 * Joystick: 22-25; digital
 * Button: 26; digital
 * OLED: 8-12; PWM
 * RGB strip: 7
 * Motors: 29-40
 * RFID: 5, 50-53
 * Servo power: 6
 * -----------------------------------------------------------------------------------------
 */ 

// Digital input: joystick
const int joystickFwd = 22;
const int joystickBck = 23;
const int joystickRight = 24;
const int joystickLeft = 25;

// Digial input: buttons
const int multiButton = 26;
int multiButton = HIGH;

// PWM output: OLED
#define OLED_MOSI  11
#define OLED_CLK   12
#define OLED_DC    9
#define OLED_CS    10
#define OLED_RESET 8

// Output: RGB strip
#define DATA_PIN 6
#define NUM_LEDS 10 // set to real value

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

// Digital input/output: RFID reader
#define RST_PIN 5
#define SS_PIN  53
// MOSI ------> 51
// MISO ------> 50
// SCK  ------> 52

// Output: power
const int servoPower = 6;

// Servo setup
Servo clawServo;
int val;

unsigned int timeLimit = 5; // controls play time

void setup() {
    setTime(01, 01, 00, 9, 9, 1999); // (Hour, minute, second, day, month, year)
    
    // Configure pinouts
    pinMode(joystickFwd, INPUT_PULLUP);
    pinMode(joystickBck, INPUT_PULLUP);
    pinMode(joystickLeft, INPUT_PULLUP);
    pinMode(joystickRight, INPUT_PULLUP);

    pinMode(multiButton, INPUT);

    pinMode(servoPower, OUTPUT);

    // "enable internal pull ups," whatever that means; "note that all functioning logic must trigger low"
    digitalWrite(multiButton, INPUT_PULLUP);
    digitalWrite(servoPower, LOW); // default servo power to off

    myServo.attach(9); // what the fuck does this do

}

void loop() {

    unsigned long currentMillis = millis(); // check if it's time to refresh the screen

    // Game idle ========================================================================

    if(currentMillis - previousMillis > intervalIdle){
        previousMillis = currentMillis;

        if(y == 0){
            y = y + 1; // "add to the y cursor position"?????
            x = x + 1;
            // oled code; print GAME OVER then insert coins to play
        } else {
            // same thing?? wtf
        }
    }
    
    if(second() == timeLimit){
            // time expired; release claw and turn off servo
        }

    // Credit accepted ==================================================================

    // *insert RFID card logic here; use do/while
    // *do [if blah blah blah wipe screen and print "credit: 1" "push start to begin" and turn on led???
    // wait for start]

    /*
    buttonStateStart = digitalRead(buttonStart);
    } while (buttonStateStart == HIGH);
    runGame();
    */

}

void runGame(){
    // *turn off blinking start button
    setTime(01, 01, 00, 9, 9, 1999); // reset time to validate gameplay
    // *wipe screen
    digitalWrite(servoPower, HIGH); // enable the servo

    // Start gameplay
    while(second() < timeLimit && year() == 1999){
        // *print time limit on screen

        // *uhh figure out how the motors work
        // *yeah this is all just stepper motor stuff i don't know how it works

        // *Servo control
        // ... this literally maps a potentiometer to the fucking servo value this shit is pissing me off
    }
}