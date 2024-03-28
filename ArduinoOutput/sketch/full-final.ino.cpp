#include <Arduino.h>
#line 1 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"

/*

Claw machine designed by MECHANEKO.
6-axis movement, no diagonal movement of the gantry (which uses "yellow gearbox" motors).
Uses RFID cards in lieu of coins (feature unavailable). 

(c) 2024 Kevin Takamura, MECHANEKO
mechaneko.carrd.co

*/

#include <TimeLib.h>
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
 * Servo: 6, PWM
 * Limit switches: 3-4
 * -----------------------------------------------------------------------------------------
 */ 

// Digital input: joystick
const int joystickFwd = 22;
const int joystickBck = 23;
const int joystickRight = 24;
const int joystickLeft = 25;

// Button/claw controls
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
#define DATA_PIN 7
#define NUM_LEDS 47
CRGB leds[NUM_LEDS];

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

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;
int block = 13;
byte normNewCardValue[16] = {"1U1TN"}; // 1 use 1 try
byte normUseTwo[16] = {"2UVN"}; // 2 use; void
byte specNewCardValue[16] = {"1U3TS"}; // 1 use 3 try
byte specUseTwo[16] = {"2U2TS"};
byte specUseThree[16] = {"3U1TS"};
byte specUseFour[16] = {"4UVS"}; // 4 use; void
byte superCard[16] = {"1U3TK"};
byte clearCardValue[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
byte readCardValue[18];

// Output: servo
const int servoPower = 6; // closed = 105; open = 55
Servo clawServo;
int pos = 0;

// PWM input: Limit switches
const int xLimit = 3;
const int zLimit = 4;

unsigned int timeLimit = 30; // controls play time
bool continueGame = 0;
long intervalStart = 500;   // rate of blink for 'insert coin' / 'game over'
long intervalIdle = 2000;    // rate of blink for 'push start to begin'
long previousMillis = 0;

#line 114 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
void setup();
#line 180 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
void loop();
#line 249 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
void runGame();
#line 373 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
void lowerClaw();
#line 405 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
void dump_byte_array(byte *buffer, byte bufferSize);
#line 412 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
int writeBlock(int blockNumber, byte arrayAddress[]);
#line 446 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
int readBlock(int blockNumber, byte arrayAddress[]);
#line 471 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
int checkIfEmpty(byte cardDat[]);
#line 479 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
int checkIfValid(byte cardDat[]);
#line 498 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
void deductCredit(byte cardDat[]);
#line 523 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
int cardCheck();
#line 114 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
void setup(){
    Serial.begin(9600);
    setTime(01, 01, 00, 9, 9, 1999); // (Hour, minute, second, day, month, year)

    display.clearDisplay();
    display.setTextSize(2);             // Normal 1:1 pixel scale
    display.setCursor(12,22);    
    display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
    display.println("MECHANEKO");
    display.display();

    // Joystick pin modes
    pinMode(joystickFwd, INPUT_PULLUP);
    pinMode(joystickBck, INPUT_PULLUP);
    pinMode(joystickLeft, INPUT_PULLUP);
    pinMode(joystickRight, INPUT_PULLUP);

    // Motor 1 pin modes
    pinMode(motor1Speed, OUTPUT);
    pinMode(motor1Out1, OUTPUT);
    pinMode(motor1Out2, OUTPUT);
    // Motor 2 pin modes
    pinMode(motor2Speed, OUTPUT);
    pinMode(motor2Out1, OUTPUT);
    pinMode(motor2Out2, OUTPUT);
    // Motor 3 pin modes
    pinMode(motor3Speed, OUTPUT);
    pinMode(motor3Out1, OUTPUT);
    pinMode(motor3Out2, OUTPUT);
    // Motor 4 pin modes
    pinMode(motor4Speed, OUTPUT);
    pinMode(motor4Out1, OUTPUT);
    pinMode(motor4Out2, OUTPUT);

    // Button/claw pin modes
    pinMode(servoPower, OUTPUT);
    pinMode(multiButton, INPUT);
    digitalWrite(multiButton, INPUT_PULLUP);
    digitalWrite(servoPower, LOW);
    pinMode(xLimit, INPUT);
    pinMode(zLimit, INPUT);

    clawServo.attach(6);
    clawServo.write(105);

    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    Serial.println();
    Serial.println(F("Waiting for a card..."));

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

    fill_solid(leds, NUM_LEDS, CRGB::CRGB(167, 75, 208));
    FastLED.show();
    
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

}

void loop(){

    // Idle
    // -----------------------------------------------------------------------------------------
    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(12, 22);    
    display.setTextColor(SSD1306_WHITE);
    display.println("MECHANEKO");
    display.setTextSize(1);
    display.setCursor(14, 48); 
    display.setTextColor(SSD1306_WHITE); 
    display.println("TAP TO START");
    display.display();
    cardCheck();

    // Game end 
    // -----------------------------------------------------------------------------------------
    if(second() == timeLimit || continueGame == 0){
        continueGame = 0;
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setCursor(14,24);    
        display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
        display.println("Time's Up");
        display.display();

        clawServo.write(55);
        delay(1000);
        clawServo.write(105);
        delay(1000);
        digitalWrite(servoPower, LOW);
        // returnToHome(); // NOT READY
    }

    // Ready to start
    // -----------------------------------------------------------------------------------------
    if(cardCheck() == 1){
        continueGame = 1;
        do{
            display.clearDisplay();
            display.setTextSize(2);
            display.setCursor(12, 22);    
            display.setTextColor(SSD1306_WHITE);
            display.println("MECHANEKO");
            display.setTextSize(1);
            display.setCursor(14, 48); 
            display.setTextColor(SSD1306_WHITE); 
            display.println("PUSH BUTTON");
            display.display();
        } while(digitalRead(multiButton) == HIGH);
        runGame();
    } else if(cardCheck() == 2){
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(12, 22);    
        display.setTextColor(SSD1306_WHITE);
        display.println("MECHANEKO");
        display.setTextSize(1);
        display.setCursor(14, 48); 
        display.setTextColor(SSD1306_WHITE); 
        display.println("NO TRIES LEFT");
        display.display();
        delay(7500);
    } else if(cardCheck() == 0){
        return;
    }
}

void runGame(){
    setTime(01,01,00,9,9,1999);
    digitalWrite(servoPower, HIGH);

    while(second() < timeLimit && year() == 1999){
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(SSD1306_WHITE);        // Draw white text
        display.setCursor(12, 22);             // Start at top-left corner
        display.print(F("Time: "));
        display.print(second()-timeLimit);
        display.display();

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

        } else if(digitalRead(joystickFwd) == LOW && digitalRead(joystickLeft) == LOW){
            digitalWrite(motor3Out1, HIGH); // MOTOR 1 FORWARD ON
            digitalWrite(motor3Out2, LOW); // REVERSE OFF
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, LOW); // MOTOR 2 FORWARD OFF (must be opposite)
            digitalWrite(motor4Out2, HIGH); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX

            digitalWrite(motor2Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, HIGH); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("UP LEFT");

        } else if(digitalRead(joystickFwd) == LOW && digitalRead(joystickRight) == LOW){
            digitalWrite(motor3Out1, HIGH); // MOTOR 1 FORWARD ON
            digitalWrite(motor3Out2, LOW); // REVERSE OFF
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, LOW); // MOTOR 2 FORWARD OFF (must be opposite)
            digitalWrite(motor4Out2, HIGH); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX

            digitalWrite(motor2Out1, HIGH); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, LOW); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("UP RIGHT");

        } else if(digitalRead(joystickBck) == LOW && digitalRead(joystickLeft) == LOW){
            digitalWrite(motor3Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor3Out2, HIGH); // REVERSE ON
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, HIGH); // MOTOR 2 FORWARD ON
            digitalWrite(motor4Out2, LOW); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX

            digitalWrite(motor2Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, HIGH); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("UP LEFT");

        } else if(digitalRead(joystickBck) == LOW && digitalRead(joystickRight) == LOW){
            digitalWrite(motor3Out1, LOW); // MOTOR 1 FORWARD OFF
            digitalWrite(motor3Out2, HIGH); // REVERSE ON
            digitalWrite(motor3Speed, 255); // SPEED MAX
            digitalWrite(motor4Out1, HIGH); // MOTOR 2 FORWARD ON
            digitalWrite(motor4Out2, LOW); // REVERSE OFF
            digitalWrite(motor4Speed, 255); // SPEED MAX

            digitalWrite(motor2Out1, HIGH); // MOTOR 1 FORWARD OFF
            digitalWrite(motor2Out2, LOW); // REVERSE ON
            digitalWrite(motor2Speed, 255); // SPEED MAX
            Serial.println("UP RIGHT");

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

        if(digitalRead(multiButton) == LOW){
            Serial.println("BUTTON PRESSED");
            lowerClaw();
        }

        if(second() >= timeLimit || continueGame == 0){
            break;
        }
    }
}

