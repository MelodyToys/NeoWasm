(module
  (type $t0 (func))
  (type $t1 (func (param i32 i32)))
  (type $t2 (func (param i32)))
  (import "arduino" "print" (func $arduino.print (type $t1)))
  (import "arduino" "delay" (func $arduino.delay (type $t2)))
  (func $_start (type $t0)
    nop)
  (func $setup (type $t0)
    i32.const 1024
    i32.const 14
    call $arduino.print
    i32.const 1048
    i32.const 1
    call $arduino.print)
  (func $loop (type $t0)
    i32.const 500
    call $arduino.delay
    i32.const 1039
    i32.const 8
    call $arduino.print
    i32.const 1048
    i32.const 1
    call $arduino.print)
  (memory $memory 1)
  (export "memory" (memory 0))
  (export "_start" (func $_start))
  (export "setup" (func $setup))
  (export "loop" (func $loop))
  (data $d0 (i32.const 1024) "C++ is running\00C++ Loop\00\0a"))
