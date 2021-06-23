wasicc -v -Os -z stack-size=4096 -Wl,--initial-memory=65536 -Wl,--allow-undefined-file=NeoWasm.syms -Wl,--strip-all -nostdlib -o strandtest.wasm strandtest.cpp
wasicc -v -Os -z stack-size=4096 -Wl,--initial-memory=65536 -Wl,--allow-undefined-file=NeoWasm.syms -Wl,--strip-all -nostdlib -o strandtest_wheel.wasm strandtest_wheel.cpp
wasicc -v -Os -z stack-size=4096 -Wl,--initial-memory=65536 -Wl,--allow-undefined-file=NeoWasm.syms -Wl,--strip-all -nostdlib -o strandtest_nodelay.wasm strandtest_nodelay.cpp
wasm-opt -O3 strandtest.wasm -o strandtest.wasm
wasm-opt -O3 strandtest_wheel.wasm -o strandtest_wheel.wasm
wasm-opt -O3 strandtest_nodelay.wasm -o strandtest_nodelay.wasm
wasm-strip strandtest.wasm
wasm-strip strandtest_wheel.wasm
wasm-strip strandtest_nodelay.wasm
wasm2wat --generate-names strandtest.wasm -o strandtest.wat
wasm2wat --generate-names strandtest_wheel.wasm -o strandtest_wheel.wat
wasm2wat --generate-names strandtest_nodelay.wasm -o strandtest_nodelay.wat
xxd -i strandtest.wasm > strandtest.wasm.h
xxd -i strandtest_wheel.wasm > strandtest_wheel.wasm.h
xxd -i strandtest_nodelay.wasm > strandtest_nodelay.wasm.h
mv strandtest.wasm ../../wasms/
mv strandtest_wheel.wasm ../../wasms/
mv strandtest_nodelay.wasm ../../wasms/
