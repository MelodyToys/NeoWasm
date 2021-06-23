(module
  (type $t0 (func))
  (type $t1 (func (param i32) (result i32)))
  (type $t2 (func (param i32 i32)))
  (type $t3 (func (param i32)))
  (type $t4 (func (result i32)))
  (type $t5 (func (param i32 i32 i32 i32)))
  (type $t6 (func (param i32 i32 i32) (result i32)))
  (import "arduino" "numPixels" (func $arduino.numPixels (type $t4)))
  (import "arduino" "setPixelColor32" (func $arduino.setPixelColor32 (type $t2)))
  (import "arduino" "show" (func $arduino.show (type $t0)))
  (import "arduino" "delay" (func $arduino.delay (type $t3)))
  (import "arduino" "Wheel" (func $arduino.Wheel (type $t1)))
  (import "arduino" "WheelR" (func $arduino.WheelR (type $t1)))
  (import "arduino" "WheelG" (func $arduino.WheelG (type $t1)))
  (import "arduino" "WheelB" (func $arduino.WheelB (type $t1)))
  (import "arduino" "setPixelColor" (func $arduino.setPixelColor (type $t5)))
  (import "arduino" "print" (func $arduino.print (type $t2)))
  (import "arduino" "Color" (func $arduino.Color (type $t6)))
  (func $_start (type $t0)
    nop)
  (func $f12 (type $t3) (param $p0 i32)
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
    (local $l0 i32) (local $l1 i32) (local $l2 i32)
    i32.const 255
    i32.const 0
    i32.const 0
    call $arduino.Color
    call $f12
    i32.const 0
    i32.const 255
    i32.const 0
    call $arduino.Color
    call $f12
    i32.const 0
    i32.const 0
    i32.const 255
    call $arduino.Color
    call $f12
    loop $L0
      call $arduino.numPixels
      if $I1
        i32.const 0
        local.set $l0
        loop $L2
          local.get $l0
          i32.const 65535
          i32.and
          local.get $l0
          local.get $l1
          i32.add
          i32.const 255
          i32.and
          local.tee $l2
          call $arduino.WheelR
          local.get $l2
          call $arduino.WheelG
          local.get $l2
          call $arduino.WheelB
          call $arduino.setPixelColor
          call $arduino.numPixels
          local.get $l0
          i32.const 1
          i32.add
          local.tee $l0
          i32.const 65535
          i32.and
          i32.gt_u
          br_if $L2
        end
      end
      call $arduino.show
      i32.const 20
      call $arduino.delay
      local.get $l1
      i32.const 1
      i32.add
      local.tee $l1
      i32.const 65535
      i32.and
      i32.const 256
      i32.lt_u
      br_if $L0
    end
    i32.const 0
    local.set $l0
    call $arduino.numPixels
    if $I3
      loop $L4
        local.get $l0
        i32.const 65535
        i32.and
        local.get $l0
        i32.const 255
        i32.and
        call $arduino.Wheel
        call $arduino.setPixelColor32
        call $arduino.numPixels
        local.get $l0
        i32.const 1
        i32.add
        local.tee $l0
        i32.const 65535
        i32.and
        i32.gt_u
        br_if $L4
      end
    end
    call $arduino.show
    i32.const 20
    call $arduino.delay
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