void lowerClaw(){
    continueGame = 0;
    Serial.println("CLAW OPENING");
    clawServo.write(55);
    Serial.println("GOING DOWN");
    digitalWrite(motor1Out1, HIGH); 
    digitalWrite(motor1Out2, LOW);
    digitalWrite(motor1Speed, 255); 
    delay(2200);

    Serial.println("STOPPING AT BOTTOM");
    digitalWrite(motor1Out1, LOW); 
    digitalWrite(motor1Out2, LOW);
    digitalWrite(motor1Speed, 0); 
    delay(1000);

    Serial.println("CLAW CLOSING");
    clawServo.write(105);
    delay(1000);

    Serial.println("GOING UP");
    digitalWrite(motor1Out1, LOW); 
    digitalWrite(motor1Out2, HIGH);
    digitalWrite(motor1Speed, 255); 
    delay(2500);

    Serial.println("STOPPING AT TOP");
    digitalWrite(motor1Out1, LOW); 
    digitalWrite(motor1Out2, LOW);
    digitalWrite(motor1Speed, 0); 
}

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}

int writeBlock(int blockNumber, byte arrayAddress[]){

  // this makes sure that we only write into data blocks. Every 4th block is a trailer block for the access/security info.
  int largestModulo4Number = blockNumber / 4 * 4;
  int trailerBlock = largestModulo4Number + 3; //determine trailer block for the sector
  if (blockNumber > 2 && (blockNumber + 1) % 4 == 0) {
    Serial.print(blockNumber);
    Serial.println("This is a trailer block:");
    return 2;
  }

  Serial.println("");
  Serial.print(blockNumber);
  Serial.println(" This is a data block:");

  // authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
    Serial.print("PCD_Authenticate() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 3; // return "3" as error message
  }

  // writing the block
  status = mfrc522.MIFARE_Write(blockNumber, arrayAddress, 16);
  // status = mfrc522.MIFARE_Write(9, value1Block, 16);
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_Write() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 4; // return "4" as error message
  }
  Serial.println("block written");
}

