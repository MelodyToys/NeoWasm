(module
  (type $t0 (func))
  (type $t1 (func (param i32 i32)))
  (type $t2 (func (param i32)))
  (type $t3 (func (result i32)))
  (type $t4 (func (param i32 i32 i32) (result i32)))
  (import "arduino" "numPixels" (func $arduino.numPixels (type $t3)))
  (import "arduino" "setPixelColor32" (func $arduino.setPixelColor32 (type $t1)))
  (import "arduino" "show" (func $arduino.show (type $t0)))
  (import "arduino" "delay" (func $arduino.delay (type $t2)))
  (import "arduino" "print" (func $arduino.print (type $t1)))
  (import "arduino" "Color" (func $arduino.Color (type $t4)))
  (func $_start (type $t0)
    nop)
  (func $f7 (type $t2) (param $p0 i32)
    (local $l1 i32)
    call $arduino.numPixels
    if $I0
      loop $L1
        local.get $l1
        i32.const 255
        i32.and
        local.get $p0
        call $arduino.setPixelColor32
        call $arduino.show
        i32.const 50
        call $arduino.delay
        call $arduino.numPixels
        local.get $l1
        i32.const 1
        i32.add
        local.tee $l1
        i32.const 255
        i32.and
        i32.gt_u
        br_if $L1
      end
    end)
  (func $setup (type $t0)
    i32.const 1024
    i32.const 21
    call $arduino.print
    i32.const 1066
    i32.const 1
    call $arduino.print)
  (func $loop (type $t0)
    i32.const 255
    i32.const 0
    i32.const 0
    call $arduino.Color
    call $f7
    i32.const 0
    i32.const 255
    i32.const 0
    call $arduino.Color
    call $f7
    i32.const 0
    i32.const 0
    i32.const 255
    call $arduino.Color
    call $f7
    i32.const 1046
    i32.const 19
    call $arduino.print
    i32.const 1066
    i32.const 1
    call $arduino.print)
  (memory $memory 1)
  (export "memory" (memory 0))
  (export "_start" (func $_start))
  (export "setup" (func $setup))
  (export "loop" (func $loop))
  (data $d0 (i32.const 1024) "\0astrandtest ... start\00strandtest ... loop\00\0a"))
