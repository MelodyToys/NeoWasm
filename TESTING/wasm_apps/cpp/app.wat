(module
  (type $t0 (func))
  (type $t1 (func (param i32)))
  (type $t2 (func (param i32) (result i32)))
  (type $t3 (func (param i32 i32)))
  (type $t4 (func (param i32 i32 i32)))
  (type $t5 (func (result i32)))
  (type $t6 (func (param i32 i32 i32 i32)))
  (type $t7 (func (param i32 i32 i32) (result i32)))
  (import "arduino" "numPixels" (func $arduino.numPixels (type $t5)))
  (import "arduino" "setPixelColor" (func $arduino.setPixelColor (type $t6)))
  (import "arduino" "show" (func $arduino.show (type $t0)))
  (import "arduino" "delay" (func $arduino.delay (type $t1)))
  (import "arduino" "setPixelColor32" (func $arduino.setPixelColor32 (type $t3)))
  (import "arduino" "clear" (func $arduino.clear (type $t0)))
  (import "arduino" "WheelR" (func $arduino.WheelR (type $t2)))
  (import "arduino" "WheelG" (func $arduino.WheelG (type $t2)))
  (import "arduino" "WheelB" (func $arduino.WheelB (type $t2)))
  (import "arduino" "print" (func $arduino.print (type $t3)))
  (import "arduino" "Color" (func $arduino.Color (type $t7)))
  (func $_start (type $t0)
    nop)
  (func $f12 (type $t4) (param $p0 i32) (param $p1 i32) (param $p2 i32)
    (local $l3 i32)
    call $arduino.numPixels
    if $I0
      loop $L1
        local.get $l3
        i32.const 65535
        i32.and
        local.get $p0
        local.get $p1
        local.get $p2
        call $arduino.setPixelColor
        call $arduino.show
        i32.const 50
        call $arduino.delay
        call $arduino.numPixels
        local.get $l3
        i32.const 1
        i32.add
        local.tee $l3
        i32.const 65535
        i32.and
        i32.gt_u
        br_if $L1
      end
    end)
  (func $f13 (type $t1) (param $p0 i32)
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
  (func $f14 (type $t1) (param $p0 i32)
    (local $l1 i32) (local $l2 i32) (local $l3 i32)
    loop $L0
      i32.const 0
      local.set $l1
      loop $L1
        call $arduino.clear
        call $arduino.numPixels
        local.get $l1
        i32.gt_u
        if $I2
          local.get $l1
          local.set $l2
          loop $L3
            local.get $l2
            i32.const 255
            i32.and
            local.get $p0
            call $arduino.setPixelColor32
            call $arduino.numPixels
            local.get $l2
            i32.const 3
            i32.add
            local.tee $l2
            i32.const 255
            i32.and
            i32.gt_u
            br_if $L3
          end
        end
        call $arduino.show
        i32.const 50
        call $arduino.delay
        local.get $l1
        i32.const 1
        i32.add
        local.tee $l1
        i32.const 3
        i32.ne
        br_if $L1
      end
      local.get $l3
      i32.const 1
      i32.add
      local.tee $l3
      i32.const 255
      i32.and
      i32.const 10
      i32.lt_u
      br_if $L0
    end)
  (func $f15 (type $t4) (param $p0 i32) (param $p1 i32) (param $p2 i32)
    (local $l3 i32) (local $l4 i32) (local $l5 i32) (local $l6 i32)
    loop $L0
      i32.const 0
      local.set $l5
      loop $L1
        call $arduino.numPixels
        if $I2
          i32.const 0
          local.set $l3
          i32.const 0
          local.set $l4
          loop $L3
            local.get $l4
            local.get $l5
            i32.add
            i32.const 65535
            i32.and
            local.get $p0
            local.get $p1
            local.get $p2
            call $arduino.setPixelColor
            call $arduino.numPixels
            local.get $l3
            i32.const 3
            i32.add
            local.tee $l4
            i32.const 65535
            i32.and
            local.tee $l3
            i32.gt_u
            br_if $L3
          end
        end
        call $arduino.show
        i32.const 50
        call $arduino.delay
        call $arduino.numPixels
        if $I4
          i32.const 0
          local.set $l3
          i32.const 0
          local.set $l4
          loop $L5
            local.get $l4
            local.get $l5
            i32.add
            i32.const 65535
            i32.and
            i32.const 0
            i32.const 0
            i32.const 0
            call $arduino.setPixelColor
            call $arduino.numPixels
            local.get $l3
            i32.const 3
            i32.add
            local.tee $l4
            i32.const 65535
            i32.and
            local.tee $l3
            i32.gt_u
            br_if $L5
          end
        end
        local.get $l5
        i32.const 1
        i32.add
        local.tee $l5
        i32.const 3
        i32.ne
        br_if $L1
      end
      local.get $l6
      i32.const 1
      i32.add
      local.tee $l6
      i32.const 255
      i32.and
      i32.const 10
      i32.lt_u
      br_if $L0
    end)
  (func $setup (type $t0)
    i32.const 1024
    i32.const 21
    call $arduino.print
    i32.const 1149
    i32.const 1
    call $arduino.print)
  (func $loop (type $t0)
    (local $l0 i32) (local $l1 i32) (local $l2 i32)
    i32.const 1046
    i32.const 14
    call $arduino.print
    i32.const 1149
    i32.const 1
    call $arduino.print
    i32.const 255
    i32.const 0
    i32.const 0
    call $f12
    i32.const 0
    i32.const 255
    i32.const 0
    call $f12
    i32.const 0
    i32.const 0
    i32.const 255
    call $f12
    i32.const 1061
    i32.const 16
    call $arduino.print
    i32.const 1149
    i32.const 1
    call $arduino.print
    i32.const 255
    i32.const 0
    i32.const 0
    call $arduino.Color
    call $f13
    i32.const 0
    i32.const 255
    i32.const 0
    call $arduino.Color
    call $f13
    i32.const 0
    i32.const 0
    i32.const 255
    call $arduino.Color
    call $f13
    i32.const 1078
    i32.const 17
    call $arduino.print
    i32.const 1149
    i32.const 1
    call $arduino.print
    i32.const 127
    i32.const 127
    i32.const 127
    call $f15
    i32.const 127
    i32.const 0
    i32.const 0
    call $f15
    i32.const 0
    i32.const 0
    i32.const 127
    call $f15
    i32.const 1096
    i32.const 19
    call $arduino.print
    i32.const 1149
    i32.const 1
    call $arduino.print
    i32.const 127
    i32.const 127
    i32.const 127
    call $arduino.Color
    call $f14
    i32.const 127
    i32.const 0
    i32.const 0
    call $arduino.Color
    call $f14
    i32.const 0
    i32.const 0
    i32.const 127
    call $arduino.Color
    call $f14
    i32.const 1116
    i32.const 12
    call $arduino.print
    i32.const 1149
    i32.const 1
    call $arduino.print
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
    i32.const 1129
    i32.const 19
    call $arduino.print
    i32.const 1149
    i32.const 1
    call $arduino.print)
  (memory $memory 1)
  (export "memory" (memory 0))
  (export "_start" (func $_start))
  (export "setup" (func $setup))
  (export "loop" (func $loop))
  (data $d0 (i32.const 1024) "\0astrandtest ... start\00colorWipe ... \00colorWipe32 ... \00theaterChase ... \00theaterChase32 ... \00rainbow ... \00strandtest ... loop\00\0a"))
