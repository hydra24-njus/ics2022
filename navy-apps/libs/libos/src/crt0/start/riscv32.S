.globl  _start
_start:
  move s0, zero
  move sp, a7
  jal call_main
