/*
 * Wasm3 - high performance WebAssembly interpreter written in C.
 * Copyright © 2020 Volodymyr Shymanskyy, Steven Massey.
 * All rights reserved.
 */

#include <wasm3.h>

#include <m3_env.h>

/*
 * Configuration
 */

// Redefine the default LED pin here, if needed
#ifndef LED_PIN
#define LED_PIN             LED_BUILTIN
#endif

#define WASM_STACK_SLOTS    2048
#define NATIVE_STACK_SIZE   (32*1024)

// For (most) devices that cannot allocate a 64KiB wasm page
#define WASM_MEMORY_LIMIT   4096

/*
 * WebAssembly app
 */

//#include "../wasm_apps/assemblyscript/app.wasm.h"
//#include "../wasm_apps/rust/app.wasm.h"
//#include "../wasm_apps/tinygo/app.wasm.h"
#include "app.wasm.h"

/*
 * API bindings
 *
 * Note: each RawFunction should complete with one of these calls:
 *   m3ApiReturn(val)   - Returns a value
 *   m3ApiSuccess()     - Returns void (and no traps)
 *   m3ApiTrap(trap)    - Returns a trap
 */

m3ApiRawFunction(m3_arduino_millis) {
    m3ApiReturnType (uint32_t)

    m3ApiReturn(millis());
}

m3ApiRawFunction(m3_arduino_delay) {
    m3ApiGetArg     (uint32_t, ms)

    // You can also trace API calls
    //Serial.print("api: delay "); Serial.println(ms);

    delay(ms);

    m3ApiSuccess();
}

// This maps pin modes from arduino_wasm_api.h
// to actual platform-specific values
uint8_t mapPinMode(uint8_t mode) {
    switch(mode) {
    case 0: return INPUT;
    case 1: return OUTPUT;
    case 2: return INPUT_PULLUP;
    }
    return INPUT;
}

m3ApiRawFunction(m3_arduino_pinMode) {
    m3ApiGetArg     (uint8_t, pin)
    m3ApiGetArg     (uint8_t, mode)

#if !defined(PARTICLE)
    typedef uint8_t PinMode;
#endif
    pinMode(pin, (PinMode)mapPinMode(mode));

    m3ApiSuccess();
}

m3ApiRawFunction(m3_arduino_digitalWrite) {
    m3ApiGetArg     (uint8_t, pin)
    m3ApiGetArg     (uint8_t, value)

    digitalWrite(pin, value);

    m3ApiSuccess();
}

m3ApiRawFunction(m3_arduino_getPinLED) {
    m3ApiReturnType (uint8_t)

    m3ApiReturn(LED_PIN);
}

m3ApiRawFunction(m3_arduino_print) {
    m3ApiGetArgMem  (const uint8_t *, buf)
    m3ApiGetArg     (uint8_t,        len)

    //printf("api: print %p %d\n", buf, len);
    Serial.write(buf, len);

    m3ApiSuccess();
}

M3Result  LinkArduino  (IM3Runtime runtime) {
    IM3Module module = runtime->modules;
    const char* arduino = "arduino";

    m3_LinkRawFunction (module, arduino, "millis",           "i()",    &m3_arduino_millis);
    m3_LinkRawFunction (module, arduino, "delay",            "v(i)",   &m3_arduino_delay);
    m3_LinkRawFunction (module, arduino, "pinMode",          "v(ii)",  &m3_arduino_pinMode);
    m3_LinkRawFunction (module, arduino, "digitalWrite",     "v(ii)",  &m3_arduino_digitalWrite);

    // Test functions
    m3_LinkRawFunction (module, arduino, "getPinLED",        "i()",    &m3_arduino_getPinLED);
    m3_LinkRawFunction (module, arduino, "print",            "v(*i)",  &m3_arduino_print);

    return m3Err_none;
}

IM3Environment m3_env;
IM3Runtime m3_runtime;
IM3Module m3_module;
IM3Function m3_setup;
IM3Function m3_loop;
bool vm_init = false;

#define FATAL(func, msg) { Serial.print("Fatal: " func " "); Serial.println(msg); return; }

void wasm_loop() {
   if(vm_init) {
      M3Result result = m3_CallV (m3_loop);
      if (result) {
          vm_init = false;
          M3ErrorInfo info;
          m3_GetErrorInfo (m3_runtime, &info);
          Serial.print("Error: ");
          Serial.print(result);
          Serial.print(" (");
          Serial.print(info.message);
          Serial.println(")");
          if (info.file && strlen(info.file) && info.line) {
             Serial.print("At ");
             Serial.print(info.file);
             Serial.print(":");
             Serial.println(info.line);
          }
      }
   }
}

void wasm_init() {
    M3Result result = m3Err_none;

    m3_env = m3_NewEnvironment ();
    if (!m3_env) FATAL("NewEnvironment", "failed");

    m3_runtime = m3_NewRuntime (m3_env, WASM_STACK_SLOTS, NULL);
    if (!m3_runtime) FATAL("NewRuntime", "failed");

#ifdef WASM_MEMORY_LIMIT
    m3_runtime->memoryLimit = WASM_MEMORY_LIMIT;
#endif

    result = m3_ParseModule (m3_env, &m3_module, app_wasm, app_wasm_len);
    if (result) FATAL("ParseModule", result);

    result = m3_LoadModule (m3_runtime, m3_module);
    if (result) FATAL("LoadModule", result);

    result = LinkArduino (m3_runtime);
    if (result) FATAL("LinkArduino", result);

    result = m3_FindFunction (&m3_setup, m3_runtime, "setup");
    if (result) FATAL("FindFunction", result);

    result = m3_FindFunction (&m3_loop, m3_runtime, "loop");
    if (result) {
      FATAL("FindFunction", result);
    } else {
      Serial.println("WebAssembly VM Running ...");
      vm_init = true;
    }

    result = m3_CallV (m3_setup);
    if (result) {
        vm_init = false;
        M3ErrorInfo info;
        m3_GetErrorInfo (m3_runtime, &info);
        Serial.print("Error: ");
        Serial.print(result);
        Serial.print(" (");
        Serial.print(info.message);
        Serial.println(")");
        if (info.file && strlen(info.file) && info.line) {
            Serial.print("At ");
            Serial.print(info.file);
            Serial.print(":");
            Serial.println(info.line);
        }
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("\nWasm3 v" M3_VERSION " (" M3_ARCH "), build " __DATE__ " " __TIME__);

    wasm_init();
}

void loop() {
    wasm_loop();
    yield();
}
