#include <Arduino.h>
#include <fastLED.h>

#define NUM_RINGS 5
#define LEDS_PER_RING 45

#define DATA_PIN    6
#define NUM_LEDS    NUM_RINGS * LEDS_PER_RING   // Total number of LEDs
#define LED_TYPE    WS2812B                     // LED Type
#define COLOR_ORDER GRB                         // Color channel order

CRGB leds[NUM_LEDS];

void rainbow();
void red();
void flag_colours();

void setup() {
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
    Serial.begin(9600);
}

void loop() {
  // for (int j = 0; j < LEDS_PER_RING j++) {
  //   if (j > 1) {
  //     leds[j - 1] = CRGB::Black;
  //   }
  //   leds[j] = CRGB::Orange;
  // }
  // FastLED.show();
  // rainbow();
  flag_colours();
}

void rainbow() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_RINGS; i++) {
    for (int j = 0; j < LEDS_PER_RING; j++) {
      leds[i * LEDS_PER_RING + j] = CHSV(hue, 255, 255);
    }
    hue++;
    delay(10);
  }

  FastLED.show();
}

void flag_colours() {
  // blue yellow red white orange
  // first ring
  for (int i = 0; i < LEDS_PER_RING; i++) {
    leds[180 + i] = CRGB::Blue;
  }
  for (int i = 0; i < LEDS_PER_RING; i++) {
    leds[135 + i] = CRGB(255, 190, 0);
  }
  for (int i = 0; i < LEDS_PER_RING; i++) {
    leds[90 + i] = CRGB::Red;
  }
  for (int i = 0; i < LEDS_PER_RING; i++) {
    leds[45 + i] = CRGB::White;
  }
  for (int i = 0; i < LEDS_PER_RING; i++) {
    leds[0 + i] = CRGB(230, 35, 0);
  }
  delay(1000);
  FastLED.show();
  for (int i = 0; i < NUM_RINGS; i++) {
    for (int j = 0; j < LEDS_PER_RING; j++) {
      leds[i * LEDS_PER_RING + j] = CRGB::Black;
      // Serial.println(i * LEDS_PER_RING + j);
    }
  }
  FastLED.show();
  delay(1000);
  
  // Serial.println("set black");
  
   
}

void red() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_RINGS; i++) {
    for (int j = 0; j < LEDS_PER_RING; j++) {
      if ((i * LEDS_PER_RING + j) % 2) {
        leds[i * LEDS_PER_RING + j] = CRGB(255, 0, 0);
      } else {
        leds[i * LEDS_PER_RING + j] = CRGB(100, 100, 100);
      }
      
    }
    hue++;
    
  }

  FastLED.show();
  delay(1000);
  for (int i = 0; i < NUM_RINGS; i++) {
    for (int j = 0; j < LEDS_PER_RING; j++) {
      if ((i * LEDS_PER_RING + j) % 2 == 0) {
        leds[i * LEDS_PER_RING + j] = CRGB(255, 0, 0);
      } else {
        leds[i * LEDS_PER_RING + j] = CRGB(100, 100, 100);
      }
      
    }
    hue++;
    
  }
  FastLED.show();
  delay(1000);
}



// Flashing lights
// Rainbow fade
