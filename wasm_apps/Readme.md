## NeoWasm WebAssembly example apps

## C++ app

`./cpp` directory contains an example Arduino app (sketch) that is compiled to WebAssembly.  
Compilation is performed using `wasicc` here, but `clang --target=wasm32` can be used as well.  
See `build.sh` for details.

## Rust app

Before building the app, please install the toolchain:
```sh
rustup target add wasm32-unknown-unknown
```
To rebuild, use `build.sh`.

## AssemblyScript app

Before building the app, please install npm dependencies:
```sh
npm install    # or yarn install
```
To rebuild, use `npm run build`.

## TinyGo app

To rebuild, use `build.sh`.
