#include <cpu/decode.h>
#include "../local-include/rtl.h"

#define INSTR_LIST(f) f(add) f(sub) f(slt) f(sltu) f(xor) f(and) f(or) f(sll) f(srl) f(sra) f(mul) f(mulh) f(mulhu) f(div) f(divu) f(rem) f(remu)\
f(addi) f(sltiu) f(auipc) f(andi) f(slli) f(slti) f(srli) f(srai) f(ori) f(xori)\
f(jal) f(jalr)\
f(lui) f(lw) f(lh) f(lhu) f(lb) f(lbu)\
f(sw) f(sh) f(sb)\
f(inv)\
f(beq) f(bne) f(bge) f(bgeu) f(blt) f(bltu)\
f(nemu_trap)\
f(csrrw)  f(csrrs) f(ecall) 
def_all_EXEC_ID();
