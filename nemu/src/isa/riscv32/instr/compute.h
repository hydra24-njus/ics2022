def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
}
def_EHelper(add){
  rtl_add(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(sub){
  rtl_sub(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(addi){
  rtl_addi(s,ddest,id_src1->preg,id_src2->imm);
}
def_EHelper(sltiu){
  rtl_subi(s,t0,id_src1->preg,id_src2->imm);
  rtl_srli(s,t0,t0,31);
  rtl_li(s,ddest,*t0);
}
def_EHelper(auipc){
  rtl_addi(s,ddest,&cpu.pc,id_src1->imm);
}