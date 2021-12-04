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

int sys_gettimeofday(struct timeval *tv){
  tv->tv_sec = io_read(AM_TIMER_UPTIME).us / 1000000;
  tv->tv_usec = io_read(AM_TIMER_UPTIME).us % 1000000;
  return 0;
}
//TODO:添加对len的处理
size_t events_read(void *buf, size_t offset, size_t len) {
  AM_INPUT_KEYBRD_T ev = io_read(AM_INPUT_KEYBRD);
  if(ev.keycode==AM_KEY_NONE)return 0;
  sprintf(buf,"%s\t%s",keyname[ev.keycode],ev.keydown?"down":"up");
  return len;
}

size_t dispinfo_read(void *buf, size_t offset, size_t len) {
  AM_GPU_CONFIG_T gpuconfig=io_read(AM_GPU_CONFIG);
  //sscanf(dispinfo, "WIDTH: %d\nHEIGHT: %d\n", &gpuconfig.width, &gpuconfig.height);
  return sprintf(buf, "WIDTH: %d\nHEIGHT: %d\n", &gpuconfig.width, &gpuconfig.height);
}

size_t fb_write(const void *buf, size_t offset, size_t len) {
  return 0;
}
void init_device() {
  Log("Initializing devices...");
  ioe_init();
}
