#ifndef arduino_wasm_api_h
#define arduino_wasm_api_h

#include <stdint.h>

#define WASM_EXPORT                   extern "C" __attribute__((used)) __attribute__((visibility ("default")))
#define WASM_EXPORT_AS(NAME)          WASM_EXPORT __attribute__((export_name(NAME)))
#define WASM_IMPORT(MODULE,NAME)      __attribute__((import_module(MODULE))) __attribute__((import_name(NAME)))
#define WASM_CONSTRUCTOR              __attribute__((constructor))

extern "C" {

WASM_IMPORT("arduino", "millis")          uint32_t millis          (void);
WASM_IMPORT("arduino", "delay")           void delay               (uint32_t ms);
WASM_IMPORT("arduino", "print")           void print               (const char* s, size_t len);
WASM_IMPORT("arduino", "show")            void show                (void);
WASM_IMPORT("arduino", "clear")           void clear               (void);
WASM_IMPORT("arduino", "setPixelColor")   void setPixelColor       (uint16_t n, uint8_t r, uint8_t g, uint8_t b);
WASM_IMPORT("arduino", "setPixelColor32") void setPixelColor32     (uint16_t n, uint32_t c);
//WASM_IMPORT("arduino", "gamma32")         uint32_t gamma32         (uint32_t x);
//WASM_IMPORT("arduino", "ColorHSV")        uint32_t ColorHSV        (uint16_t hue, uint8_t sat=255, uint8_t val=255);
//WASM_IMPORT("arduino", "Wheel")           uint32_t Wheel           (uint8_t Pos);
//WASM_IMPORT("arduino", "WheelR")          uint8_t WheelR           (uint8_t Pos);
//WASM_IMPORT("arduino", "WheelG")          uint8_t WheelG           (uint8_t Pos);
//WASM_IMPORT("arduino", "WheelB")          uint8_t WheelB           (uint8_t Pos);
WASM_IMPORT("arduino", "numPixels")       uint16_t numPixels       (void);
WASM_IMPORT("arduino", "Color")           uint32_t Color           (uint8_t r, uint8_t g, uint8_t b);

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

WASM_EXPORT
void _start() {}
WASM_EXPORT
void setup();
WASM_EXPORT
void loop();

#endif // arduino_wasm_api_h
