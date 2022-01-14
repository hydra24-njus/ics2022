.globl  _start
_start:
  move s0, zero
  move a7,sp
  jal call_main
