// MESA RPG BH ESCAPE
// Sensores PN532
// Feito por Carlos e André - Novembro 2021


//CARTAS:
//
//Chico o Guerreiro
//0xE9 0x0 0xBF 0x99
//
//Estopa o Cinzento
//0xD9 0x52 0x63 0xB9
//
//Pedro o Druida
//0x49 0x1F 0x66 0xB9
//
//Mudinho o Bardo
//0x59 0xE5 0x69 0xB9
//
//Lu a Maga
//0x9 0xA 0x69 0xB9
//
//Felipe o Barbaro
//0x59 0xE5 0xC9 0x99
//
//Iago o Anao
//0xB9 0xA2 0xC9 0x99


//Bibliotecas

#include <Wire.h>
#include <SPI.h>
#include <Adafruit_PN532.h>

// Control pins
#define RPG_RESET 8
#define RPG_STATUS 9

// If using the breakout with SPI, define the pins for SPI communication.
#define PN532_SCK  (13)
#define PN532_MOSI (11)
#define PN532_MISO (12)

// Uncomment just _one_ line below depending on how your breakout or shield
// is connected to the Arduino:

// Use this line for a breakout with a software SPI connection (recommended):
Adafruit_PN532 nfc0(PN532_SCK, PN532_MISO, PN532_MOSI, 7);
Adafruit_PN532 nfc1(PN532_SCK, PN532_MISO, PN532_MOSI, 4);
Adafruit_PN532 nfc2(PN532_SCK, PN532_MISO, PN532_MOSI, 5);
Adafruit_PN532 nfc3(PN532_SCK, PN532_MISO, PN532_MOSI, 6);

#define NUM_ADAPTERS 4
#define MAX_ADAPTERS 4
Adafruit_PN532 nfc[NUM_ADAPTERS] = {nfc0, nfc1, nfc2, nfc3};
boolean nfc_found[NUM_ADAPTERS] = {false, false, false, false};

String data[NUM_ADAPTERS];
boolean dataUpdate = false;
boolean rpgStatus = false;
int cardsOk = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing NFC Readers");

  for ( int i = 0; i < MAX_ADAPTERS; i++ ) {
    Serial.println("Init Board " + String(i) + "...");
    nfc[i].begin();

    uint32_t versiondata = nfc[i].getFirmwareVersion();
    if (! versiondata) {
      Serial.print("Didn't find PN53x board");
    }
    else {
      // Got ok data, print it out!
      Serial.print("Found chip PN5"); Serial.println((versiondata>>24) & 0xFF, HEX); 
      Serial.print("Firmware ver. "); Serial.print((versiondata>>16) & 0xFF, DEC); 
      Serial.print('.'); Serial.println((versiondata>>8) & 0xFF, DEC);
      nfc_found[i] = true;
      modela 
      
      // configure board to read RFID tags
      nfc[i].SAMConfig();
    }
  }
  
  // pinMode(RPG_RESET, INPUT_PULLUP);
  // pinMode(RPG_STATUS, OUTPUT);
}

void reset() {
  // If the RPG_RESET pin is activated, clears the status to restart the game
  rpgStatus = false;
//  digitalWrite(RPG_STATUS, LOW);
}

void set_rpg_ok() {
  // game is solved, sthe the status pin HIGH and keep it until reset
  rpgStatus = true;
//  digitalWrite(RPG_STATUS, HIGH);
}

void loop() {
  if (!rpgStatus) {
    for ( int i = 0; i < MAX_ADAPTERS; i++ ) {
      if (!nfc_found[i]) continue;
      boolean success;
      uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
      uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    

      // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
      // 'uid' will be populated with the UID, and uidLength will indicate
      // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
      success = nfc[i].readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength, 100);
    
      if (success) {
        Serial.println("Found a card!");
        Serial.print("SS:" + String(i)+ " ");
        Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
        Serial.print("UID Value: ");
        for (uint8_t i=0; i < uidLength; i++) {
          Serial.print(" 0x");Serial.print(uid[i], HEX); 
        }
        Serial.println("");
        // test to check if it's the right card
        // should set the cards with a code to avoid having to fix the code when replacing cards
        // if its the right card increments the cardsOk counter
      }

      // 50ms delay between card reads; 200ms to read all four cards
      delay(50);
    }
    if (cardsOk == 4) {
      set_rpg_ok();
    }
  }

  // reads the status sign
  {
    int rpgReset = 1;
    // rpgReset = digitalRead(RPG_RESET);
    if (!rpgReset) {
      reset();
    }
  }
}
