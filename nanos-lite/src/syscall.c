#include <common.h>
#include "syscall.h"

int sys_yield(){
  yield();
  return 0;
}
void sys_exit(uintptr_t ret){
  halt(ret);
}
int do_write(int fd, const void*buf, size_t count){   
    if(fd==1 || fd==2){
        for(int i = 0;i < count;i++){
            putch(((char*)buf)[i]);
        }
        return count;
    }
    if(fd==0)return 0;
  return 0;
}
void do_syscall(Context *c) {
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  //printf("%u\n",a[0]);
  switch (a[0]) {
    case SYS_exit:printf("%d\n",a[1]);sys_exit(a[1]);break;
    case SYS_yield:c->GPRx=sys_yield();break;
    case SYS_write:c->GPRx = do_write(a[1], (void*)(a[2]), a[3]);break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}

