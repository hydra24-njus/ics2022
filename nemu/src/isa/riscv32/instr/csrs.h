#include "cpu/exec.h"
def_EHelper(csrrw){
  switch(id_src2->imm){
      case 0x300:/*mstatus*/*t0=cpu.mstatus;cpu.mstatus=*id_src1->preg;*ddest=*t0;break;
      case 0x305:/*mtvec*/*t0=cpu.mtvec;cpu.mtvec=*id_src1->preg;*ddest=*t0;break;
      case 0x341:/*mepc*/*t0=cpu.mepc;cpu.mepc=*id_src1->preg;*ddest=*t0;break;
      case 0x342:/*mcause*/*t0=cpu.mcause;cpu.mcause=*id_src1->preg;*ddest=*t0;break;
  }
}
def_EHelper(csrrs){
  switch(id_src2->imm){
      case 0x300:/*mstatus*/*s0=cpu.mstatus;cpu.mstatus=(*s0)|*id_src1->preg;*ddest=*s0;break;
      case 0x305:/*mtvec*/*s0=cpu.mtvec;cpu.mtvec=(*s0)|*id_src1->preg;*ddest=*s0;break;
      case 0x341:/*mepc*/*s0=cpu.mepc;cpu.mepc=(*s0)|*id_src1->preg;*ddest=*s0;break;
      case 0x342:/*mcause*/*s0=cpu.mcause;cpu.mcause=(*s0)|*id_src1->preg;*ddest=*s0;break;
  }
}
def_EHelper(ecall){
  *t0=isa_raise_intr(gpr(17),cpu.pc);
  s->dnpc=*t0;
}
def_EHelper(mret){
  rtl_j(s,cpu.mepc);
}
