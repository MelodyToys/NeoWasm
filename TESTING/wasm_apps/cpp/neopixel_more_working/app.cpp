#include "arduino_api.h"

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

/*
// rainbow32()
void rainbow32(uint8_t wait) {
	long firstPixelHue = 0;
	uint8_t i, pixelHue;
	while(firstPixelHue < 5 * 65536) {
		i = 0;
		while(i < numPixels()) {
			pixelHue = firstPixelHue + (i * 65536L / numPixels());
			setPixelColor32(i, gamma32(ColorHSV(pixelHue, 255, 255)));
			i++;
		}
		show();
		delay(wait);
		firstPixelHue += 256;
	}
}

// rainbow32()
void rainbow32(uint8_t wait) {
	uint16_t j = 0, i;
	uint8_t p;
	while(j <= 255) {
		i = 0;
		while(i < numPixels()) {
			p = (i + j) & 255;
			setPixelColor32(i, Wheel(p));
			i++;
		}
		show();
		delay(wait);
		j++;
	}
}
*/

// rainbow32()
void rainbow32(uint8_t wait) {
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

// rainbow()
void rainbow(uint8_t wait) {
	uint16_t j = 0, i;
	uint8_t p;
	while(j <= 255) {
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

// setup()
void setup() {
	println("\nstrandtest ... start");
}

// loop()
void loop() {
	colorWipe(Color(255, 0, 0), 50); // Red
	colorWipe(Color(0, 255, 0), 50); // Green
	colorWipe(Color(0, 0, 255), 50); // Blue
	rainbow(20);
	rainbow32(20);
	
	println("strandtest ... loop");
}

