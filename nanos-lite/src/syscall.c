#include <common.h>
#include "syscall.h"

extern int fs_open(const char */*, int flags, mode_t mode*/);
extern size_t fs_lseek(int fd, size_t offset, int whence);
extern size_t fs_read(int,void *,size_t);
extern size_t fs_write(int,const void*,size_t);
extern int fs_close(int);
int sys_yield(){
  yield();
  return 0;
}
void sys_exit(uintptr_t ret){
  halt(ret);
}
int sys_open(const char *pathname){
  int res=fs_open(pathname);
  return res;
}
int sys_read(int fd, void*buf, size_t count){
  int res = fs_read(fd, buf, count);
  return res;
}
int sys_write(int fd,const void *buf, size_t count){
  if(fd==1||fd==2){
    for(int i = 0;i < count;i++){
      putch(((char*)buf)[i]);
    }
    return count;
  }
  int res = fs_write(fd, buf, count);
  return res;
}
size_t sys_lseek(int fd, size_t offset, int whence){
  size_t res = fs_lseek(fd, offset, whence);
  return res;
}
int sys_close(int fd){
  int res = fs_close(fd);
  return res;
}
//static intptr_t brk;
int sys_brk(int addr){
  //brk=addr;
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
    case SYS_exit:printf("exit\n");sys_exit(a[1]);break;
    case SYS_yield:c->GPRx=sys_yield();break;
    case SYS_open:c->GPRx=sys_open((const char*)(a[1]));break;
    case SYS_lseek:c->GPRx=sys_lseek(a[1],a[2],a[3]);break;
    case SYS_read:c->GPRx=sys_read(a[1],(void*)(a[2]),a[3]);break;
    case SYS_write:c->GPRx=sys_write(a[1],(void*)a[2],a[3]);break;
    case SYS_close:c->GPRx=sys_close(a[1]);break;
    case SYS_brk:c->GPRx=sys_brk(a[1]);break;
    default: panic("Unhandled syscall ID = %d", a[0]);
  }
}

