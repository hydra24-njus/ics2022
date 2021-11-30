#include <common.h>
extern void do_syscall(Context*);
static Context* do_event(Event e, Context* c) {
printf("%d\n",e.event);
  e.event=c->GPR1;
  printf("%d\n",e.event);
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
