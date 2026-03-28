#include <Arduino.h>
#include <fastLED.h>

#define NUM_RINGS 5
#define LEDS_PER_RING 45

#define DATA_PIN    6
#define NUM_LEDS    NUM_RINGS * LEDS_PER_RING   // Total number of LEDs
#define LED_TYPE    WS2812B                     // LED Type
#define COLOR_ORDER GRB                         // Color channel order

/** Define default colours */
#define BLUE CRGB::Blue;
#define RED CRGB::Red;
#define YELLOW CRGB::Yellow;
#define ORANGE CRGB(230, 35, 0);
#define WHITE CRGB::White;

/** Colours of the Buddhist Flag */
CRGB FLAG_COLOURS[] = {BLUE, YELLOW, RED, WHITE, ORANGE};


CRGB leds[NUM_LEDS];

void rainbow();
void red();
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
  // CRGB colours[] = {CRGB::Red, CRGB::White, CRGB::Blue, CRGB::Yellow, CRGB(230, 35, 0)};
  for (int j = 0; j < LEDS_PER_RING; j++) {
    for (int i = 0; i < NUM_RINGS; i++) {
      for (int k = 0; k < 5; k++) {
        leds[i * LEDS_PER_RING + (j + k * len) % LEDS_PER_RING] = FLAG_COLOURS[k];
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
}

void buddhist_flag_rotate() {
  int len = 0;
  for (int i = 0; i < NUM_RINGS; i++) {
    for (int j = 0; j < LEDS_PER_RING; j++) {
      for (int k = 0; k < 5; k++) {
        leds[i * LEDS_PER_RING + (j + k * len) % LEDS_PER_RING] = FLAG_COLOURS[k];
        // Serial.println(k);
      }
    }
    FastLED.show();
    delay(100);
  }
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