#include <LiquidCrystal.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel stripBouton = Adafruit_NeoPixel(4, 52, NEO_GRB + NEO_KHZ800);

void setPixel(int Pixel, byte red, byte green, byte blue) {
 #ifdef ADAFRUIT_NEOPIXEL_H 
   // NeoPixel
   stripBouton.setPixelColor(Pixel, stripBouton.Color(red, green, blue));

 #endif
 #ifndef ADAFRUIT_NEOPIXEL_H 
   // FastLED
   leds[Pixel].r = red;
   leds[Pixel].g = green;
   leds[Pixel].b = blue;
 #endif
}



void setup() {
  // put your setup code here, to run once:
  stripBouton.begin();
setPixel(0, 223, 0, 0);
stripBouton.show();
}

void loop() {
  // put your main code here, to run repeatedly:
setPixel(0, 223, 0, 0);
stripBouton.show();
}
