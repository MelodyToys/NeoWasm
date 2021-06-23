// NeoWasm Demo ~ sfranzyshen
// strandtest_nodelay.cpp

#include "NeoWasm.h"

unsigned long	patternPrevious;	// Previous Pattern Millis
int 			patternCurrent;		// Current Pattern Number
int 			patternInterval;	// Pattern Interval (ms)
unsigned long	pixelPrevious;		// Previous Pixel Millis
int 			pixelInterval;		// Pixel Interval (ms)
int 			pixelQueue;			// Pixel Queue
int 			pixelCycle;			// Pixel Cycle
uint16_t		pixelCurrent;		// Current Pixel Number
uint16_t		pixelNumber;		// Number of Pixels

// colorWipe()
void colorWipe(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
	if(pixelInterval != wait) pixelInterval = wait;
	setPixelColor(pixelCurrent, r, g, b);
	show();
	pixelCurrent++;
	if(pixelCurrent >= pixelNumber) {
		pixelCurrent = 0;
		clear();
	}
}

// rainbow()
void rainbow(uint8_t wait) {
	if(pixelInterval != wait) pixelInterval = wait;
	uint16_t i = 0;
	int p = 0;
	while(i < pixelNumber) {
		p = (i + pixelCycle) & 255;
		setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
		i++;
	}
	show();
	pixelCycle++;
	if(pixelCycle >= 255) pixelCycle = 0;
}

// rainbowCycle()
void rainbowCycle(uint8_t wait) {
	if(pixelInterval != wait) pixelInterval = wait;
	uint16_t i = 0;
	int p = 0;
	while( i < pixelNumber) {
		p = ((i * 255 / pixelNumber) + pixelCycle) & 255;
		setPixelColor(i, WheelR(p), WheelG(p), WheelB(p));
		i++;
	}
	show();
	pixelCycle++;
	if(pixelCycle >= 255 * 5) pixelCycle = 0;
}

// theaterChase()
void theaterChase(uint8_t r, uint8_t g, uint8_t b, uint8_t wait) {
	if(pixelInterval != wait) pixelInterval = wait;
	int i = 0;
	while(i < pixelNumber) {
		setPixelColor(i + pixelQueue, r, g, b);
		i = i + 3;
	}
	show();
	i = 0;
	while(i < pixelNumber) {
		setPixelColor(i + pixelQueue, 0, 0, 0);
		i = i + 3;
	}
	pixelQueue++;
	if(pixelQueue >= 3) pixelQueue = 0;
}

// theaterChaseRainbow()
void theaterChaseRainbow(uint8_t wait) {
	if(pixelInterval != wait) pixelInterval = wait;
	int i = 0;
	int p = 0;
	while(i < pixelNumber) {
		p = (i + pixelCycle) % 255;
		setPixelColor(i + pixelQueue, WheelR(p), WheelG(p), WheelB(p));
		i = i + 3;
	}
	show();
	i = 0;
	while( i < pixelNumber) {
		setPixelColor(i + pixelQueue, 0, 0, 0);
		i = i + 3;
	}      
	pixelQueue++;
	pixelCycle++;
	if(pixelQueue >= 3) pixelQueue = 0;
	if(pixelCycle >= 255) pixelCycle = 0;
}

// setup()
void setup() {
	patternPrevious	= 0;	       // Previous Pattern Millis
	patternCurrent	= 0;		   // Current Pattern Number
	patternInterval	= 5500;	       // Pattern Interval (ms)
	pixelPrevious	= 0;		   // Previous Pixel Millis
	pixelInterval	= 50;		   // Pixel Interval (ms)
	pixelQueue		= 0;		   // Pixel Queue
	pixelCycle		= 0;		   // Pixel Cycle
	pixelCurrent	= 0;		   // Current Pixel Number
	pixelNumber		= numPixels(); // Number of Pixels	
	
	println("\nstrandtest_nodelay ... start");
}

// loop()
void loop() {
	unsigned long currentMillis = millis();
	if((currentMillis - patternPrevious) >= patternInterval) {
		patternPrevious = currentMillis ;
		patternCurrent++;
		if(patternCurrent >= 8) {
			patternCurrent = 0;
			println("strandtest_nodelay ... loop");
		}
	}  
	if(currentMillis - pixelPrevious >= pixelInterval) {
		pixelPrevious = currentMillis;
		if(patternCurrent == 8) theaterChaseRainbow(50);
		else if(patternCurrent == 7) rainbowCycle(20);
		else if(patternCurrent == 6) rainbow(20);
		else if(patternCurrent == 5) theaterChase(0, 0, 127, 50);     // Blue
		else if(patternCurrent == 4) theaterChase(127, 0, 0, 50);     // Red
		else if(patternCurrent == 3) theaterChase(127, 127, 127, 50); // White
		else if(patternCurrent == 2) colorWipe(0, 0, 255, 50);        // Blue
		else if(patternCurrent == 1) colorWipe(0, 255, 0, 50);        // Green
		else if(patternCurrent == 0) colorWipe(255, 0, 0, 50);        // Red
	}    
}
