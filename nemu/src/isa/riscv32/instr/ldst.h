def_EHelper(lw) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 4);
}
def_EHelper(lh) {
  rtl_lm(s, ddest, dsrc1, id_src2->imm, 2);
  rtl_sext(s,ddest,ddest,16);
}
def_EHelper(sw) {
  rtl_sm(s, ddest, dsrc1, id_src2->imm, 4);
}
