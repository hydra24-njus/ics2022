#include <common.h>
#include "syscall.h"

int sys_yield();

void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  //printf("%u\n",a[0]);
  switch (a[0]) {
    case 1:c->GPRx=sys_yield();break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}

int sys_yield(){
  yield();
  return 0;
}