# Compile
npm install
npm run build

# Optimize (optional)
wasm-opt -O3 app.wasm -o app.wasm
wasm-strip app.wasm

# Convert to WAT
#wasm2wat --generate-names app.wasm -o app.wat

# Convert to C header
# xxd -i app.wasm > app.wasm.h

# Copy wasm to ROM filesystem
# cp app.wasm ../../../NeoWasm/data/wasm/strandtest_nodelay.wasm
