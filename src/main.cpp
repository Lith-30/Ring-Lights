#include <Arduino.h>
#include <fastLED.h>

#define UINT8_MAX 256

#define NUM_RINGS 5
#define LEDS_PER_RING 45

#define DATA_PIN    6
#define NUM_LEDS    NUM_RINGS * LEDS_PER_RING   // Total number of LEDs
#define LED_TYPE    WS2812B                     // LED Type
#define COLOR_ORDER GRB                         // Color channel order

/** Define default colours */
#define BLUE    CRGB::Blue
#define RED     CRGB::Red
#define YELLOW  CRGB::Yellow
#define ORANGE  CRGB(230, 35, 0)
#define WHITE   CRGB::White

/** Colours of the Buddhist Flag */
CRGB FLAG_COLOURS[] = {BLUE, YELLOW, RED, WHITE, ORANGE};


CRGB leds[NUM_LEDS];

void rainbow();
void rotate();
void shiftRingColours(int shift_num, int ring_num);
void buddhist_flag_rotate();
void fade();
void flash(int gap = 20);

void setup() {
    FastLED.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(50);
    Serial.begin(9600);
}

/**
 * @brief Main loop
 */
void loop() {
  buddhist_flag_rotate();
  FastLED.show();
  delay(1);
}

/**
 * @brief Make rings show a rainbow pattern
 */
void rainbow() {
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_RINGS; i++) {
    for (int j = 0; j < LEDS_PER_RING; j++) {
      leds[i * LEDS_PER_RING + j] = CHSV(hue, 255, 255);
    }
    hue += 1;
  }
}


/**
* @brief Sets the rings to show the colour of the buddhist flag rotating around rings 
*/
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

/**
 * Same as rotate function, but more optimised WIP
 */
void buddhist_flag_rotate() {
  int len = 9;
  static uint8_t offset = 0;
  for (int i = 0; i < NUM_RINGS; i++) {
    for (int j = 0; j < LEDS_PER_RING; j++) {
      leds[i * LEDS_PER_RING + (j + offset) % LEDS_PER_RING] = FLAG_COLOURS[j / len];
    }
  }
  offset++;
  offset %= NUM_LEDS;
}

/**
 * @brief Add make lights fade on and off
 */
void fade() {
  // when fade = 0 we have max original brightness
  // when fade = 256 we have low brightness
  static uint8_t fade_level = 0;
  double fade_percent = (double) (UINT8_MAX - fade_level) / UINT8_MAX;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i].r *= fade_percent;
    leds[i].g *= fade_percent;
    leds[i].b *= fade_percent;
  }
  fade_level++;
}

/**
 * @brief Add make lights flash on and off
 */
void flash(int gap) {
  // when fade = 0 we have max original brightness
  // when fade = 256 we have low brightness
  static uint8_t flash_clock = 0;
  if ((flash_clock / gap) % 2) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].r *= 0;
      leds[i].g *= 0;
      leds[i].b *= 0;
    }
  }
  flash_clock++;
}

/**
 * @brief Shifts the colours within a specific ring. WIP
 */
void shiftRingColours(int shift_num, int ring_num) {
  // shift colours inside each circle
  shift_num = shift_num % LEDS_PER_RING;
  int temp_len = LEDS_PER_RING - shift_num;

  CRGB temp[LEDS_PER_RING];
  int ring_pos = ring_num * LEDS_PER_RING;
  int next_ring_pos = (1 + ring_num) * LEDS_PER_RING;

  memcpy(temp, (void *) leds + (next_ring_pos - shift_num - 1), shift_num);
  memmove(leds + ring_pos, (void *) leds + ring_pos + shift_num, LEDS_PER_RING - shift_num);
  memcpy(leds + ring_pos, temp, shift_num);
}