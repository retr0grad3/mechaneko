
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

// Set pinout values
// the reference code uses all buttons instead of joystick control
    // ** TO-DO: How to use joystick?!?!?!
// Input: joystick
const int joystickFwd = 1;
const int joystickBck = 2;
const int joystickRight = 3;
const int joystickLeft = 4;
// Input: buttons
const int buttonDive = 5;
const int buttonStart = 6;
int buttonStateDive = HIGH;
int buttonStateStart = HIGH;

// Output: power
const int servoPower = 8;
// Add LEDs?
    // ** TO-DO: How to use OLED?!?!?!?!?!?!
    // ** TO-DO: How to use motors?!?!?!?!?!?!??!!?!?!??!?!?!?!?!?!? Very IMPORTANT!!!!!!!!

// Set time intervals
long intervalStart = 500; // rate of blink for "insert coin" or "game over"
long intervalIdle = 1000; // rate of blink for "push to start to begin"
long previousMillis = 0;

int y = 0; // wtf is this
int x = 0;

// Servo setup
Servo clawServo;
int potpin = 0; // POTENTIOMETER........................................
int val;

unsigned int timelimit = 5; // controls play time

void setup() {
    setTime(01, 01, 00, 9, 9, 1999); // (Hour, minute, second, day, month, year)
    
    // Configure pinouts
    // pinMode() for all 4 axes of joystick
    pinMode(buttonDive, INPUT);
    pinMode(buttonStart, INPUT);

    pinMode(servoPower, OUTPUT);

    // "enable internal pull ups," whatever that means; "note that all functioning logic must trigger low"
    digitalWrite(buttonDive, INPUT_PULLUP);
    digitalWrite(buttonStart, INPUT_PULLUP);
    digitalWrite(servopower, LOW); // default servo power to off

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

    // insert RFID card logic here; use do/while
    // do [if blah blah blah wipe screen and print "credit: 1" "push start to begin" and turn on led???
    // wait for start]

    /*
    buttonStateStart = digitalRead(buttonStart);
    } while (buttonStateStart == HIGH);
    runGame();
    */

}

void runGame(){
    // turn off blinking start button
    setTime(01, 01, 00, 9, 9, 1999); // reset time to validate gameplay
    // wipe screen
    digitalWrite(servoPower, HIGH); // enable the servo

    // Start gameplay
    while(second() < timelimit && year() == 1999){
        // print time limit on screen

        // uhh figure out how the motors work
        // yeah this is all just stepper motor stuff i don't know how it works

        // Servo control
        // ... this literally maps a potentiometer to the fucking servo value this shit is pissing me off
    }
}