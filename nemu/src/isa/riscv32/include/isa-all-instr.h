#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(add) f(sub) f(slt) f(sltu) f(xor) f(or) f(sll) f(mul) f(div) f(divu) f(rem)\
f(addi) f(sltiu) f(auipc) f(andi) f(slli) f(srli) f(srai) f(xori)\
f(jal) f(jalr)\
f(lui) f(lw) f(lh) f(lhu) f(lb) f(lbu)\
f(sw) f(sh) f(sb)\
f(inv)\
f(beq) f(bne) f(bge) f(bgeu) f(blt) f(bltu)\
f(nemu_trap)

def_all_EXEC_ID();
