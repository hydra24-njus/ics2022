.globl  _start
_start:
  move s0, zero
  sw a5,(sp)
  jal call_main
