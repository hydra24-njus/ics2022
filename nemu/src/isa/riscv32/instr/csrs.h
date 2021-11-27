#include "cpu/exec.h"
def_EHelper(csrrw){
    uint32_t t;
  switch(id_src2->imm){
      case 0x300://*mstatus*/t=isa.mstatus;isa.mstatus=*id_src1->preg;*ddest=t;break;
      case 0x305:/*mtvec*/t=s->isa.mtvec;s->isa.mtvec=*id_src1->preg;*ddest=t;*id_src1->preg=1;printf("%u\n",s->isa.mtvec);break;
      case 0x341://*mepc*/t=isa.mepc;isa.mepc=*id_src1->preg;*ddest=t;break;
      case 0x342:///*mcause*/t=isa.mcause;isa.mcause=*id_src1->preg;*ddest=t;break;
      break;
  }

}
def_EHelper(ecall){
  
}