int readBlock(int blockNumber, byte arrayAddress[])
{
  int largestModulo4Number = blockNumber / 4 * 4;
  int trailerBlock = largestModulo4Number + 3; //determine trailer block for the sector

  //authentication of the desired block for access
  byte status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));

  if (status != MFRC522::STATUS_OK) {
    Serial.print("PCD_Authenticate() failed (read): ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 3;//return "3" as error message
  }

  //reading a block
  byte buffersize = 18;//we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size...
  status = mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
    Serial.print("MIFARE_read() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return 4;//return "4" as error message
  }
  Serial.println("block was read");
} 

int checkIfEmpty(byte cardDat[]){
    if(cardDat[1] < 1 && cardDat[2] < 1 && cardDat[3] < 1 && cardDat[4] < 1){
        return 1;
    } else{
        return 0;
    }
}

int checkIfValid(byte cardDat[]){
    if(cardDat[0] >= 49 && cardDat[0] <= 52 && cardDat[1] == 85){ // if first digit is between 1-4 & second digit is U
      Serial.println("FIRST TWO BITS VALID");
      if(cardDat[2] >= 49 && cardDat[2] <= 51){ // if third digit is between 1-3
        Serial.println("");
        Serial.write(cardDat[2]);
        Serial.print(" TRIES REMAINING");
        return 1;
      } else if(cardDat[2] == 86){
        Serial.println("CARD IS VOID");
        return 2;
      } else{
        return 0;
      }
    } else{
      return 0;
    }
}

