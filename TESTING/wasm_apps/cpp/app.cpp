#include "arduino_api.h"

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


// colorWipe32()
void colorWipe32(uint32_t color, uint8_t wait) {
	uint8_t i = 0;
	while(i < numPixels()) {
		setPixelColor32(i, color);
		show();
		delay(wait);
		i++;
	}
}


// theaterChase32()
void theaterChase32(uint32_t color, uint8_t wait) {
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
*/

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

/*
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



// theaterChaseRainbow32()
void theaterChaseRainbow32(uint8_t wait) {
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
*/
// setup()
void setup() {
	println("\nstrandtest ... start");
}

// loop()
void loop() {
	println("colorWipe ... ");
	colorWipe(255, 0, 0, 50); // Red
	colorWipe(0, 255, 0, 50); // Green
	colorWipe(0, 0, 255, 50); // Blue

	println("colorWipe32 ... ");
	colorWipe32(Color(255, 0, 0), 50); // Red
	colorWipe32(Color(0, 255, 0), 50); // Green
	colorWipe32(Color(0, 0, 255), 50); // Blue

	println("theaterChase ... ");
	theaterChase(127, 127, 127, 50); // White
	theaterChase(127, 0, 0, 50); // Red
	theaterChase(0, 0, 127, 50); // Blue
	
	println("theaterChase32 ... ");
	theaterChase32(Color(127, 127, 127), 50); // White
	theaterChase32(Color(127, 0, 0), 50);     // Red
	theaterChase32(Color( 0, 0, 127), 50);    // Blue

//	println("theaterChaseRainbow ... ");
//	theaterChaseRainbow(50);
//	println("theaterChaseRainbow32 ... ");
//	theaterChaseRainbow32(50);

	println("rainbow ... ");
	rainbow(20);
//	println("rainbow32 ... ");
//	rainbow32(20);
	
	println("strandtest ... loop");
}

