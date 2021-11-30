#include <common.h>
#include "syscall.h"

extern int sys_yield();
extern void sys_exit(uintptr_t);

void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  //printf("%u\n",a[0]);
  switch (a[0]) {
    case 0:sys_exit(a[1]);break;
    case 1:c->GPRx=sys_yield();break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}

