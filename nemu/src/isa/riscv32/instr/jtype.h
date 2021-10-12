def_EHelper(jal){
  rtl_addi(s,ddest,&cpu.pc,4);
  rtl_add(s,t0,&id_src2->imm,&cpu.pc);
  rtl_j(s,*t0);
}