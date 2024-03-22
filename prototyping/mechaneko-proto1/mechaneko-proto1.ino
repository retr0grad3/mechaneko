
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
#include <FastLED.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <MFRC522.h>

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
const int servoPower = 6;

// Servo setup
Servo clawServo;
int val;

unsigned int timeLimit = 5; // controls play time
unsigned int timeLimit = 5; // controls play time

void setup() {
    setTime(01, 01, 00, 9, 9, 1999); // (Hour, minute, second, day, month, year)
    
    pinMode(joystickFwd, INPUT_PULLUP);
    pinMode(joystickBck, INPUT_PULLUP);
    pinMode(joystickLeft, INPUT_PULLUP);
    pinMode(joystickRight, INPUT_PULLUP);

    pinMode(multiButton, INPUT);

    // Motor 1 (Y axis; claw lift) pins
    pinMode(motor1Out1, OUTPUT);
    pinMode(motor1Out2, OUTPUT);
    pinMode(motor1Speed, OUTPUT); // Speed control, 0-255
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

    pinMode(servoPower, OUTPUT);

    // "enable internal pull ups," whatever that means; "note that all functioning logic must trigger low"
    digitalWrite(multiButton, INPUT_PULLUP);
    digitalWrite(servoPower, LOW); // default servo power to off
    digitalWrite(multiButton, INPUT_PULLUP);
    digitalWrite(servoPower, LOW); // default servo power to off

    myServo.attach(9); // what the fuck does this do
    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

}

void loop() {

    unsigned long currentMillis = millis(); // check if it's time to refresh the screen

    // Game idle ========================================================================

    if(currentMillis - previousMillis > intervalIdle){
        previousMillis = currentMillis;

        // oled code; print GAME OVER then tap card to play

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

        digitalWrite(motor1Out1, HIGH);
        digitalWrite(motor1out2, LOW);
        digitalWrite(motor1Speed, 255);

        Serial.println("CLAW GOING DOWN");
        delay(1000);`
    }
}