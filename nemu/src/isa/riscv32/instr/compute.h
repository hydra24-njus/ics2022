def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
}
def_EHelper(xor){
  rtl_xor(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(or){
  rtl_xor(s,ddest,id_src1->preg,id_src2->preg);
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
def_EHelper(andi){
  rtl_andi(s,ddest,id_src1->preg,id_src2->imm);
}
def_EHelper(slli){
  rtl_slli(s,ddest,id_src1->preg,id_src2->imm);
}
def_EHelper(srli){
  rtl_srli(s,ddest,id_src1->preg,id_src2->imm);
}
def_EHelper(xori){
  rtl_xori(s,ddest,id_src1->preg,id_src2->imm);
}
def_EHelper(sltiu){
  rtl_li(s,ddest, interpret_relop(RELOP_LTU, *id_src1->preg, id_src2->imm));
}
def_EHelper(sll){
  rtl_zext(s,t0,id_src2->preg,5);
  rtl_sll(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(slt){
  rtl_li(s,ddest, interpret_relop(RELOP_LT, *id_src1->preg, *id_src2->preg));
}
def_EHelper(sltu){
  rtl_li(s,ddest, interpret_relop(RELOP_LTU, *id_src1->preg, *id_src2->preg));
}
def_EHelper(auipc){
  rtl_addi(s,ddest,&cpu.pc,id_src1->imm);
}