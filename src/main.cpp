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
void rotate();
void shiftRingColours(int shift_num, int ring_num);

void setup() {
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
    // Serial.begin(9600);
    // set LEDs to rainbow    
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
  // shiftRingColours(1, 0);
  rotate();
  
  // delay(100);
}

void rainbow() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_RINGS; i++) {
    for (int j = 0; j < LEDS_PER_RING; j++) {
      leds[i * LEDS_PER_RING + j] = CHSV(hue, 255, 255);
      hue += 2;
    }
    
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
  FastLED.show();
  delay(1000);
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

void rotate() {
  int len = 9;

  CRGB colours[] = {CRGB::Blue, CRGB::Yellow, CRGB::Red, CRGB::White, CRGB(230, 35, 0)};
  // CRGB colours[] = {CRGB::Red, CRGB::White, CRGB::Blue, CRGB::Yellow, CRGB(230, 35, 0)};
  for (int j = 0; j < LEDS_PER_RING; j++) {
    for (int i = 0; i < NUM_RINGS; i++) {
      for (int k = 0; k < 5; k++) {
        leds[i * LEDS_PER_RING + (j + k * len) % LEDS_PER_RING] = colours[k];
        // Serial.println(k);
      }
      // int pos = (j - len) % LEDS_PER_RING;
      // // This solves the tail leds staying permanently on,
      // // as they are not accessed when j < len.
      // if (j < len) {
        //   pos += LEDS_PER_RING;
        // }
        // leds[i * LEDS_PER_RING + pos] = CRGB::Black;
      FastLED.show();
      // delay(1);
    }
    
  }
  // int len = 1;
  // for (int i = 0; i < LEDS_PER_RING; i++) {
  //   for (int j = 0; j < len; j++) {
  //     leds[(i - j) % LEDS_PER_RING] = CRGB::Blue;
  //   }
  //   if (i - len >= 0) {
  //     leds[i - len] = CRGB::Black;
  //   }
  //   FastLED.show();
  //   delay(100);
  // }

  // leds[LEDS_PER_RING - 1] = CRGB::Black;
}

/**
 * @brief Shifts the colours within a specific ring
 */
void shiftRingColours(int shift_num, int ring_num) {
  // shift colours inside each circle
  shift_num = shift_num % LEDS_PER_RING;
  int temp_len = LEDS_PER_RING - shift_num;
  CRGB temp[LEDS_PER_RING];
  int ring_pos = ring_num * LEDS_PER_RING;
  size_t ring_shift = sizeof(CRGB) * (ring_pos % NUM_RINGS);
  size_t led_shift = sizeof(CRGB) * shift_num;
  size_t temp_shift = sizeof(CRGB) * temp_len;

  memcpy(temp, (void *) leds + ring_shift + temp_shift, temp_shift);
  memmove(leds + ring_shift, (void *) leds + ring_shift + temp_shift, led_shift);
  memcpy(leds + ring_shift, temp, temp_shift);
  FastLED.show();
}