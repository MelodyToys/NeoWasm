(module
  (type $t0 (func))
  (type $t1 (func (param i32) (result i32)))
  (type $t2 (func (result i32)))
  (type $t3 (func (param i32 i32 i32)))
  (type $t4 (func (param i32 i32 i32 i32)))
  (type $t5 (func (param i32 i32)))
  (import "neowasm" "setPixelColor" (func $neowasm.setPixelColor (type $t4)))
  (import "neowasm" "show" (func $neowasm.show (type $t0)))
  (import "neowasm" "clear" (func $neowasm.clear (type $t0)))
  (import "neowasm" "WheelR" (func $neowasm.WheelR (type $t1)))
  (import "neowasm" "WheelG" (func $neowasm.WheelG (type $t1)))
  (import "neowasm" "WheelB" (func $neowasm.WheelB (type $t1)))
  (import "neowasm" "numPixels" (func $neowasm.numPixels (type $t2)))
  (import "neowasm" "print" (func $neowasm.print (type $t5)))
  (import "neowasm" "millis" (func $neowasm.millis (type $t2)))
  (func $_start (type $t0)
    nop)
  (func $f10 (type $t3) (param $p0 i32) (param $p1 i32) (param $p2 i32)
    i32.const 1040
    i32.load
    i32.const 50
    i32.ne
    if $I0
      i32.const 1040
      i32.const 50
      i32.store
    end
    i32.const 1052
    i32.load16_u
    local.get $p0
    local.get $p1
    local.get $p2
    call $neowasm.setPixelColor
    call $neowasm.show
    i32.const 1052
    i32.const 1052
    i32.load16_u
    i32.const 1
    i32.add
    local.tee $p0
    i32.store16
    i32.const 1054
    i32.load16_u
    local.get $p0
    i32.const 65535
    i32.and
    i32.le_u
    if $I1
      i32.const 1052
      i32.const 0
      i32.store16
      call $neowasm.clear
    end)
  (func $f11 (type $t3) (param $p0 i32) (param $p1 i32) (param $p2 i32)
    (local $l3 i32)
    i32.const 1040
    i32.load
    i32.const 50
    i32.ne
    if $I0
      i32.const 1040
      i32.const 50
      i32.store
    end
    i32.const 1054
    i32.load16_u
    if $I1
      loop $L2
        local.get $l3
        i32.const 1044
        i32.load
        i32.add
        i32.const 65535
        i32.and
        local.get $p0
        local.get $p1
        local.get $p2
        call $neowasm.setPixelColor
        local.get $l3
        i32.const 3
        i32.add
        local.tee $l3
        i32.const 1054
        i32.load16_u
        i32.lt_u
        br_if $L2
      end
    end
    call $neowasm.show
    i32.const 1044
    i32.load
    local.set $p0
    i32.const 1054
    i32.load16_u
    if $I3
      i32.const 0
      local.set $l3
      loop $L4
        local.get $p0
        local.get $l3
        i32.add
        i32.const 65535
        i32.and
        i32.const 0
        i32.const 0
        i32.const 0
        call $neowasm.setPixelColor
        i32.const 1044
        i32.load
        local.set $p0
        local.get $l3
        i32.const 3
        i32.add
        local.tee $l3
        i32.const 1054
        i32.load16_u
        i32.lt_u
        br_if $L4
      end
    end
    i32.const 1044
    i32.const 0
    local.get $p0
    i32.const 1
    i32.add
    local.get $p0
    i32.const 1
    i32.gt_s
    select
    i32.store)
  (func $setup (type $t0)
    i32.const 1032
    i32.const 5500
    i32.store
    i32.const 1040
    i32.const 50
    i32.store
    i32.const 1028
    i32.const 0
    i32.store
    i32.const 1024
    i32.const 0
    i32.store
    i32.const 1036
    i32.const 0
    i32.store
    i32.const 1044
    i32.const 0
    i32.store
    i32.const 1048
    i32.const 0
    i32.store
    i32.const 1052
    i32.const 0
    i32.store16
    i32.const 1054
    call $neowasm.numPixels
    i32.store16
    i32.const 1056
    i32.const 29
    call $neowasm.print
    i32.const 1114
    i32.const 1
    call $neowasm.print)
  (func $loop (type $t0)
    (local $l0 i32) (local $l1 i32) (local $l2 i32)
    block $B0
      call $neowasm.millis
      local.tee $l0
      i32.const 1024
      i32.load
      i32.sub
      i32.const 1032
      i32.load
      i32.lt_u
      br_if $B0
      i32.const 1024
      local.get $l0
      i32.store
      i32.const 1028
      i32.const 1028
      i32.load
      local.tee $l1
      i32.const 1
      i32.add
      i32.store
      local.get $l1
      i32.const 7
      i32.lt_s
      br_if $B0
      i32.const 1028
      i32.const 0
      i32.store
      i32.const 1086
      i32.const 27
      call $neowasm.print
      i32.const 1114
      i32.const 1
      call $neowasm.print
    end
    block $B1
      i32.const 1040
      i32.load
      local.get $l0
      i32.const 1036
      i32.load
      i32.sub
      i32.gt_u
      br_if $B1
      i32.const 1036
      local.get $l0
      i32.store
      i32.const 1028
      i32.load
      local.tee $l0
      i32.const 8
      i32.gt_u
      br_if $B1
      block $B2
        block $B3
          block $B4
            block $B5
              block $B6
                block $B7
                  block $B8
                    block $B9
                      block $B10
                        local.get $l0
                        i32.const 1
                        i32.sub
                        br_table $B3 $B4 $B5 $B6 $B7 $B8 $B9 $B10 $B2
                      end
                      i32.const 0
                      local.set $l0
                      i32.const 1040
                      i32.load
                      i32.const 50
                      i32.ne
                      if $I11
                        i32.const 1040
                        i32.const 50
                        i32.store
                      end
                      i32.const 1054
                      i32.load16_u
                      if $I12
                        loop $L13
                          local.get $l0
                          i32.const 1044
                          i32.load
                          i32.add
                          i32.const 65535
                          i32.and
                          local.get $l0
                          i32.const 1048
                          i32.load
                          i32.add
                          i32.const 255
                          i32.rem_s
                          i32.const 255
                          i32.and
                          local.tee $l1
                          call $neowasm.WheelR
                          local.get $l1
                          call $neowasm.WheelG
                          local.get $l1
                          call $neowasm.WheelB
                          call $neowasm.setPixelColor
                          local.get $l0
                          i32.const 3
                          i32.add
                          local.tee $l0
                          i32.const 1054
                          i32.load16_u
                          i32.lt_u
                          br_if $L13
                        end
                      end
                      call $neowasm.show
                      i32.const 1044
                      i32.load
                      local.set $l1
                      i32.const 1054
                      i32.load16_u
                      if $I14
                        i32.const 0
                        local.set $l0
                        loop $L15
                          local.get $l0
                          local.get $l1
                          i32.add
                          i32.const 65535
                          i32.and
                          i32.const 0
                          i32.const 0
                          i32.const 0
                          call $neowasm.setPixelColor
                          i32.const 1044
                          i32.load
                          local.set $l1
                          local.get $l0
                          i32.const 3
                          i32.add
                          local.tee $l0
                          i32.const 1054
                          i32.load16_u
                          i32.lt_u
                          br_if $L15
                        end
                      end
                      i32.const 1044
                      local.get $l1
                      i32.const 1
                      i32.add
                      i32.store
                      i32.const 1048
                      i32.const 1048
                      i32.load
                      local.tee $l0
                      i32.const 1
                      i32.add
                      i32.store
                      local.get $l1
                      i32.const 2
                      i32.ge_s
                      if $I16
                        i32.const 1044
                        i32.const 0
                        i32.store
                      end
                      local.get $l0
                      i32.const 254
                      i32.ge_s
                      if $I17
                        i32.const 1048
                        i32.const 0
                        i32.store
                      end
                      return
                    end
                    i32.const 0
                    local.set $l0
                    i32.const 0
                    local.set $l1
                    i32.const 1040
                    i32.load
                    i32.const 20
                    i32.ne
                    if $I18
                      i32.const 1040
                      i32.const 20
                      i32.store
                    end
                    i32.const 1054
                    i32.load16_u
                    local.tee $l2
                    if $I19
                      loop $L20
                        local.get $l1
                        i32.const 65535
                        i32.and
                        i32.const 1048
                        i32.load
                        local.get $l0
                        local.get $l2
                        i32.div_u
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
                        local.get $l0
                        i32.const 255
                        i32.add
                        local.set $l0
                        local.get $l1
                        i32.const 1
                        i32.add
                        local.tee $l1
                        i32.const 1054
                        i32.load16_u
                        local.tee $l2
                        i32.lt_u
                        br_if $L20
                      end
                    end
                    call $neowasm.show
                    i32.const 1048
                    i32.const 0
                    i32.const 1048
                    i32.load
                    local.tee $l0
                    i32.const 1
                    i32.add
                    local.get $l0
                    i32.const 1273
                    i32.gt_s
                    select
                    i32.store
                    return
                  end
                  i32.const 0
                  local.set $l0
                  i32.const 1040
                  i32.load
                  i32.const 20
                  i32.ne
                  if $I21
                    i32.const 1040
                    i32.const 20
                    i32.store
                  end
                  i32.const 1054
                  i32.load16_u
                  if $I22
                    loop $L23
                      local.get $l0
                      i32.const 65535
                      i32.and
                      local.get $l0
                      i32.const 1048
                      i32.load
                      i32.add
                      i32.const 255
                      i32.and
                      local.tee $l1
                      call $neowasm.WheelR
                      local.get $l1
                      call $neowasm.WheelG
                      local.get $l1
                      call $neowasm.WheelB
                      call $neowasm.setPixelColor
                      local.get $l0
                      i32.const 1
                      i32.add
                      local.tee $l0
                      i32.const 1054
                      i32.load16_u
                      i32.lt_u
                      br_if $L23
                    end
                  end
                  call $neowasm.show
                  i32.const 1048
                  i32.const 0
                  i32.const 1048
                  i32.load
                  local.tee $l0
                  i32.const 1
                  i32.add
                  local.get $l0
                  i32.const 253
                  i32.gt_s
                  select
                  i32.store
                  return
                end
                i32.const 0
                i32.const 0
                i32.const 127
                call $f11
                return
              end
              i32.const 127
              i32.const 0
              i32.const 0
              call $f11
              return
            end
            i32.const 127
            i32.const 127
            i32.const 127
            call $f11
            return
          end
          i32.const 0
          i32.const 0
          i32.const 255
          call $f10
          return
        end
        i32.const 0
        i32.const 255
        i32.const 0
        call $f10
        return
      end
      i32.const 255
      i32.const 0
      i32.const 0
      call $f10
    end)
  (memory $memory 1)
  (export "memory" (memory 0))
  (export "_start" (func $_start))
  (export "setup" (func $setup))
  (export "loop" (func $loop))
  (data $d0 (i32.const 1056) "\0astrandtest_nodelay ... start\00strandtest_nodelay ... loop\00\0a"))
