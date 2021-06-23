(module
  (type $t0 (func))
  (type $t1 (func (param i32) (result i32)))
  (type $t2 (func (param i32 i32 i32)))
  (type $t3 (func (result i32)))
  (type $t4 (func (param i32 i32 i32 i32)))
  (type $t5 (func (param i32)))
  (type $t6 (func (param i32 i32)))
  (import "neowasm" "numPixels" (func $neowasm.numPixels (type $t3)))
  (import "neowasm" "setPixelColor" (func $neowasm.setPixelColor (type $t4)))
  (import "neowasm" "show" (func $neowasm.show (type $t0)))
  (import "neowasm" "delay" (func $neowasm.delay (type $t5)))
  (import "neowasm" "WheelR" (func $neowasm.WheelR (type $t1)))
  (import "neowasm" "WheelG" (func $neowasm.WheelG (type $t1)))
  (import "neowasm" "WheelB" (func $neowasm.WheelB (type $t1)))
  (import "neowasm" "print" (func $neowasm.print (type $t6)))
  (func $_start (type $t0)
    nop)
  (func $f9 (type $t2) (param $p0 i32) (param $p1 i32) (param $p2 i32)
    (local $l3 i32)
    call $neowasm.numPixels
    if $I0
      loop $L1
        local.get $l3
        i32.const 65535
        i32.and
        local.get $p0
        local.get $p1
        local.get $p2
        call $neowasm.setPixelColor
        call $neowasm.show
        i32.const 50
        call $neowasm.delay
        call $neowasm.numPixels
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
  (func $f10 (type $t2) (param $p0 i32) (param $p1 i32) (param $p2 i32)
    (local $l3 i32) (local $l4 i32) (local $l5 i32) (local $l6 i32)
    loop $L0
      i32.const 0
      local.set $l5
      loop $L1
        call $neowasm.numPixels
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
            call $neowasm.setPixelColor
            call $neowasm.numPixels
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
        call $neowasm.show
        i32.const 50
        call $neowasm.delay
        call $neowasm.numPixels
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
            call $neowasm.setPixelColor
            call $neowasm.numPixels
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
    i32.const 27
    call $neowasm.print
    i32.const 1052
    i32.const 1
    call $neowasm.print)
  (func $loop (type $t0)
    (local $l0 i32) (local $l1 i32) (local $l2 i32) (local $l3 i32) (local $l4 i32)
    i32.const 255
    i32.const 0
    i32.const 0
    call $f9
    i32.const 0
    i32.const 255
    i32.const 0
    call $f9
    i32.const 0
    i32.const 0
    i32.const 255
    call $f9
    i32.const 127
    i32.const 127
    i32.const 127
    call $f10
    i32.const 127
    i32.const 0
    i32.const 0
    call $f10
    i32.const 0
    i32.const 0
    i32.const 127
    call $f10
    loop $L0
      call $neowasm.numPixels
      if $I1
        i32.const 0
        local.set $l1
        loop $L2
          local.get $l1
          i32.const 65535
          i32.and
          local.get $l0
          local.get $l1
          i32.add
          i32.const 255
          i32.and
          local.tee $l2
          call $neowasm.WheelR
          local.get $l2
          call $neowasm.WheelG
          local.get $l2
          call $neowasm.WheelB
          call $neowasm.setPixelColor
          call $neowasm.numPixels
          local.get $l1
          i32.const 1
          i32.add
          local.tee $l1
          i32.const 65535
          i32.and
          i32.gt_u
          br_if $L2
        end
      end
      call $neowasm.show
      i32.const 20
      call $neowasm.delay
      local.get $l0
      i32.const 1
      i32.add
      local.tee $l0
      i32.const 65535
      i32.and
      i32.const 256
      i32.lt_u
      br_if $L0
    end
    i32.const 0
    local.set $l1
    loop $L3
      call $neowasm.numPixels
      if $I4
        i32.const 0
        local.set $l0
        i32.const 0
        local.set $l2
        loop $L5
          local.get $l2
          i32.const 65535
          i32.and
          local.get $l0
          call $neowasm.numPixels
          i32.div_u
          local.get $l1
          i32.add
          i32.const 255
          i32.and
          local.tee $l3
          call $neowasm.WheelR
          local.get $l3
          call $neowasm.WheelG
          local.get $l3
          call $neowasm.WheelB
          call $neowasm.setPixelColor
          local.get $l0
          i32.const 256
          i32.add
          local.set $l0
          call $neowasm.numPixels
          local.get $l2
          i32.const 1
          i32.add
          local.tee $l2
          i32.gt_u
          br_if $L5
        end
      end
      call $neowasm.show
      i32.const 20
      call $neowasm.delay
      local.get $l1
      i32.const 1
      i32.add
      local.tee $l1
      i32.const 1276
      i32.ne
      br_if $L3
    end
    i32.const 0
    local.set $l3
    loop $L6
      local.get $l3
      i32.const 255
      i32.and
      local.set $l4
      i32.const 0
      local.set $l2
      loop $L7
        call $neowasm.numPixels
        if $I8
          i32.const 0
          local.set $l1
          i32.const 0
          local.set $l0
          loop $L9
            local.get $l0
            local.get $l2
            i32.add
            i32.const 65535
            i32.and
            local.get $l1
            local.get $l4
            i32.add
            i32.const 255
            i32.rem_u
            local.tee $l0
            call $neowasm.WheelR
            local.get $l0
            call $neowasm.WheelG
            local.get $l0
            call $neowasm.WheelB
            call $neowasm.setPixelColor
            call $neowasm.numPixels
            local.get $l1
            i32.const 3
            i32.add
            local.tee $l0
            i32.const 65535
            i32.and
            local.tee $l1
            i32.gt_u
            br_if $L9
          end
        end
        call $neowasm.show
        i32.const 50
        call $neowasm.delay
        call $neowasm.numPixels
        if $I10
          i32.const 0
          local.set $l1
          i32.const 0
          local.set $l0
          loop $L11
            local.get $l0
            local.get $l2
            i32.add
            i32.const 65535
            i32.and
            i32.const 0
            i32.const 0
            i32.const 0
            call $neowasm.setPixelColor
            call $neowasm.numPixels
            local.get $l1
            i32.const 3
            i32.add
            local.tee $l0
            i32.const 65535
            i32.and
            local.tee $l1
            i32.gt_u
            br_if $L11
          end
        end
        local.get $l2
        i32.const 1
        i32.add
        local.tee $l2
        i32.const 3
        i32.ne
        br_if $L7
      end
      local.get $l3
      i32.const 1
      i32.add
      local.set $l3
      br $L6
    end
    unreachable)
  (memory $memory 1)
  (export "memory" (memory 0))
  (export "_start" (func $_start))
  (export "setup" (func $setup))
  (export "loop" (func $loop))
  (data $d0 (i32.const 1024) "\0astrandtest_wheel ... start\00\0a"))
