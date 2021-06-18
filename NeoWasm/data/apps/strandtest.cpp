// NeoWasm Demo ~ sfranzyshen
// strandtest.cpp

#include "neowasm_api.h"

// colorWipe()
void colorWipe(uint32_t color, uint8_t wait) {
  uint8_t i = 0;
  
  while(i < numPixels()) {
    setPixelColor32(i, color);
    show();
    delay(wait);
	i++;
  }
}

// theaterChase()
void theaterChase(uint32_t color, uint8_t wait) {
  uint8_t a = 0, b, c;
  
  while(a < 10) {
	b = 0;
    while(b < 3) {
      clear();
	  c = b;
      while(c < numPixels()) {
        setPixelColor32(c, color);
		c += 3;
      }
      show();
      delay(wait);
	  b++;
    }
	a++;
  }
}

// rainbow()
void rainbow(uint8_t wait) {
  long firstPixelHue = 0;
  uint8_t i, pixelHue;
  
  while(firstPixelHue < 5 * 65536) {
	i = 0;
    while(i < numPixels()) {
      pixelHue = firstPixelHue + (i * 65536L / numPixels());
      setPixelColor32(i, gamma32(ColorHSV(pixelHue)));
	  i++;
    }
    show();
    delay(wait);
	firstPixelHue += 256;
  }
}

// theaterChaseRainbow()
void theaterChaseRainbow(uint8_t wait) {
  uint8_t firstPixelHue = 0;
  uint8_t a = 0, b, c, hue;
  uint32_t color;
  
  while(a < 30) {
	b = 0;
    while(b < 3) {
      clear();
	  c = b;
      while(c < numPixels()) {
        hue = firstPixelHue + c * 65536L / numPixels();
        color = gamma32(ColorHSV(hue));
        setPixelColor32(c, color);
		c += 3;
      }
      show();
      delay(wait);
      firstPixelHue += 65536 / 90;
	  b++;
    }
	a++;
  }
}

// setup()
void setup() {
  println("\nstrandtest ... start");
}

// loop()
void loop() {
  colorWipe(Color(255, 0, 0), 50); // Red
  colorWipe(Color(0, 255, 0), 50); // Green
  colorWipe(Color(0, 0, 255), 50); // Blue

  theaterChase(Color(127, 127, 127), 50); // White
  theaterChase(Color(127, 0, 0), 50); // Red
  theaterChase(Color( 0, 0, 127), 50); // Blue

  rainbow(10);
  theaterChaseRainbow(50);
  println("strandtest ... loop");
}

