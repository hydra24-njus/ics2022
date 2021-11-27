#include <isa.h>
#include "cpu/exec.h"
extern Decode *s;
word_t isa_raise_intr(word_t NO, vaddr_t epc) {
  /* TODO: Trigger an interrupt/exception with ``NO''.
   * Then return the address of the interrupt/exception vector.
   */
  s->isa.mepc=epc;

  return 0;
}

word_t isa_query_intr() {
  return INTR_EMPTY;
}
