#include <proc.h>

#define MAX_NR_PROC 4

extern void naive_uload(PCB*, const char*);
static PCB pcb[MAX_NR_PROC] __attribute__((used)) = {};
static PCB pcb_boot = {};
PCB *current = NULL;
void context_kload(PCB* create_pcb,void (*entry)(void*),void *arg);

void switch_boot_pcb() {
  current = &pcb_boot;
}

void hello_fun(void *arg) {
  int j = 1;
  while (1) {
    Log("Hello World from Nanos-lite with arg '%p' for the %dth time!", (uintptr_t)arg, j);
    j ++;
    yield();
  }
}

void init_proc() {
  context_kload(&pcb[0],hello_fun,NULL);
  context_kload(&pcb[1],hello_fun,(void*)0x114514);
  switch_boot_pcb();





  //switch_boot_pcb();

  //Log("Initializing processes...");

  // load program here
  //naive_uload(NULL,"/bin/menu");
}
static int cnt=1;
Context* schedule(Context *prev) {
  current->cp=prev;
  cnt++;
  if(cnt&1){
  current=&pcb[0];
  }
  else current=&pcb[1];
  return current->cp;
}

void context_kload(PCB* create_pcb,void (*entry)(void*),void *arg){
  Area stack={create_pcb->stack,create_pcb->stack+STACK_SIZE};
  create_pcb->cp=kcontext(stack,entry,arg);
}
