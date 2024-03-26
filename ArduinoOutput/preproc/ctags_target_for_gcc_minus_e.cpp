# 1 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino"
# 2 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino" 2
# 3 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino" 2
# 4 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino" 2
# 5 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino" 2
# 6 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino" 2
# 7 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino" 2

void lowerClaw();

// Button/claw controls
const int servoPower = 6;
const int multiButton = 49;
Servo clawServo;
int pos = 0;

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

// Joystick pins
int joystickBck = 23;
int joystickFwd = 22;
int joystickRight = 24;
int joystickLeft = 25;

// PWM output: OLED







Adafruit_SSD1306 display(128 /* OLED display width, in pixels*/, 64 /* OLED display height, in pixels*/,
  11 /* SDA*/, 12 /* SCK*/, 9, 8 /* RST*/, 10);

// Output: RGB strip


CRGB leds[47];

void setup(){
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(0x02 /*|< Gen. display voltage from 3.3V*/)) {
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 59 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 59 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino"
                      "SSD1306 allocation failed"
# 59 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino" 3
                      ); &__c[0];}))
# 59 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\cardless-final\\cardless-final.ino"
                      )));
        for(;;); // Don't proceed, loop forever
    }

    display.clearDisplay();
    display.setTextSize(2); // Normal 1:1 pixel scale
    display.setCursor(14,24);
    display.setTextColor(1 /*|< Draw 'on' pixels*/); // Draw 'inverse' text
    display.println("MECHANEKO");
    display.display();

    // Motor 1 pin modes
    pinMode(motor1Speed, 0x1);
    pinMode(motor1Out1, 0x1);
    pinMode(motor1Out2, 0x1);
    // Motor 2 pin modes
    pinMode(motor2Speed, 0x1);
    pinMode(motor2Out1, 0x1);
    pinMode(motor2Out2, 0x1);
    // Motor 3 pin modes
    pinMode(motor3Speed, 0x1);
    pinMode(motor3Out1, 0x1);
    pinMode(motor3Out2, 0x1);
    // Motor 4 pin modes
    pinMode(motor4Speed, 0x1);
    pinMode(motor4Out1, 0x1);
    pinMode(motor4Out2, 0x1);

    // Joystick pin modes
    pinMode(joystickBck, 0x2);
    pinMode(joystickFwd, 0x2);
    pinMode(joystickLeft, 0x2);
    pinMode(joystickRight, 0x2);

    // Button/claw pin modes
    pinMode(servoPower, 0x1);
    pinMode(multiButton, 0x0);
    digitalWrite(multiButton, 0x2);
    digitalWrite(servoPower, 0x1);

    clawServo.attach(6);
    clawServo.write(105);

    FastLED.addLeds<NEOPIXEL, 7>(leds, 47);

    fill_solid(leds, 47, CRGB::CRGB(167, 75, 208));
    FastLED.show();

    Serial.begin(9600);

}

