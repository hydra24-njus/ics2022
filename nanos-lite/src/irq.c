#include <common.h>
extern void do_syscall(Context*);
static Context* do_event(Event e, Context* c) {
printf("%x %x\n",(uint32_t)e.event>>16,((uint32_t)e.event<<16)>>16);
printf("%x %x\n",(uint32_t)c->GPR1,((uint32_t)c->GPR1<<16)>>16);
  //e.event=c->GPR1;

  switch (e.event) {
    case EVENT_YIELD:printf("yield!\n");break;
    case EVENT_SYSCALL:printf("syscall!\n");do_syscall(c);break;
    default: panic("Unhandled event ID = %d", e.event);
  }
  return c;
}



void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
