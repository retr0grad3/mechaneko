#include <Servo.h>
#include <FastLED.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <MFRC522.h>

/* 
 * Set pinout values
 * -----------------------------------------------------------------------------------------
 * Joystick: 22-25; digital
 * Button: 49; digital
 * OLED: 8-12; PWM
 * RGB strip: 7; PWM
 * Motors: 29-40; digital
 * RFID: 5, 50-53; PWM, digital
 * Servo power: 6, PWM
 * Limit switches: 3-4
 * -----------------------------------------------------------------------------------------
 */ 

// Digital input: joystick
const int joystickFwd = 22;
const int joystickBck = 23;
const int joystickRight = 24;
const int joystickLeft = 25;

// Digial input: buttons
const int multiButton = 49;

// PWM output: OLED
#define OLED_MOSI  11 // SDA
#define OLED_CLK   12 // SCK
#define OLED_DC    9
#define OLED_CS    10
#define OLED_RESET 8  // RST
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

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
#define SS_PIN  53 // SDA
// MOSI ------> 51
// MISO ------> 50
// SCK  ------> 52

// PWM input: Limit switches
const int xLimit = 3;
const int zLimit = 4;

// Output: power
const int servoPower = 6;

// Servo setup
Servo clawServo;
int pos;

void setup() {
    
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
    pinMode(xLimit, INPUT);
    pinMode(zLimit, INPUT);

    // "enable internal pull ups," whatever that means; "note that all functioning logic must trigger low"
    digitalWrite(multiButton, INPUT_PULLUP);
    digitalWrite(servoPower, LOW); // default servo power to off

    clawServo.attach(6); // attaches pin 6 to claw servo object

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

}

void loop(){

    

    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setCursor(14,24);    
    display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
    display.println("PHASE ONE");
    display.display();


    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setCursor(14,24);    
    display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
    display.println("PHASE TWO");
    display.display();
}