#include "cpu/exec.h"
def_EHelper(csrrw){
    uint32_t t;
  switch(id_src2->imm){
      case 0x300:/*mstatus*/t=cpu.mstatus;cpu.mstatus=*id_src1->preg;*ddest=t;break;
      case 0x305:/*mtvec*/t=cpu.mtvec;cpu.mtvec=*id_src1->preg;*ddest=t;break;
      case 0x341:/*mepc*/t=cpu.mepc;cpu.mepc=*id_src1->preg;*ddest=t;break;
      case 0x342:/*mcause*/t=cpu.mcause;cpu.mcause=*id_src1->preg;*ddest=t;break;
      break;
  }
}
def_EHelper(csrrs){
    uint32_t t;
  switch(id_src2->imm){
      case 0x300:/*mstatus*/t=cpu.mstatus;cpu.mstatus=*id_src1->preg|t;*ddest=t;break;
      case 0x305:/*mtvec*/t=cpu.mtvec;cpu.mtvec=*id_src1->preg|t;*ddest=t;break;
      case 0x341:/*mepc*/t=cpu.mepc;cpu.mepc=*id_src1->preg|t;*ddest=t;break;
      case 0x342:/*mcause*/t=cpu.mcause;cpu.mcause=*id_src1->preg|t;*ddest=t;break;
      break;
  }
}
def_EHelper(ecall){
  *t0=isa_raise_intr(11,cpu.pc-4);
  rtl_jr(s,t0);
}
def_EHelper(mret){
  s->dnpc=cpu.mepc+8;
}