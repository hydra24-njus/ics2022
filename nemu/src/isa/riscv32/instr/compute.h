def_EHelper(lui) {
  rtl_li(s, ddest, id_src1->imm);
}
def_EHelper(xor){
  rtl_xor(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(and){
  rtl_and(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(or){
  rtl_or(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(add){
  rtl_add(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(sub){
  rtl_sub(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(mul){
  rtl_mulu_lo(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(mulh){
  rtl_muls_hi(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(div){
  rtl_divs_q(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(divu){
  rtl_divu_q(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(rem){
  rtl_divs_r(s,ddest,id_src1->preg,id_src2->preg);
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
def_EHelper(srai){
  rtl_srai(s,ddest,id_src1->preg,id_src2->imm);
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
def_EHelper(srl){
  rtl_srl(s,ddest,id_src1->preg,id_src2->preg);
}
def_EHelper(sra){
  rtl_sra(s,ddest,id_src1->preg,id_src2->preg);
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