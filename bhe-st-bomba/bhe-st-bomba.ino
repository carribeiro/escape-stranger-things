// Bombas BH Escape Sala Stranger Things
// Código por André Solis v1.0 de 15/11/21

//Biblioteca dos Neopixels
#include <Adafruit_NeoPixel.h>

#define tempo (300)

// FITAS COLUNA (2X DE 7 LEDS)
#define LED_PIN     4
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  7


// FITA BASE (1X DE 10 LEDS)
#define LED2_PIN    2
// How many NeoPixels are attached to the Arduino?
#define LED2_COUNT  10


// BRILHO DA FITA EM MODO STANDBY
#define BRILHO_CORPO_BOMBA_STANDBY 50
#define BRILHO_BASE_BOMBA_STANDBY  20

// BRILHO DA FITA EM MODO ATIVO (ARMANDO, OU JÁ ARMADA)
#define BRILHO_CORPO_BOMBA_ATIVA 80
#define BRILHO_BASE_BOMBA_ATIVA  40

// STATUS DA BOMBA
#define BOMBA_STANDBY 0
#define BOMBA_ARMADA 2
#define BUZZER 8
#define LED_BOMBA_ATIVA 9

int status_bomba = BOMBA_STANDBY;
int status_animacao = 0;

//Botão
bool oldState  = HIGH;
int BUTTON_PIN = 6;
 
// Declare our NeoPixel strip object:
Adafruit_NeoPixel led_corpo_bomba(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel led_base_bomba(LED2_COUNT, LED2_PIN, NEO_GRB + NEO_KHZ800);

void seta_led_base_bomba(uint32_t color) {
  for (int i = 0; i < led_base_bomba.numPixels(); i++) { // For each pixel in led_corpo_bomba...
    led_base_bomba.setPixelColor(i, color);              //  Set pixel's color (in RAM)
    led_base_bomba.show();
  }
}

void seta_led_corpo_bomba(uint32_t color) {
  for (int i = 0; i < led_corpo_bomba.numPixels(); i++) { // For each pixel in led_corpo_bomba...
    led_corpo_bomba.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    led_corpo_bomba.show();                          //  Update strip to match
  }
}

void theaterChase2(uint32_t color, int wait) {
  for (int a = 0; a < 1000; a++) { // Repeat 10 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      led_corpo_bomba.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < led_corpo_bomba.numPixels(); c += 3) {
        led_corpo_bomba.setPixelColor(c, (127,   0,   0)); // Set pixel 'c' to value 'color'
      }
      led_corpo_bomba.show(); // Update strip with new contents

      delay(100);  // Pause for a moment

    }
  }
}

void setup() {

  // esperar o LED inicializar (não sabemos se precisa disso)
  delay(200);

  // inicialização dos LEDs
  led_corpo_bomba.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  led_corpo_bomba.show();
  led_corpo_bomba.clear();
  led_corpo_bomba.setBrightness(BRILHO_CORPO_BOMBA_STANDBY);

  led_base_bomba.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  led_base_bomba.show();
  led_corpo_bomba.clear();
  led_base_bomba.setBrightness(BRILHO_BASE_BOMBA_STANDBY);

  // buzzer
  pinMode(BUZZER, OUTPUT);

  // botão
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  // led bomba ativa
  pinMode(LED_BOMBA_ATIVA, OUTPUT);
  digitalWrite(LED_BOMBA_ATIVA, LOW);

  // status da bomba
  status_bomba = BOMBA_STANDBY;
  seta_led_corpo_bomba(led_corpo_bomba.Color(  20,   10,   40));    // lilás fraco
  seta_led_base_bomba(led_base_bomba.Color(  20,   10,   40));      // lilás fraco
 
  Serial.begin(115200); 
}

void loop() {

  // Verifica se o botão foi pressionado
  boolean newState = digitalRead(BUTTON_PIN);
  if ((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {     // Yes, still low
      switch (status_bomba) {
        case BOMBA_STANDBY:
          Serial.println("Estado ONLINE --> ATIVA"); 
          digitalWrite(LED_BOMBA_ATIVA, HIGH);
          status_bomba = BOMBA_ARMADA;
          break;
        case BOMBA_ARMADA:
          Serial.println("Estado ATIVA --> ONLINE"); 
          digitalWrite(LED_BOMBA_ATIVA, LOW);
          status_bomba = BOMBA_STANDBY;
          status_animacao = 0;
          break;
      }
    }
  }
  oldState = newState;

  switch (status_bomba) {
    case BOMBA_STANDBY:
      // não tem animação no modo standby, fica com luz fraca
      led_corpo_bomba.setBrightness(BRILHO_CORPO_BOMBA_STANDBY);
      seta_led_corpo_bomba(led_corpo_bomba.Color(  20,   10,   40));    // lilás fraco
      led_base_bomba.setBrightness(BRILHO_BASE_BOMBA_STANDBY);
      seta_led_base_bomba(led_base_bomba.Color(  20,   10,   40));      // lilás fraco
      break;

    case BOMBA_ARMADA:

      if (status_animacao == 0) {
        seta_led_base_bomba(led_base_bomba.Color(127,   0,   0)); // red
        seta_led_corpo_bomba(led_corpo_bomba.Color(127,   0,   0));        
        tone(BUZZER, 950, 350); 
        delay(tempo);
        status_animacao = 1;
      }
      else {
        led_base_bomba.clear();
        led_base_bomba.show();
        led_corpo_bomba.clear();
        led_corpo_bomba.show();
        tone(BUZZER, 200, 350);
        delay(tempo);
        status_animacao = 0;
      }

      break;
  }
}
