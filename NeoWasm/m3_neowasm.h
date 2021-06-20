#ifndef m3_neowasm_h
#define m3_neowasm_h

#include <m3_core.h>

#if defined(__cplusplus)
extern "C"
{
#endif

  M3Result m3_LinkArduino(IM3Runtime runtime);
  size_t m3_readWasmSize(const char *path);
  size_t m3_readWasm(const char *path, uint8_t *buf);
  
#if defined(__cplusplus)
}
#endif

#endif // m3_neowasm_h