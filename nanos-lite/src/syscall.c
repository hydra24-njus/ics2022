#include <common.h>
#include "syscall.h"

int sys_yield(){
  yield();
  return 0;
}
void sys_exit(uintptr_t ret){
  halt(ret);
}

int sys_write(int fd,const void *buf, size_t count){
  if(fd==1||fd==2){
    for(int i=0;i<count;i++){
      putch(((char*)buf)[i]);
    }
    return count;
  }
  else if(fd==0)return 0;
  return 0;
}
static intptr_t brk;
int sys_brk(int addr){
  brk=addr;
  return 0;
}
void do_syscall(Context *c) {
  Log("sys_call\n");
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  switch (a[0]) {
    case SYS_exit:printf("exit\n");sys_exit(a[1]);break;
    case SYS_yield:c->GPRx=sys_yield();break;
    case SYS_write:c->GPRx=sys_write(a[1],(void*)a[2],a[3]);break;
    case SYS_brk:c->GPRx=sys_brk(a[1]);break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}

