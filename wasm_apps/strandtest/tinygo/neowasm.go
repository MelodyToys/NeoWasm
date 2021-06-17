/*
 * NeoWasm API
 */

const (
    LOW  = 0
    HIGH = 1

    INPUT           =  0
    OUTPUT          =  1
    INPUT_PULLUP    =  2
)

//go:wasm-module neowasm
//go:export millis
func millis() uint

//go:wasm-module neowasm
//go:export delay
func delay(ms uint)

//go:wasm-module neowasm
//go:export pinMode
func pinMode(pin, mode uint)

//go:wasm-module neowasm
//go:export digitalWrite
func digitalWrite(pin, value uint)

//go:wasm-module neowasm
//go:export getPinLED
func getPinLED() uint
