#include "m3_neowasm.h"

#include <m3_api_defs.h>
#include <m3_env.h>

#include <Arduino.h>

m3ApiRawFunction(m3_neowasm_millis)
{
  m3ApiReturnType(uint32_t);
  m3ApiReturn(millis());
}

m3ApiRawFunction(m3_neowasm_delay)
{
  m3ApiGetArg(uint32_t, ms);

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
  m3_LinkRawFunction(module, neowasm, "print", "v(*i)", &m3_arduino_print);

  // Dummy (for TinyGo)
  m3_LinkRawFunction(module, "env", "io_get_stdout", "i()", &m3_dummy);

  return m3Err_none;
}

