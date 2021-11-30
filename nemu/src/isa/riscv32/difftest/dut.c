#include <isa.h>
#include <cpu/difftest.h>
#include "../local-include/reg.h"
extern const char *regs[];
bool isa_difftest_checkregs(CPU_state *ref_r, vaddr_t pc) {
  
  for (int i = 0; i < 32; i++) {
    /*if (ref_r->gpr[i]._32 != gpr(i)) {
      printf("%s.ref=%-15u%s.nemu=%u\n",regs[i],ref_r->gpr[i]._32,regs[i],gpr(i));
      return false;
    }*/
    if(!difftest_check_reg(regs[i],ref_r->pc,ref_r->gpr[i]._32,gpr(i))){
      printf("%x,%x,%x,%x\n",ref_r->mepc,ref_r->mcause,ref_r->mstatus,ref_r->mtvec);
      printf("%x,%x,%x,%x\n",cpu.mepc,cpu.mcause,cpu.mstatus,cpu.mtvec);
      return false;
    }
  }
  if (ref_r->pc != cpu.pc){
    printf("%p,%p,%p,%p\n",&ref_r->mepc,&ref_r->mcause,&ref_r->mstatus,&ref_r->mtvec);
    printf("%p,%p,%p,%p\n",&cpu.mepc,&cpu.mcause,&cpu.mstatus,&cpu.mtvec);
    Log("PC is different after executing instruction, right = " FMT_WORD ", wrong = " FMT_WORD, ref_r->pc, cpu.pc);
    return false;
  }
  return true;
}

void isa_difftest_attach() {
}
