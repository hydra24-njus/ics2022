def_EHelper(jal){
  rtl_addi(s,ddest,&cpu.pc,4);
  rtl_add(s,t0,&id_src1->imm,&cpu.pc);
  rtl_j(s,*t0);
}
def_EHelper(jalr){
  rtl_addi(s,ddest,&cpu.pc,4);
  rtl_addi(s,t0,id_src1->preg,id_src2->imm);
  rtl_j(s,*t0);
}
/*def_EHelper(beq){
  
}*/