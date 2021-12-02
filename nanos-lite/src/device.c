#include <common.h>
#include<sys/time.h>
#if defined(MULTIPROGRAM) && !defined(TIME_SHARING)
# define MULTIPROGRAM_YIELD() yield()
#else
# define MULTIPROGRAM_YIELD()
#endif

#define NAME(key) \
  [AM_KEY_##key] = #key,

static const char *keyname[256] __attribute__((used)) = {
  [AM_KEY_NONE] = "NONE",
  AM_KEYS(NAME)
};

size_t serial_write(const void *buf, size_t offset, size_t count) {
  for(int i = 0;i < count;i++){
    putch(((char*)buf)[i]);
  }
  return count;
}
typedef struct{
  long int sec;
  long int usec;
} timeval;
int sys_gettimeofday(timeval *tv){
  printf("%d\t%d\n",sizeof(long long int),sizeof(struct timeval));
  tv->sec = io_read(AM_TIMER_UPTIME).us / 1000000;
  tv->usec = io_read(AM_TIMER_UPTIME).us % 1000000;
  return 0;
}

size_t events_read(void *buf, size_t offset, size_t len) {
  return 0;
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  return 0;
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  return 0;
}
void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
