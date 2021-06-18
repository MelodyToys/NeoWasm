# Compile strandtest
wasicc  -Os                                                   \
        -z stack-size=4096 -Wl,--initial-memory=65536         \
        -Wl,--allow-undefined-file=neowasm_api.syms           \
        -Wl,--strip-all -nostdlib                             \
        -o strandtest.wasm strandtest.cpp

# Compile strandtest_nodelay
wasicc  -Os                                                   \
        -z stack-size=4096 -Wl,--initial-memory=65536         \
        -Wl,--allow-undefined-file=neowasm_api.syms           \
        -Wl,--strip-all -nostdlib                             \
        -o strandtest_nodelay.wasm strandtest_nodelay.cpp
# Compile strandtest_wheel
wasicc  -Os                                                   \
        -z stack-size=4096 -Wl,--initial-memory=65536         \
        -Wl,--allow-undefined-file=neowasm_api.syms           \
        -Wl,--strip-all -nostdlib                             \
        -o strandtest_wheel.wasm strandtest_wheel.cpp

# Optimize (optional)
wasm-opt -O3 strandtest.wasm -o strandtest.wasm
wasm-strip strandtest.wasm
wasm-opt -O3 strandtest_nodelay.wasm -o strandtest_nodelay.wasm
wasm-strip strandtest_nodelay.wasm
wasm-opt -O3 strandtest_wheel.wasm -o strandtest_wheel.wasm
wasm-strip strandtest_wheel.wasm

# Convert to WAT
#wasm2wat --generate-names strandtest.wasm -o strandtest.wat
#wasm2wat --generate-names strandtest_nodelay.wasm -o strandtest_nodelay.wat
#wasm2wat --generate-names strandtest_wheel.wasm -o strandtest_wheel.wat

# Convert to C header
# xxd -i strandtest.wasm > strandtest.wasm.h
# xxd -i strandtest_nodelay.wasm > strandtest_nodelay.wasm.h
# xxd -i strandtest_wheel.wasm > strandtest_wheel.wasm.h

# Copy wasm to ROM filesystem
cp strandtest.wasm ../wasms/strandtest.wasm
cp strandtest_nodelay.wasm ../wasms/strandtest_nodelay.wasm
cp strandtest_wheel.wasm ../wasms/strandtest_wheel.wasm
