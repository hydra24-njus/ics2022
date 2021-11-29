#include <common.h>

static Context* do_event(Event e, Context* c) {
	uint32_t i=0;
  switch (e.event) {
    case EVENT_YIELD:
    	printf("yield!\n");
    	asm volatile("csrrs %0,mepc, %0;"
    		     "addi  %0,%0,0x4;"
    		     "csrrs %0,mepc, %0;"
    	 : :"r"(i)
    	 );
    	break;
    default: panic("Unhandled event ID = %d", e.event);
  }

  return c;
}

void init_irq(void) {
  Log("Initializing interrupt/exception handler...");
  cte_init(do_event);
}
