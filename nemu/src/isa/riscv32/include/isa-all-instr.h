#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(add) f(sub) f(sltu) f(xor) f(or)\
f(addi) f(sltiu) f(auipc)\
f(jal) f(jalr)\
f(lui) f(lw)\
f(sw) f(inv)\
f(beq) f(bne) f(bge) f(bgeu)\
f(nemu_trap)

def_all_EXEC_ID();
