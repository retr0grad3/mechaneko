# 1 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino"

/*



Claw machine designed by MECHANEKO.

6-axis movement, no diagonal movement of the gantry (which uses "yellow gearbox" motors).

Uses RFID cards in lieu of coins (feature unavailable). 



(c) 2024 Kevin Takamura, MECHANEKO

mechaneko.carrd.co



*/
# 13 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino"
# 14 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino" 2
# 15 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino" 2
# 16 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino" 2
# 17 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino" 2
# 18 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino" 2

// PWM output: OLED







Adafruit_SSD1306 display(128 /* OLED display width, in pixels*/, 64 /* OLED display height, in pixels*/,
  11 /* SDA*/, 12 /* SCK*/, 9, 8 /* RST*/, 10);

// Output: RGB strip


CRGB leds[47];

void setup(){
    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if(!display.begin(0x02 /*|< Gen. display voltage from 3.3V*/)) {
        Serial.println((reinterpret_cast<const __FlashStringHelper *>(
# 38 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino" 3
                      (__extension__({static const char __c[] __attribute__((__progmem__)) = (
# 38 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino"
                      "SSD1306 allocation failed"
# 38 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino" 3
                      ); &__c[0];}))
# 38 "C:\\Users\\kebin\\Documents\\GitHub\\mechaneko\\final\\outofservice-final\\outofservice-final.ino"
                      )));
        for(;;); // Don't proceed, loop forever
    }

    display.clearDisplay();
    display.setTextSize(2);
    display.setCursor(12, 22);
    display.setTextColor(1 /*|< Draw 'on' pixels*/);
    display.println("MECHANEKO");
    display.setTextSize(1);
    display.setCursor(14, 44);
    display.setTextColor(1 /*|< Draw 'on' pixels*/); // Draw 'inverse' text
    display.println("OUT OF SERVICE :(");
    display.display();

    FastLED.addLeds<NEOPIXEL, 7>(leds, 47);

    fill_solid(leds, 47, CRGB::CRGB(167, 75, 208));
    FastLED.show();

    Serial.begin(9600);

}

void loop(){

}
