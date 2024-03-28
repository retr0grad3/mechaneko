# 1 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"

/*



Claw machine designed by MECHANEKO.

6-axis movement, no diagonal movement of the gantry (which uses "yellow gearbox" motors).

Uses RFID cards in lieu of coins (feature unavailable). 



(c) 2024 Kevin Takamura, MECHANEKO

mechaneko.carrd.co



*/
# 13 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
# 14 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 2
# 15 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 2
# 16 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 2
# 17 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 2
# 18 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 2
# 19 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 2
# 20 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 2
# 21 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 2

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
# 36 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
// Digital input: joystick
const int joystickFwd = 22;
const int joystickBck = 23;
const int joystickRight = 24;
const int joystickLeft = 25;

// Button/claw controls
const int multiButton = 49;

// PWM output: OLED







Adafruit_SSD1306 display(128 /* OLED display width, in pixels*/, 64 /* OLED display height, in pixels*/,
  11 /* SDA*/, 12 /* SCK*/, 9, 8 /* RST*/, 10);

// Output: RGB strip


CRGB leds[47];

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


// MOSI ------> 51
// MISO ------> 50
// SCK  ------> 52

MFRC522 mfrc522(53 /* SDA*/, 5); // Create MFRC522 instance.
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
long intervalStart = 500; // rate of blink for 'insert coin' / 'game over'
long intervalIdle = 2000; // rate of blink for 'push start to begin'
long previousMillis = 0;

void setup(){
    Serial.begin(9600);
    setTime(01, 01, 00, 9, 9, 1999); // (Hour, minute, second, day, month, year)

    display.clearDisplay();
    display.setTextSize(2); // Normal 1:1 pixel scale
    display.setCursor(12,22);
    display.setTextColor(1 /*|< Draw 'on' pixels*/); // Draw 'inverse' text
    display.println("MECHANEKO");
    display.display();

    // Joystick pin modes
    pinMode(joystickFwd, 0x2);
    pinMode(joystickBck, 0x2);
    pinMode(joystickLeft, 0x2);
    pinMode(joystickRight, 0x2);

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

    // Button/claw pin modes
    pinMode(servoPower, 0x1);
    pinMode(multiButton, 0x0);
    digitalWrite(multiButton, 0x2);
    digitalWrite(servoPower, 0x0);
    pinMode(xLimit, 0x0);
    pinMode(zLimit, 0x0);

    clawServo.attach(6);
    clawServo.write(105);

    SPI.begin(); // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    Serial.println();
    Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 162 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                  (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 162 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                  "Waiting for a card..."
# 162 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                  ); &__c[0];}))
# 162 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                  )));

    FastLED.addLeds<NEOPIXEL, 7>(leds, 47);

    fill_solid(leds, 47, CRGB::CRGB(167, 75, 208));
    FastLED.show();

    if(!display.begin(0x02 /*|< Gen. display voltage from 3.3V*/)) {
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 170 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 170 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                      "SSD1306 allocation failed"
# 170 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                      ); &__c[0];}))
# 170 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                      )));
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
    display.setTextColor(1 /*|< Draw 'on' pixels*/);
    display.println("MECHANEKO");
    display.setTextSize(1);
    display.setCursor(14, 48);
    display.setTextColor(1 /*|< Draw 'on' pixels*/);
    display.println("TAP TO START");
    display.display();
    cardCheck();

    // Game end 
    // -----------------------------------------------------------------------------------------
    if(second() == timeLimit || continueGame == 0){
        continueGame = 0;
        display.clearDisplay();
        display.setTextSize(2); // Normal 1:1 pixel scale
        display.setCursor(14,24);
        display.setTextColor(1 /*|< Draw 'on' pixels*/); // Draw 'inverse' text
        display.println("Time's Up");
        display.display();

        clawServo.write(55);
        delay(1000);
        clawServo.write(105);
        delay(1000);
        digitalWrite(servoPower, 0x0);
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
            display.setTextColor(1 /*|< Draw 'on' pixels*/);
            display.println("MECHANEKO");
            display.setTextSize(1);
            display.setCursor(14, 48);
            display.setTextColor(1 /*|< Draw 'on' pixels*/);
            display.println("PUSH BUTTON");
            display.display();
        } while(digitalRead(multiButton) == 0x1);
        runGame();
    } else if(cardCheck() == 2){
        display.clearDisplay();
        display.setTextSize(2);
        display.setCursor(12, 22);
        display.setTextColor(1 /*|< Draw 'on' pixels*/);
        display.println("MECHANEKO");
        display.setTextSize(1);
        display.setCursor(14, 48);
        display.setTextColor(1 /*|< Draw 'on' pixels*/);
        display.println("NO TRIES LEFT");
        display.display();
        delay(7500);
    } else if(cardCheck() == 0){
        return;
    }
}

void runGame(){
    setTime(01,01,00,9,9,1999);
    digitalWrite(servoPower, 0x1);

    while(second() < timeLimit && year() == 1999){
        display.clearDisplay();
        display.setTextSize(2); // Normal 1:1 pixel scale
        display.setTextColor(1 /*|< Draw 'on' pixels*/); // Draw white text
        display.setCursor(12, 22); // Start at top-left corner
        display.print((reinterpret_cast<const __FlashStringHelper *>(
# 258 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                     (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 258 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                     "Time: "
# 258 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                     ); &__c[0];}))
# 258 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                     )));
        display.print(second()-timeLimit);
        display.display();

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

void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], 16);
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
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 532 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 532 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                "Card found. Identifying..."
# 532 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                ); &__c[0];}))
# 532 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                )));
    Serial.println();
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 534 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 534 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                "Card UID:"
# 534 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                ); &__c[0];}))
# 534 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                )));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print((reinterpret_cast<const __FlashStringHelper *>(
# 537 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 537 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                "PICC type: "
# 537 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                ); &__c[0];}))
# 537 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                )));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    if ( piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        && piccType != MFRC522::PICC_TYPE_MIFARE_1K
        && piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 544 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 544 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                      "This sample only works with MIFARE Classic cards."
# 544 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino" 3
                      ); &__c[0];}))
# 544 "C:\\Users\\kevi1\\Documents\\GitHub\\mechaneko\\final\\full-final\\full-final.ino"
                      )));
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
