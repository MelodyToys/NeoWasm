(module
  (type $t0 (func (param i32 i32)))
  (type $t1 (func))
  (type $t2 (func (result i32)))
  (type $t3 (func (param i32)))
  (import "arduino" "print" (func $arduino.print (type $t0)))
  (import "arduino" "getPinLED" (func $arduino.getPinLED (type $t2)))
  (import "arduino" "pinMode" (func $arduino.pinMode (type $t0)))
  (import "arduino" "digitalWrite" (func $arduino.digitalWrite (type $t0)))
  (import "arduino" "delay" (func $arduino.delay (type $t3)))
  (func $_start (type $t1)
    nop)
  (func $setup (type $t1)
    (local $l0 i32)
    i32.const 1025
    i32.const 14
    call $arduino.print
    i32.const 1049
    i32.const 1
    call $arduino.print
    i32.const 1024
    call $arduino.getPinLED
    local.tee $l0
    i32.store8
    local.get $l0
    i32.const 1
    call $arduino.pinMode)
  (func $loop (type $t1)
    i32.const 1024
    i32.load8_u
    i32.const 1
    call $arduino.digitalWrite
    i32.const 500
    call $arduino.delay
    i32.const 1024
    i32.load8_u
    i32.const 0
    call $arduino.digitalWrite
    i32.const 500
    call $arduino.delay
    i32.const 1040
    i32.const 8
    call $arduino.print
    i32.const 1049
    i32.const 1
    call $arduino.print)
  (memory $memory 1)
  (export "memory" (memory 0))
  (export "_start" (func $_start))
  (export "setup" (func $setup))
  (export "loop" (func $loop))
  (data $d0 (i32.const 1025) "C++ is running\00C++ Loop\00\0a"))
