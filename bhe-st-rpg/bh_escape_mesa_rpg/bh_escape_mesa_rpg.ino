// MESA RPG BH ESCAPE
// Sensores PN532
// Feito por Carlos e André - Novembro 2021

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
Adafruit_PN532 nfc[NUM_ADAPTERS] = {nfc0, nfc1, nfc2, nfc3};
boolean nfc_found[NUM_ADAPTERS] = {false, false, false, false};

String data[NUM_ADAPTERS];
boolean dataUpdate = false;
boolean rpgStatus = false;

// CARTAS
#define NUM_CARDS 9
#define CARD_NONE {0x00, 0x00, 0x00, 0x00}
#define CARD_CHICO_GUERREIRO {0xE9, 0x0, 0xBF, 0x99}
#define CARD_ESTOPA_CINZENTO {0xD9, 0x52, 0x63, 0xB9}
#define CARD_PEDRO_DRUIDA {0x49, 0x1F, 0x66, 0xB9}
#define CARD_MUDINHO_BARDO {0x59, 0xE5, 0x69, 0xB9}
#define CARD_LU_MAGA {0x09, 0xA, 0x69, 0xB9}
#define CARD_FELIPE_BARBARO {0x59, 0xE5, 0xC9, 0x99}
#define CARD_IAGO_ANAO {0xB9, 0xA2, 0xC9, 0x99}
#define CARD_TEST {0x51, 0x88, 0xE8, 0x21}

// IDs DAS CARTAS
#define ID_NONE 0
#define ID_CHICO_GUERREIRO 1
#define ID_ESTOPA_CINZENTO 2
#define ID_PEDRO_DRUIDA 3
#define ID_MUDINHO_BARDO 4
#define ID_LU_MAGA 5
#define ID_FELIPE_BARBARO 6
#define ID_IAGO_ANAO 7
#define ID_TEST 8

// ARRAY DE CARTAS
char CARDS[NUM_CARDS][4] = {
  CARD_NONE,
  CARD_CHICO_GUERREIRO,
  CARD_ESTOPA_CINZENTO,
  CARD_PEDRO_DRUIDA,
  CARD_MUDINHO_BARDO,
  CARD_LU_MAGA,
  CARD_FELIPE_BARBARO,
  CARD_IAGO_ANAO,
  CARD_TEST
};

// SOLUÇÃO RPG: Estopa, Felipe, Pedro e Mudinho
char RPG_answer[NUM_ADAPTERS] = { ID_ESTOPA_CINZENTO, ID_FELIPE_BARBARO, ID_PEDRO_DRUIDA, ID_MUDINHO_BARDO };

int cardsOk = 0;
int cards_on_table[NUM_ADAPTERS] = {ID_NONE,ID_NONE,ID_NONE,ID_NONE};

void setup() {
  Serial.begin(115200);
  Serial.println("Initializing NFC Readers");

  for ( int i = 0; i < NUM_ADAPTERS; i++ ) {
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
    for ( int i = 0; i < NUM_ADAPTERS; i++ ) {
      if (!nfc_found[i]) continue;
      boolean success;
      boolean card_found;
      uint8_t uid[] = { 0, 0, 0, 0, 0, 0, 0 };  // Buffer to store the returned UID
      uint8_t uidLength;                        // Length of the UID (4 or 7 bytes depending on ISO14443A card type)
    

      // Wait for an ISO14443A type cards (Mifare, etc.).  When one is found
      // 'uid' will be populated with the UID, and uidLength will indicate
      // if the uid is 4 bytes (Mifare Classic) or 7 bytes (Mifare Ultralight)
      success = nfc[i].readPassiveTargetID(PN532_MIFARE_ISO14443A, &uid[0], &uidLength, 100);
    
      if (success) {
        //Serial.println("Found a card!");
        //Serial.print("SS:" + String(i)+ " ");
        //Serial.print("UID Length: "); Serial.print(uidLength, DEC); Serial.println(" bytes");
        //Serial.print("UID Value: ");
        for (uint8_t i=0; i < uidLength; i++) {
          Serial.print(" 0x"); Serial.print(uid[i], HEX); 
        }
        Serial.println("");
        // test to check if it's the right card
        // should set the cards with a code to avoid having to fix the code when replacing defective or worn cards
        // if its the right card increments the cardsOk counter
        card_found = false;
        for ( int card_id = 0; card_id < NUM_CARDS; card_id++ ) {
          if (memcmp(CARDS[card_id], uid, 4) == 0) {
            // found a card in the card library, save on cards_on_table
            Serial.println("Found card: pos(" + String(i)+") card("+String(card_id)+")");
            cards_on_table[i] = card_id;
            card_found = true;
            break;
          }
        }
        // if it finishes the loop without finding the card, zero the cards_on_table entry for the sensor
        if (!card_found) {
          if (cards_on_table[i] != ID_NONE) {
            // card was removed
            Serial.println("Removed card:" + String(i));
            cards_on_table[i] = ID_NONE;
          }
        }
      }
      else {
        // check if there was a card there before
        if (cards_on_table[i] != ID_NONE) {
          // card was removed
          Serial.println("Removed card:" + String(i));
          cards_on_table[i] = ID_NONE;
        }
      }
      
      // 50ms delay between card reads; 200ms to read all four cards
      delay(50);
    }

    /// counts how many cards are in the right position
    cardsOk = 0;
    for ( int i = 0; i < NUM_ADAPTERS; i++ ) {  
      if (RPG_answer[i] == cards_on_table[i]) {
        cardsOk++;        
      }
    }
    if (cardsOk == 4) {
      Serial.print("Game solved!");
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
