#include <wasm3.h>
#include <m3_env.h>
#include <FS.h>

#define FATAL(func, msg) { Serial.print("Fatal: " func " "); Serial.println(msg); return; }

#define WASM_STACK_SLOTS    4096
#define NATIVE_STACK_SIZE   (32*1024)

// For (most) devices that cannot allocate a 64KiB wasm page
#define WASM_MEMORY_LIMIT   4096

//#include "app.wasm.h"

IM3Environment  m3_env;
IM3Runtime      m3_runtime;
IM3Module       m3_module;
IM3Function     m3_setup;
IM3Function     m3_loop;
bool            m3_init = false;

m3ApiRawFunction(m3_arduino_millis) {
    m3ApiReturnType (uint32_t)

    m3ApiReturn(millis());
}

/*
m3ApiRawFunction(m3_arduino_delay) {
    m3ApiGetArg     (uint32_t, ms)

    //Serial.print("api: delay "); Serial.println(ms);
    delay(ms);
    m3ApiSuccess();
}
*/

m3ApiRawFunction(m3_arduino_delay) {
  m3ApiGetArg   (uint32_t, milli)

  unsigned long targetMillis = millis() + milli;
  unsigned long currentMillis = millis();
  
  while(currentMillis < targetMillis) {
    yield();
    currentMillis = millis();
  }
  m3ApiSuccess();
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
    m3_LinkRawFunction (module, arduino, "print",            "v(*i)",  &m3_arduino_print);

    return m3Err_none;
}

size_t readWasmFileSize(const char *path) {
  //Serial.printf("Reading file: %s\n", path);

  if (!SPIFFS.exists(path))
  {
    Serial.println("File not found");
    return 0;
  }

  File file = SPIFFS.open(path, "r");
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return 0;
  }
  size_t size = file.size();
  file.close();
  return size;
}

size_t readWasmFile(const char *path, uint8_t *buf)
{
  Serial.printf("Reading file: %s\n", path);

  if (!SPIFFS.exists(path))
  {
    Serial.println("File not found");
    return 0;
  }

  File file = SPIFFS.open(path, "r");
  if (!file)
  {
    Serial.println("Failed to open file for reading");
    return 0;
  }

  Serial.print("Read from file: ");
  Serial.println(path);
  size_t i = 0;
  while (file.available())
  {
    buf[i] = file.read();
    i++;
  }
  file.close();

  return i;
}

void wasm_loop() {
   if(m3_init) {
      M3Result result = m3_CallV (m3_loop);
      if (result) {
          m3_init = false;
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

    size_t app_wasm_size = readWasmFileSize("/app.wasm");
    if (app_wasm_size == 0)
      FATAL("ReadWasm", "File not found")

    uint8_t * buf = new uint8_t[app_wasm_size];
//    uint8_t buf[app_wasm_size];
    size_t read_bytes = readWasmFile("/app.wasm", buf);
    if (read_bytes == 0)
      FATAL("ReadWasm", "File not found")

/*
    if (buf) {
      memcpy_P(buf, app_wasm, app_wasm_len);
      //Serial.write(buf, app_wasm_len); // dump the buffer.
    }
*/
    Serial.print("Free Heap: "); Serial.println(ESP.getFreeHeap(),DEC);

    result = m3_ParseModule (m3_env, &m3_module, buf, app_wasm_size);
    if (result) FATAL("ParseModule", result);

    //delete[] buf;
    delete buf;

    Serial.print("Free Heap: "); Serial.println(ESP.getFreeHeap(),DEC);

    result = m3_LoadModule (m3_runtime, m3_module);
    if (result) FATAL("LoadModule", result);

    Serial.print("Free Heap: "); Serial.println(ESP.getFreeHeap(),DEC);

    result = LinkArduino (m3_runtime);
    if (result) FATAL("LinkArduino", result);

    result = m3_FindFunction (&m3_setup, m3_runtime, "setup");
    if (result) FATAL("FindFunction setup() ", result);

    result = m3_FindFunction (&m3_loop, m3_runtime, "loop");
    if (result) {
      FATAL("FindFunction loop()", result);
    } else {
      Serial.println("WebAssembly VM Running ...");
      m3_init = true;
    }

    result = m3_CallV (m3_setup);
    if (result) {
        m3_init = false;
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
    Serial.print("Free Heap: "); Serial.println(ESP.getFreeHeap(),DEC);
    SPIFFS.begin();
    wasm_init();
    Serial.print("Free Heap: "); Serial.println(ESP.getFreeHeap(),DEC);
}

void loop() {
    wasm_loop();
    yield();
}
