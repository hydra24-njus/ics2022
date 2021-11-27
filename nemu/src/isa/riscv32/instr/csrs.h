#include "cpu/exec.h"
def_EHelper(csrrw){
    uint32_t t;
  switch(id_src2->imm){
      case 0x300:/*mstatus*/break;
      case 0x305:/*mtvec*/t=s->isa.mtvec;s->isa.mtvec=*id_src1->preg;*ddest=t;break;
      case 0x341:/*mepc*/t=s->isa.mepc;s->isa.mepc=*id_src1->preg;*ddest=t;break;
      case 0x342:/*mcause*/t=s->isa.mcause;s->isa.mcause=*id_src1->preg;*ddest=t;break;
      break;
  }
}
def_EHelper(csrrs){
    uint32_t t;
  switch(id_src2->imm){
      case 0x300:/*mstatus*/break;
      case 0x305:/*mtvec*/t=s->isa.mtvec;s->isa.mtvec=*id_src1->preg|t;*ddest=t;break;
      case 0x341:/*mepc*/t=s->isa.mepc;s->isa.mepc=*id_src1->preg|t;*ddest=t;break;
      case 0x342:/*mcause*/t=s->isa.mcause;s->isa.mcause=*id_src1->preg|t;*ddest=t;break;
      break;
  }
}
def_EHelper(ecall){
  s->isa.mepc=cpu.pc;
  s->isa.mcause=11;
  *t0=s->isa.mtvec;
  rtl_jr(s,t0);
}