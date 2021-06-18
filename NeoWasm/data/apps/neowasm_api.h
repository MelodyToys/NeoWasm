#ifndef neowasm_api_h
#define neowasm_api_h

#include <stdint.h>

#define WASM_EXPORT                   extern "C" __attribute__((used)) __attribute__((visibility ("default")))
#define WASM_EXPORT_AS(NAME)          WASM_EXPORT __attribute__((export_name(NAME)))
#define WASM_IMPORT(MODULE,NAME)      __attribute__((import_module(MODULE))) __attribute__((import_name(NAME)))
#define WASM_CONSTRUCTOR              __attribute__((constructor))

extern "C" {

WASM_IMPORT("neowasm", "millis") uint32_t millis (void);
WASM_IMPORT("neowasm", "delay") void delay (uint32_t ms);
WASM_IMPORT("neowasm", "print") void print (const char* s, size_t len);
WASM_IMPORT("neowasm", "show") void show (void);
WASM_IMPORT("neowasm", "clear") void show (void);
WASM_IMPORT("neowasm", "setPixelColor") void setPixelColor(uint16_t n, uint8_t r, uint8_t g, uint8_t b);
WASM_IMPORT("neowasm", "setPixelColor32") void setPixelColor(uint16_t n, uint32_t c);
WASM_IMPORT("neowasm", "gamma32") static uint32_t gamma32(uint32_t x);
WASM_IMPORT("neowasm", "ColorHSV") static uint32_t ColorHSV(uint16_t hue, uint8_t sat, uint8_t val);
WASM_IMPORT("neowasm", "Wheel") uint32_t Wheel(byte WheelPos);
WASM_IMPORT("neowasm", "WheelR") uint8_t WheelR(byte Pos);
WASM_IMPORT("neowasm", "WheelG") uint8_t WheelG(byte Pos);
WASM_IMPORT("neowasm", "WheelB") uint8_t WheelB(byte Pos);
WASM_IMPORT("neowasm", "numPixels") uint16_t numPixels(void);

static inline size_t strlen(const char *str) {
  const char *s;
  for (s = str; *s; ++s);
  return (s - str);
}

static inline void print (const char* s) {
  print(s, strlen(s));
}

static inline void println (const char* s) {
  print(s); print("\n");
}

}

#endif // neowasm_api_h
