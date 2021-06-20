#include "m3_neowasm.h"

#include <m3_api_defs.h>
#include <m3_env.h>

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <FS.h>
#include <SPIFFS.h>

m3ApiRawFunction(m3_neowasm_millis)
{
  m3ApiReturnType(uint32_t)
  m3ApiReturn(millis());
}

m3ApiRawFunction(m3_neowasm_delay)
{
  m3ApiGetArg(uint32_t, ms)

  delay(ms);

  m3ApiSuccess();
}

m3ApiRawFunction(m3_neowasm_print)
{
    m3ApiGetArgMem  (const uint8_t *, buf)
    m3ApiGetArg     (uint32_t,        len)

    //printf("api: print %p %d\n", buf, len);
    Serial.write(buf, len);

    m3ApiSuccess();
}
m3ApiRawFunction(m3_neowasm_numPixels) {
    m3ApiReturnType (uint16_t)
	
    m3ApiReturn(strip.numPixels());
}

m3ApiRawFunction(m3_neowasm_clear) {
    strip.clear();
    m3ApiSuccess();
}

m3ApiRawFunction(m3_neowasm_show) {
    strip.show();
    delay(0);
    m3ApiSuccess();
}

m3ApiRawFunction(m3_neowasm_gamma32) {
    m3ApiReturnType (uint32_t)
    m3ApiGetArg     (uint32_t, color)
	
    m3ApiReturn(strip.gamma32(color));
}

m3ApiRawFunction(m3_neowasm_setPixelColor)
{
  m3ApiGetArg     (uint16_t, n)
  m3ApiGetArg     (uint8_t, r)
  m3ApiGetArg     (uint8_t, g)
  m3ApiGetArg     (uint8_t, b)

  strip.setPixelColor(n, r, g, b);

  m3ApiSuccess();
}

m3ApiRawFunction(m3_neowasm_setPixelColor32)
{
  m3ApiGetArg     (uint16_t, n)
  m3ApiGetArg     (uint32_t, c)

  strip.setPixelColor(n, c);

  m3ApiSuccess();
}

m3ApiRawFunction(m3_neowasm_ColorHSV) {
    m3ApiReturnType (uint32_t)
    m3ApiGetArg     (uint16_t, hue)
	m3ApiGetArg     (uint8_t, sat)
	m3ApiGetArg     (uint8_t, val)	
	
    m3ApiReturn(strip.ColorHSV(hue, sat, val));
}

m3ApiRawFunction(m3_neowasm_Color) {
    m3ApiReturnType (uint32_t)
    m3ApiGetArg     (uint8_t, r)
	m3ApiGetArg     (uint8_t, g)
	m3ApiGetArg     (uint8_t, b)	
	
    m3ApiReturn(strip.Color(r, g, b));
}

m3ApiRawFunction(m3_neowasm_wheel) {
    m3ApiReturnType (uint32_t)
    m3ApiGetArg     (uint8_t, pos)
	
    m3ApiReturn(wheel(pos));
}

m3ApiRawFunction(m3_neowasm_wheelR) {
    m3ApiReturnType (uint8_t)
    m3ApiGetArg     (uint8_t, pos)
	
    m3ApiReturn(wheelR(pos));
}

m3ApiRawFunction(m3_neowasm_wheelG) {
    m3ApiReturnType (uint8_t)
    m3ApiGetArg     (uint8_t, pos)
	
    m3ApiReturn(wheelR(pos));
}

m3ApiRawFunction(m3_neowasm_wheelB) {
    m3ApiReturnType (uint8_t)
    m3ApiGetArg     (uint8_t, pos)
	
    m3ApiReturn(wheelR(pos));
}

// Dummy, for TinyGO
m3ApiRawFunction(m3_dummy)
{
  m3ApiSuccess();
}

M3Result m3_LinkArduino(IM3Runtime runtime)
{
  IM3Module module = runtime->modules;
  const char *neowasm = "neowasm";

  m3_LinkRawFunction(module, neowasm, "millis", "i()", &m3_neowasm_millis);
  m3_LinkRawFunction(module, neowasm, "delay", "v(i)", &m3_neowasm_delay);
  m3_LinkRawFunction(module, neowasm, "print", "v(*i)", &m3_neowasm_print);
  m3_LinkRawFunction(module, neowasm, "show", "v()", &m3_neowasm_show);
  m3_LinkRawFunction(module, neowasm, "clear", "v()", &m3_neowasm_clear);
  m3_LinkRawFunction(module, neowasm, "setPixelColor", "v(iiii)", &m3_neowasm_setPixelColor);
  m3_LinkRawFunction(module, neowasm, "setPixelColor32", "v(ii)", &m3_neowasm_setPixelColor32);
  m3_LinkRawFunction(module, neowasm, "gamma32", "i(i)", &m3_neowasm_gamma32);
  m3_LinkRawFunction(module, neowasm, "ColorHSV", "i(iii)", &m3_neowasm_ColorHSV);
  m3_LinkRawFunction(module, neowasm, "wheel", "i(i)", &m3_neowasm_wheel);
  m3_LinkRawFunction(module, neowasm, "wheelR", "i(i)", &m3_neowasm_wheelR);
  m3_LinkRawFunction(module, neowasm, "wheelG", "i(i)", &m3_neowasm_wheelG);
  m3_LinkRawFunction(module, neowasm, "wheelB", "i(i)", &m3_neowasm_wheelB);
  m3_LinkRawFunction(module, neowasm, "numPixels", "i()", &m3_neowasm_numPixels);
  m3_LinkRawFunction(module, neowasm, "Color", "i(iii)", &m3_neowasm_Color);
  
  // Dummy (for TinyGo)
  m3_LinkRawFunction(module, "env", "io_get_stdout", "i()", &m3_dummy);

  return m3Err_none;
}

size_t m3_readWasmSize(const char *path) {
	Serial.printf("Reading file: %s\n", path);

	if(!SPIFFS.exists(path)) {
		Serial.println("File not found");
		return 0;
	}

	File file = SPIFFS.open(path);
	if(!file) {
		Serial.println("Failed to open file for reading");
		return 0;
	}
	size_t size = file.size();
	file.close();
	return size;
}

size_t m3_readWasm(const char *path, uint8_t *buf) {
	Serial.printf("Reading file: %s\n", path);

	if(!SPIFFS.exists(path)) {
		Serial.println("File not found");
		return 0;
	}

	File file = SPIFFS.open(path);
	if(!file) {
		Serial.println("Failed to open file for reading");
		return 0;
	}

	Serial.println("Read from file: ");
	size_t i = 0;
	while(file.available()) {
		buf[i] = file.read();
		i++;
	}

	file.close();
	return i;
}