void loop(){
if(digitalRead(joystickFwd) == 0x0){
        digitalWrite(motor3Out1, 0x1); // MOTOR 1 FORWARD ON
        digitalWrite(motor3Out2, 0x0); // REVERSE OFF
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, 0x0); // MOTOR 2 FORWARD OFF (must be opposite)
        digitalWrite(motor4Out2, 0x1); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX
        Serial.println("DOWN");

    } else if(digitalRead(joystickBck) == 0x0){
        digitalWrite(motor3Out1, 0x0); // MOTOR 1 FORWARD OFF
        digitalWrite(motor3Out2, 0x1); // REVERSE ON
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, 0x1); // MOTOR 2 FORWARD ON
        digitalWrite(motor4Out2, 0x0); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX
        Serial.println("UP");

    } else if(digitalRead(joystickLeft) == 0x0){
        digitalWrite(motor2Out1, 0x0); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, 0x1); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("LEFT");

    } else if(digitalRead(joystickRight) == 0x0){
        digitalWrite(motor2Out1, 0x1); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, 0x0); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("RIGHT");

    } else if(digitalRead(joystickFwd) == 0x0 && digitalRead(joystickLeft) == 0x0){
        digitalWrite(motor3Out1, 0x1); // MOTOR 1 FORWARD ON
        digitalWrite(motor3Out2, 0x0); // REVERSE OFF
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, 0x0); // MOTOR 2 FORWARD OFF (must be opposite)
        digitalWrite(motor4Out2, 0x1); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX

        digitalWrite(motor2Out1, 0x0); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, 0x1); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("UP LEFT");

    } else if(digitalRead(joystickFwd) == 0x0 && digitalRead(joystickRight) == 0x0){
        digitalWrite(motor3Out1, 0x1); // MOTOR 1 FORWARD ON
        digitalWrite(motor3Out2, 0x0); // REVERSE OFF
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, 0x0); // MOTOR 2 FORWARD OFF (must be opposite)
        digitalWrite(motor4Out2, 0x1); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX

        digitalWrite(motor2Out1, 0x1); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, 0x0); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("UP RIGHT");

    } else if(digitalRead(joystickBck) == 0x0 && digitalRead(joystickLeft) == 0x0){
        digitalWrite(motor3Out1, 0x0); // MOTOR 1 FORWARD OFF
        digitalWrite(motor3Out2, 0x1); // REVERSE ON
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, 0x1); // MOTOR 2 FORWARD ON
        digitalWrite(motor4Out2, 0x0); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX

        digitalWrite(motor2Out1, 0x0); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, 0x1); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("UP LEFT");

    } else if(digitalRead(joystickBck) == 0x0 && digitalRead(joystickRight) == 0x0){
        digitalWrite(motor3Out1, 0x0); // MOTOR 1 FORWARD OFF
        digitalWrite(motor3Out2, 0x1); // REVERSE ON
        digitalWrite(motor3Speed, 255); // SPEED MAX
        digitalWrite(motor4Out1, 0x1); // MOTOR 2 FORWARD ON
        digitalWrite(motor4Out2, 0x0); // REVERSE OFF
        digitalWrite(motor4Speed, 255); // SPEED MAX

        digitalWrite(motor2Out1, 0x1); // MOTOR 1 FORWARD OFF
        digitalWrite(motor2Out2, 0x0); // REVERSE ON
        digitalWrite(motor2Speed, 255); // SPEED MAX
        Serial.println("UP RIGHT");

    } else {
        digitalWrite(motor2Out1, 0x0); // MOTOR 1/X FORWARD OFF
        digitalWrite(motor2Out2, 0x0); // REVERSE OFF
        digitalWrite(motor2Speed, 0); // SPEED MIN

        digitalWrite(motor3Out1, 0x0); // MOTOR 2/Y FORWARD OFF
        digitalWrite(motor3Out2, 0x0); // REVERSE OFF
        digitalWrite(motor3Speed, 0); // SPEED MIN

        digitalWrite(motor4Out1, 0x0); // MOTOR 2/Y FORWARD OFF
        digitalWrite(motor4Out2, 0x0); // REVERSE OFF
        digitalWrite(motor4Speed, 0); // SPEED MIN

        Serial.println("CENTER");
        delay(100);

    }

    if(digitalRead(multiButton) == 0x0){
        Serial.println("BUTTON PRESSED");
        lowerClaw();

    } else{
        // Serial.println("WAITING");
    }
}

void lowerClaw(){
    Serial.println("CLAW OPENING");
    clawServo.write(55);
    Serial.println("GOING DOWN");
    digitalWrite(motor1Out1, 0x1);
    digitalWrite(motor1Out2, 0x0);
    digitalWrite(motor1Speed, 255);
    delay(2200);

    Serial.println("STOPPING AT BOTTOM");
    digitalWrite(motor1Out1, 0x0);
    digitalWrite(motor1Out2, 0x0);
    digitalWrite(motor1Speed, 0);
    delay(1000);

    Serial.println("CLAW CLOSING");
    clawServo.write(105);
    delay(1000);

    Serial.println("GOING UP");
    digitalWrite(motor1Out1, 0x0);
    digitalWrite(motor1Out2, 0x1);
    digitalWrite(motor1Speed, 255);
    delay(2500);

    Serial.println("STOPPING AT TOP");
    digitalWrite(motor1Out1, 0x0);
    digitalWrite(motor1Out2, 0x0);
    digitalWrite(motor1Speed, 0);
}
