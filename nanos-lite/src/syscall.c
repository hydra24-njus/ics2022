#include <common.h>
#include "syscall.h"
extern int fs_open(const char */*, int flags, mode_t mode*/);
extern size_t fs_lseek(int fd, size_t offset, int whence);
extern size_t fs_read(int,void *,size_t);
extern size_t fs_write(int,const void*,size_t);
extern int fs_close(int);
extern int sys_gettimeofday(void*);
/*int sys_write(int fd,const void *buf,size_t count){
  for(int i=0;i<count;i++){
    putch(buf++);
  }
  return count;
}*/
static char *empty_args[] = {NULL};
int sys_execve(const char *pathname,char *const argv[],char *const envp[]){
return 0;
}
void do_syscall(Context *c) {
  //Log("sys_call");
  uintptr_t a[4];
  a[0] = c->GPR1;
  a[1] = c->GPR2;
  a[2] = c->GPR3;
  a[3] = c->GPR4;
  switch (a[0]) {
    case SYS_exit:sys_execve("/bin/nterm",empty_args,empty_args);break;
    case SYS_yield:yield();break;
    case SYS_open:c->GPRx=fs_open((const char*)(a[1]));break;
    case SYS_lseek:c->GPRx=fs_lseek(a[1],a[2],a[3]);break;
    case SYS_read:/*Log("sys_call:read");*/c->GPRx=fs_read(a[1],(void*)(a[2]),a[3]);break;
    case SYS_write:/*Log("sys_write");*/c->GPRx=fs_write(a[1],(void*)a[2],a[3]);break;
    case SYS_close:c->GPRx=fs_close(a[1]);break;
    case SYS_brk:c->GPRx=0;break;
    case SYS_gettimeofday:c->GPRx=sys_gettimeofday((void *)a[1]);break;
    case SYS_execve:printf("execve\n\n");c->GPRx=sys_execve((char*)a[1],(char**)a[2],(char**)a[3]);break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}


