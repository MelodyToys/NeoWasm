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

// setup()
void setup() {
	println("\nstrandtest ... start");
}

// loop()
void loop() {
	colorWipe(Color(255, 0, 0), 50); // Red
	colorWipe(Color(0, 255, 0), 50); // Green
	colorWipe(Color(0, 0, 255), 50); // Blue
	println("strandtest ... loop");
}

