// NeoWasm Demo ~ sfranzyshen
// strandtest_wheel.cpp

#include "neowasm_api.h"

// colorWipe()
void colorWipe(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  uint16_t i = 0;
  
  while(i < numPixels()) {
    setPixelColor(i, r, g, b);
    show();
    delay(wait);
	i++;
  }
}

// theaterChase()
void theaterChase(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
  uint8_t j = 0, q;
  uint16_t i = 0;
  
  while(j < 10) {  //do 10 cycles of chasing
    q = 0;
    while(q < 3) {
	  i = 0;
      while(i < numPixels()) {
        setPixelColor(i + q, r, g, b);    //turn every third pixel on
		i = i + 3;
      }
      show();
      delay(wait);
	  i = 0;
      while(i < numPixels()) {
        setPixelColor(i + q, 0, 0, 0);        //turn every third pixel off
		i = i + 3;
      }
	  q++;
    }
	j++;
  }
}

// rainbow()
void rainbow(uint8_t wait) {
  uint16_t j = 0, i;
  uint8_t p;
  
  while(j < 256) {
	i = 0;
    while(i < numPixels()) {
	  p = (i + j) & 255;
      setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
	  i++;
    }
    show();
    delay(wait);
	j++;
  }
}

// rainbowCycle()
void rainbowCycle(uint8_t wait) {
  uint16_t j = 0, i;
  uint8_t p;
  
  while(j < 256 * 5) { // 5 cycles of all colors on wheel
    i = 0;
    while(i < numPixels()) {
      p = ((i * 256 / numPixels()) + j) & 255;
      setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
	  i++;
    }
    show();
    delay(wait);
	j++;
  }
}

// theaterChaseRainbow()
void theaterChaseRainbow(uint8_t wait) {
  uint8_t j = 0, q, p;
  uint16_t i;
  
  while(j < 256) {     // cycle all 256 colors in the wheel
    q = 0;
    while(q < 3) {
	  i = 0;
      while(i < numPixels()) {
		p = (i + j) % 255;
        setPixelColor(i + q, WheelR(p), WheelG(p), WheelB(p));    //turn every third pixel on
		i = i + 3;
      }
      show();
      delay(wait);
	  i = 0;
      while(i < numPixels()) {
        setPixelColor(i + q, 0, 0, 0);        //turn every third pixel off
		i = i + 3;
      }
	  q++;
    }
	j++;
  }
}

// setup()
void setup() {
  println("\nstrandtest_wheel ... start");
}

// loop()
void loop() {
  colorWipe(255, 0, 0, 50); // Red
  colorWipe(0, 255, 0, 50); // Green
  colorWipe(0, 0, 255, 50); // Blue

  theaterChase(127, 127, 127, 50); // White
  theaterChase(127, 0, 0, 50); // Red
  theaterChase(0, 0, 127, 50); // Blue

  rainbow(20);
  rainbowCycle(20);
  theaterChaseRainbow(50);
  println("strandtest_wheel ... loop");
}
