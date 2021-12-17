//Bombas BH Escape Sala Stranger Things
//Código por André Solis v1.0 de 15/11/21

//Biblioteca dos Neopixels
#include <Adafruit_NeoPixel.h>

// FITAS COLUNA (2X DE 7 LEDS)
#define LED_PIN     4
// How many NeoPixels are attached to the Arduino?
#define LED_COUNT  7


// FITA BASE (1X DE 10 LEDS)
#define LED2_PIN    2
// How many NeoPixels are attached to the Arduino?
#define LED2_COUNT  10


// BRILHO DA FITA, 0 (min) to 255 (max)
#define BRIGHTNESS 70 // Set BRIGHTNESS to about 1/5 (max = 255)
#define BRIGHTNESS2 30 // Set BRIGHTNESS to about 1/5 (max = 255)
//Botão


bool oldState = HIGH;
int     mode     = 0;
int BUTTON_PIN = 6;
 
// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2(LED2_COUNT, LED2_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // LED_PIN = LOW;
  // LED_PIN2 = LOW;
  delay(200);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(BRIGHTNESS);
  strip2.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip2.show();            // Turn OFF all pixels ASAP
  strip2.setBrightness(BRIGHTNESS2);
  strip.clear();
  strip2.clear();
  strip.show();
  strip2.show();

  //buzzer
//
pinMode(8,OUTPUT);

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  colorWipe(strip.Color(  20,   10,   40), 50);    // amarelo fraco
  colorWipe2(strip2.Color(  20,   10,   40), 50);    // amarelo fraco

  
}

void loop() {

  strip.clear();
  strip2.clear();
  colorWipe(strip.Color(  20,   10,   40), 50);    // amarelo fraco
  colorWipe2(strip2.Color(  20,   10,   40), 50);    // amarelo fraco
  delay(1000);


  // Get current button state.
  boolean newState = digitalRead(BUTTON_PIN);

  // Check if state changed from high to low (button press).
  if ((newState == LOW) && (oldState == HIGH)) {
    // Short delay to debounce button.
    delay(20);
    // Check if button is still low after debounce.
    newState = digitalRead(BUTTON_PIN);
    if (newState == LOW) {     // Yes, still low
      if (++mode > 2) mode = 0; // Advance to next mode, wrap around after #8
      switch (mode) {          // Start the new animation...
        case 0:

          //BOMBA ATIVADA

          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 300); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 100); //
          delay(50);

          tone(8, 200, 100); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 100); //
          delay(50);

          tone(8, 200, 300); ////
          colorWipe2(strip2.Color(127,   0,   0), 50); // red
          colorWipe(strip.Color(127,   0,   0), 50);
          
          delay(50);
          tone(8, 950, 100); //
          delay(50);

          tone(8, 200, 100); ////
          
          break;


        case 1:

          //BOMBA PRÉ ATIVADA, MOSTRA O JOGADOR COMO ATIVAR A BOMBA
          colorWipe(strip2.Color(0,   127,   127), 100); // BLUE
          colorWipe2(strip2.Color(0,   127,   127), 100); //
          colorWipe(strip2.Color(0,   127,   127), 100); //
          break;
      }
    }
  }
}
void colorWipe2(uint32_t color, int wait) {
  for (int i = 0; i < strip2.numPixels(); i++) { // For each pixel in strip...
    strip2.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip2.show();
    delay(wait);
  }
}
void colorWipe(uint32_t color, int wait) {
  for (int i = 0; i < strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
void theaterChase2(uint32_t color, int wait) {
  for (int a = 0; a < 1000; a++) { // Repeat 10 times...
    for (int b = 0; b < 3; b++) { //  'b' counts from 0 to 2...
      strip.clear();         //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < strip.numPixels(); c += 3) {
        strip.setPixelColor(c, (127,   0,   0)); // Set pixel 'c' to value 'color'
      }
      strip.show(); // Update strip with new contents

      delay(100);  // Pause for a moment

    }
  }
}
