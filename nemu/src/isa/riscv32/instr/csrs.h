#include "cpu/exec.h"
def_EHelper(csrrw){
    uint32_t t;
  switch(id_src2->imm){
      case 0x300:/*mstatus*/t=cpu.mstatus;cpu.mstatus=*id_src1->preg;*ddest=t;break;
      case 0x305:/*mtvec*/t=cpu.mtvec;cpu.mtvec=*id_src1->preg;*ddest=t;printf("%u\n",cpu.mtvec);break;
      case 0x341:/*mepc*/t=cpu.mepc;cpu.mepc=*id_src1->preg;*ddest=t;break;
      case 0x342:/*mcause*/t=cpu.mcause;cpu.mcause=*id_src1->preg;*ddest=t;break;
  }

}
def_EHelper(ecall){
  
}