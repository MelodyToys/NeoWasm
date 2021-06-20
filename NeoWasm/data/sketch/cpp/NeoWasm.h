#ifndef neowasm_api_h
#define neowasm_api_h

#include <stdint.h>

#define WASM_EXPORT                   extern "C" __attribute__((used)) __attribute__((visibility ("default")))
#define WASM_EXPORT_AS(NAME)          WASM_EXPORT __attribute__((export_name(NAME)))
#define WASM_IMPORT(MODULE,NAME)      __attribute__((import_module(MODULE))) __attribute__((import_name(NAME)))
#define WASM_CONSTRUCTOR              __attribute__((constructor))

extern "C" {
	
WASM_IMPORT("neowasm", "millis")          uint32_t millis          (void);
WASM_IMPORT("neowasm", "delay")           void delay               (uint32_t ms);
WASM_IMPORT("neowasm", "print")           void print               (const char* s, size_t len);
WASM_IMPORT("neowasm", "show")            void show                (void);
WASM_IMPORT("neowasm", "clear")           void clear               (void);
WASM_IMPORT("neowasm", "setPixelColor")   void setPixelColor       (uint16_t n, uint8_t r, uint8_t g, uint8_t b);
WASM_IMPORT("neowasm", "setPixelColor32") void setPixelColor32     (uint16_t n, uint32_t c);
WASM_IMPORT("neowasm", "gamma32")         uint32_t gamma32         (uint32_t x);
WASM_IMPORT("neowasm", "ColorHSV")        uint32_t ColorHSV        (uint16_t hue, uint8_t sat=255, uint8_t val=255);
WASM_IMPORT("neowasm", "wheel")           uint32_t wheel           (uint8_t Pos);
WASM_IMPORT("neowasm", "wheelR")          uint8_t wheelR           (uint8_t Pos);
WASM_IMPORT("neowasm", "wheelG")          uint8_t wheelG           (uint8_t Pos);
WASM_IMPORT("neowasm", "wheelB")          uint8_t wheelB           (uint8_t Pos);
WASM_IMPORT("neowasm", "numPixels")       uint16_t numPixels       (void);
WASM_IMPORT("neowasm", "Color")           uint32_t Color           (uint8_t r, uint8_t g, uint8_t b);

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

WASM_EXPORT
void setup();
WASM_EXPORT
void loop();

WASM_EXPORT
void _start() {}

} // extern "C"

#endif // neowasm_api_h
