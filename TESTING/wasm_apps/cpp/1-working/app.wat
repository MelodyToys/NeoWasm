(module
  (type $t0 (func (param i32 i32)))
  (type $t1 (func (result i32)))
  (type $t2 (func (param i32)))
  (type $t3 (func))
  (import "arduino" "print" (func $arduino.print (type $t0)))
  (import "arduino" "getPinLED" (func $arduino.getPinLED (type $t1)))
  (import "arduino" "pinMode" (func $arduino.pinMode (type $t0)))
  (import "arduino" "digitalWrite" (func $arduino.digitalWrite (type $t0)))
  (import "arduino" "delay" (func $arduino.delay (type $t2)))
  (func $_start (type $t3)
    (local $l0 i32)
    i32.const 1028
    i32.const 19
    call $arduino.print
    i32.const 1057
    i32.const 1
    call $arduino.print
    i32.const 1024
    call $arduino.getPinLED
    local.tee $l0
    i32.store
    local.get $l0
    i32.const 1
    call $arduino.pinMode
    loop $L0
      i32.const 1024
      i32.load
      i32.const 1
      call $arduino.digitalWrite
      i32.const 500
      call $arduino.delay
      i32.const 1024
      i32.load
      i32.const 0
      call $arduino.digitalWrite
      i32.const 500
      call $arduino.delay
      i32.const 1048
      i32.const 8
      call $arduino.print
      i32.const 1057
      i32.const 1
      call $arduino.print
      br $L0
    end
    unreachable)
  (memory $memory 1)
  (export "memory" (memory 0))
  (export "_start" (func $_start))
  (data $d0 (i32.const 1028) "C++ is running \f0\9f\98\8e\00C++ Loop\00\0a"))
