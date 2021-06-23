// NeoWasm Demo ~ sfranzyshen
// strandtest.cpp

#include "NeoWasm.h"

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
	uint16_t i = 0;
	uint8_t p = 0;
	uint8_t	c = 0;
	
	while(i < numPixels()) {
		p = (i + c) & 255;
		setPixelColor32(i, Wheel(p));
		i++;
	}
	show();
	delay(wait);
	c++;
	if(c > 255) c = 0;
}

// theaterChaseRainbow()
void theaterChaseRainbow(uint8_t wait) {
	uint8_t j = 0, q, p;
	uint16_t i;
	while(j <= 255) {     // cycle all 256 colors in the wheel
		q = 0;
		while(q < 3) {
			i = 0;
			while(i < numPixels()) {
				p = (i + j) % 255;
				setPixelColor32(i + q, Wheel(p));    //turn every third pixel on
				i = i + 3;
			}
			show();
			delay(wait);
			i = 0;
			while(i < numPixels()) {
				setPixelColor32(i + q, Color(0, 0, 0));        //turn every third pixel off
				i = i + 3;
			}
			q++;
		}
		j++;
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

