(module
  (type $t0 (func))
  (type $t1 (func (param i32)))
  (type $t2 (func (param i32 i32)))
  (type $t3 (func (result i32)))
  (type $t4 (func (param i32) (result i32)))
  (type $t5 (func (param i32 i32 i32) (result i32)))
  (import "neowasm" "numPixels" (func $neowasm.numPixels (type $t3)))
  (import "neowasm" "setPixelColor32" (func $neowasm.setPixelColor32 (type $t2)))
  (import "neowasm" "show" (func $neowasm.show (type $t0)))
  (import "neowasm" "delay" (func $neowasm.delay (type $t1)))
  (import "neowasm" "clear" (func $neowasm.clear (type $t0)))
  (import "neowasm" "Wheel" (func $neowasm.Wheel (type $t4)))
  (import "neowasm" "Color" (func $neowasm.Color (type $t5)))
  (import "neowasm" "print" (func $neowasm.print (type $t2)))
  (func $_start (type $t0)
    nop)
  (func $f9 (type $t1) (param $p0 i32)
    (local $l1 i32)
    call $neowasm.numPixels
    if $I0
      loop $L1
        local.get $l1
        i32.const 255
        i32.and
        local.get $p0
        call $neowasm.setPixelColor32
        call $neowasm.show
        i32.const 50
        call $neowasm.delay
        call $neowasm.numPixels
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
  (func $f10 (type $t1) (param $p0 i32)
    (local $l1 i32) (local $l2 i32) (local $l3 i32)
    loop $L0
      i32.const 0
      local.set $l1
      loop $L1
        call $neowasm.clear
        call $neowasm.numPixels
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
            call $neowasm.setPixelColor32
            call $neowasm.numPixels
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
        call $neowasm.show
        i32.const 50
        call $neowasm.delay
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
  (func $setup (type $t0)
    i32.const 1024
    i32.const 21
    call $neowasm.print
    i32.const 1046
    i32.const 1
    call $neowasm.print)
  (func $loop (type $t0)
    (local $l0 i32) (local $l1 i32) (local $l2 i32) (local $l3 i32) (local $l4 i32)
    i32.const 255
    i32.const 0
    i32.const 0
    call $neowasm.Color
    call $f9
    i32.const 0
    i32.const 255
    i32.const 0
    call $neowasm.Color
    call $f9
    i32.const 0
    i32.const 0
    i32.const 255
    call $neowasm.Color
    call $f9
    i32.const 127
    i32.const 127
    i32.const 127
    call $neowasm.Color
    call $f10
    i32.const 127
    i32.const 0
    i32.const 0
    call $neowasm.Color
    call $f10
    i32.const 0
    i32.const 0
    i32.const 127
    call $neowasm.Color
    call $f10
    call $neowasm.numPixels
    if $I0
      loop $L1
        local.get $l0
        i32.const 65535
        i32.and
        local.get $l0
        i32.const 255
        i32.and
        call $neowasm.Wheel
        call $neowasm.setPixelColor32
        call $neowasm.numPixels
        local.get $l0
        i32.const 1
        i32.add
        local.tee $l0
        i32.const 65535
        i32.and
        i32.gt_u
        br_if $L1
      end
    end
    call $neowasm.show
    i32.const 10
    call $neowasm.delay
    loop $L2
      local.get $l3
      i32.const 255
      i32.and
      local.set $l4
      i32.const 0
      local.set $l2
      loop $L3
        call $neowasm.numPixels
        if $I4
          i32.const 0
          local.set $l0
          i32.const 0
          local.set $l1
          loop $L5
            local.get $l1
            local.get $l2
            i32.add
            i32.const 65535
            i32.and
            local.get $l0
            local.get $l4
            i32.add
            i32.const 255
            i32.rem_u
            call $neowasm.Wheel
            call $neowasm.setPixelColor32
            call $neowasm.numPixels
            local.get $l0
            i32.const 3
            i32.add
            local.tee $l1
            i32.const 65535
            i32.and
            local.tee $l0
            i32.gt_u
            br_if $L5
          end
        end
        call $neowasm.show
        i32.const 50
        call $neowasm.delay
        call $neowasm.numPixels
        if $I6
          i32.const 0
          local.set $l0
          i32.const 0
          local.set $l1
          loop $L7
            local.get $l1
            local.get $l2
            i32.add
            i32.const 65535
            i32.and
            i32.const 0
            i32.const 0
            i32.const 0
            call $neowasm.Color
            call $neowasm.setPixelColor32
            call $neowasm.numPixels
            local.get $l0
            i32.const 3
            i32.add
            local.tee $l1
            i32.const 65535
            i32.and
            local.tee $l0
            i32.gt_u
            br_if $L7
          end
        end
        local.get $l2
        i32.const 1
        i32.add
        local.tee $l2
        i32.const 3
        i32.ne
        br_if $L3
      end
      local.get $l3
      i32.const 1
      i32.add
      local.set $l3
      br $L2
    end
    unreachable)
  (memory $memory 1)
  (export "memory" (memory 0))
  (export "_start" (func $_start))
  (export "setup" (func $setup))
  (export "loop" (func $loop))
  (data $d0 (i32.const 1024) "\0astrandtest ... start\00\0a"))
