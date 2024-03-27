
/*

Claw machine designed by MECHANEKO.
6-axis movement, no diagonal movement of the gantry (which uses "yellow gearbox" motors).
Uses RFID cards in lieu of coins (feature unavailable). 

(c) 2024 Kevin Takamura, MECHANEKO
mechaneko.carrd.co

*/

#include <FastLED.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// PWM output: OLED
#define OLED_MOSI  11 // SDA
#define OLED_CLK   12 // SCK
#define OLED_DC    9
#define OLED_CS    10
#define OLED_RESET 8  // RST
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

// Output: RGB strip
#define DATA_PIN 7
#define NUM_LEDS 47
CRGB leds[NUM_LEDS];

void setup(){
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(SSD1306_SWITCHCAPVCC)) {
        Serial.println(F("SSD1306 allocation failed"));
        for(;;); // Don't proceed, loop forever
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(12, 22);    
    display.setTextColor(SSD1306_WHITE);
    display.println("MECHANEKO");
    display.setTextSize(1);
    display.setCursor(14, 44); 
    display.setTextColor(SSD1306_WHITE); // Draw 'inverse' text
    display.println("OUT OF SERVICE :(");
    display.display();

    FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);

    fill_solid(leds, NUM_LEDS, CRGB::CRGB(167, 75, 208));
    FastLED.show();

    Serial.begin(9600);

}

void loop(){

}