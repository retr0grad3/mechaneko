#include <FastLED.h>

#define DATA_PIN 7
#define NUM_LEDS 47

CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  // Set all LEDs to MECHA PINK
  fill_solid(leds, NUM_LEDS, CRGB::CRGB(255, 110, 188));
  FastLED.show();
  delay(1000);

  // Set all LEDs to BABY BLUE
  fill_solid(leds, NUM_LEDS, CRGB::CRGB(109, 163, 103));
  FastLED.show();
  delay(1000);
  
  // Set all LEDs to AZUMI PURPLE
  fill_solid(leds, NUM_LEDS, CRGB::CRGB(167, 75, 208));
  FastLED.show();
  delay(1000);

}