void deductCredit(byte cardDat[]){
  if(cardDat[2] == 49 && cardDat[4] == 83){ // if card has 1 try left & is special, void on play
    Serial.println("VOIDING SPECIAL CARD");
    writeBlock(block, clearCardValue);
    writeBlock(block, specUseFour);

  } else if(cardDat[2] == 50 && cardDat[4] == 83){
    Serial.println("REMOVING 1 SPECIAL TRY; 1 REMAIN");
    writeBlock(block, clearCardValue);
    writeBlock(block, specUseThree);

  } else if(cardDat[2] == 51 && cardDat[4] == 83){
    Serial.println("REMOVING 1 SPECIAL TRY; 2 REMAIN");
    writeBlock(block, clearCardValue);
    writeBlock(block, specUseTwo);

  } else if(cardDat[2] == 49 && cardDat[4] == 78){
    Serial.println("VOIDING NORMAL CARD");
    writeBlock(block, clearCardValue);
    writeBlock(block, normUseTwo);
  } else if(cardDat[4] == 75){
    Serial.println("SUPERCARD DETECTED; CONTINUING");
  }
}

int cardCheck(){
    if ( ! mfrc522.PICC_IsNewCardPresent()){
      return 0;
    }
    if ( ! mfrc522.PICC_ReadCardSerial()){
      return 0;
    }

    Serial.println();
    Serial.print(F("Card found. Identifying..."));
    Serial.println();
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("This sample only works with MIFARE Classic cards."));
        return;
    }

    readBlock(block, readCardValue); // check card status
    if(checkIfEmpty(readCardValue) == 1){ // if card is empty
        Serial.println("CARD EMPTY; REWRITING");
        writeBlock(block, normNewCardValue);
        Serial.println("DONE; STARTING");
        readBlock(block, readCardValue);
        Serial.print("read block: ");
        for (int j = 0 ; j < 16 ; j++){
            Serial.write (readCardValue[j]);
        }
        return 1;

    } else if(checkIfEmpty(readCardValue) == 0){ // if card is not empty
      if(checkIfValid(readCardValue) == 1){ // if card is valid
        Serial.println("CARD VALID; STARTING");
        deductCredit(readCardValue);
        readBlock(block, readCardValue);
        Serial.print("read block: ");
        for (int j = 0 ; j < 16 ; j++){
            Serial.write (readCardValue[j]);
        }
        return 1;

      } else if(checkIfValid(readCardValue) == 0){ // if card is invalid
        Serial.println("CARD INVALID; REWRITING");
        writeBlock(block, clearCardValue);
        writeBlock(block, normNewCardValue);
        Serial.println("DONE; STARTING");
        readBlock(block, readCardValue);
        Serial.print("read block: ");
        for (int j = 0 ; j < 16 ; j++){
            Serial.write (readCardValue[j]);
        }
        return 1;

      } else if(checkIfValid(readCardValue) == 2){ // if card is void
        Serial.println("CARD IS VOID");
        Serial.println("");
        readBlock(block, readCardValue);
        Serial.print("read block: ");
        for (int j = 0 ; j < 16 ; j++){
            Serial.write (readCardValue[j]);
        }
        return 2;
      }

    }

    Serial.println("");
    readBlock(block, readCardValue);
    Serial.print("read block: ");
    for (int j = 0 ; j < 16 ; j++){
      Serial.write (readCardValue[j]);
    }
}
