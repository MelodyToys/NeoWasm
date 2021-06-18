# Compile
wasicc  -Os                                                   \
        -z stack-size=4096 -Wl,--initial-memory=65536         \
        -Wl,--allow-undefined-file=neowasm_api.syms           \
        -Wl,--strip-all -nostdlib                             \
        -o app.wasm app.cpp

# Optimize (optional)
wasm-opt -O3 app.wasm -o app.wasm
wasm-strip app.wasm

# Convert to WAT
#wasm2wat --generate-names app.wasm -o app.wat

# Convert to C header
# xxd -i app.wasm > app.wasm.h

# Copy wasm to ROM filesystem
# cp app.wasm ../../../wasms/strandtest.wasm