/*
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

/* Resources
 * -----------------------------------------------------------------------------------------
 * https://aaenics.com/2021/01/understanding-rfids-and-integrating-them-in-your-projects - Blocks and shit
 * https://randomnerdtutorials.com/security-access-using-mfrc522-rfid-reader-with-arduino/ - If/else logic
 * https://gettobyte.com/read-and-write-to-a-rfid-tag/ - I forgot
 * -----------------------------------------------------------------------------------------
 */

// Configuration
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         5           // Configurable, see typical pin layout above
#define SS_PIN          53          // Configurable, see typical pin layout above

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

// Denotes the block number being written/read to/from
int block = 13;

// Arrays with card values
byte normNewCardValue[16] = {"1U1TN"}; // 1 use 1 try
byte normUseTwo[16] = {"2UVN"}; // 2 use; void
byte specNewCardValue[16] = {"1U3TS"}; // 1 use 3 try
byte specUseTwo[16] = {"2U2TS"};
byte specUseThree[16] = {"3U1TS"};
byte specUseFour[16] = {"4UVS"}; // 4 use; void
byte clearCardValue[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

// Array to read back card value
byte readCardValue[18];

void setup() {
    Serial.begin(9600); // Initialize serial communications with the PC
    while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522 card
    Serial.println();
    Serial.println(F("Waiting for a card..."));

    // Prepare the key (used both as key A and as key B)
    // using FFFFFFFFFFFFh which is the default at chip delivery from the factory
    for (byte i = 0; i < 6; i++) {
        key.keyByte[i] = 0xFF;
    }

}

void loop() {
    // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
    if ( ! mfrc522.PICC_IsNewCardPresent()){
      return;
    }

    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()){
      return;
    }

    // Show some details of the PICC (that is: the tag/card)
    Serial.println();
    Serial.print(F("Card found. Identifying..."));
    Serial.println();
    Serial.print(F("Card UID:"));
    dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
    Serial.println();
    Serial.print(F("PICC type: "));
    MFRC522::PICC_Type piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
    Serial.println(mfrc522.PICC_GetTypeName(piccType));

    // Check for compatibility
    if (    piccType != MFRC522::PICC_TYPE_MIFARE_MINI
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_1K
        &&  piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
        Serial.println(F("This sample only works with MIFARE Classic cards."));
        return;
    }

    // Start actual code
    readBlock(block, readCardValue); // check card status
    if(checkIfEmpty(readCardValue) == 1){ // if card is empty
      Serial.println("CARD EMPTY; REWRITING");
      writeBlock(block, normNewCardValue);

    } else if(checkIfEmpty(readCardValue) == 0){ // if card is not empty

      if(checkIfValid(readCardValue) == 1){ // if card is valid
        Serial.println("CARD VALID; STARTING");
        deductCredit(readCardValue);
      } else if(checkIfValid(readCardValue) == 0){ // if card is invalid
        Serial.println("CARD INVALID; REWRITING");
        writeBlock(block, clearCardValue);
        writeBlock(block, normNewCardValue);
      } else if(checkIfValid(readCardValue) == 2){ // if card is void
        Serial.println("CARD IS VOID");

      }

    }

    Serial.println("");
    readBlock(block, readCardValue);
    Serial.print("read block: ");
    for (int j = 0 ; j < 16 ; j++){
      Serial.write (readCardValue[j]);
    }
    Serial.println("");
    Serial.write(readCardValue[4]);
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
    writeBlock(block, specUseFour);

  } else if(cardDat[2] == 50 && cardDat[4] == 83){
    Serial.println("REMOVING 1 SPECIAL TRY; 1 REMAIN");
    writeBlock(block, specUseThree);

  } else if(cardDat[2] == 51 && cardDat[4] == 83){
    Serial.println("REMOVING 1 SPECIAL TRY; 2 REMAIN");
    writeBlock(block, specUseTwo);

  } else if(cardDat[2] == 49 && cardDat[4] == 78){
    Serial.println("VOIDING NORMAL CARD");
    writeBlock(block, normUseTwo);
  }
}