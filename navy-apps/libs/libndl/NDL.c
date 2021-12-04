#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>
static int evtdev = -1;
static int fbdev = -1;
static int screen_w = 0, screen_h = 0;
static int canvas_w = 0, canvas_h = 0;
uint32_t NDL_GetTicks() {
  struct timeval tv;
  struct timezone tz;
  gettimeofday(&tv, &tz);  
  return tv.tv_usec / 1000 + 1000 * tv.tv_sec;//ms
}

int NDL_PollEvent(char *buf, int len) {
  int fd=_open("/dev/events",0,0);
  return _read(fd,buf,len);
}

void NDL_OpenCanvas(int *w, int *h) {
//猜测用于加载app，暂时忽略
  if (getenv("NWM_APP")) {
    int fbctl = 4;
    fbdev = 5;
    screen_w = *w; screen_h = *h;
    char buf[64];
    int len = sprintf(buf, "%d %d", screen_w, screen_h);
    // let NWM resize the window and create the frame buffer
    write(fbctl, buf, len);
    while (1) {
      // 3 = evtdev
      int nread = read(3, buf, sizeof(buf) - 1);
      if (nread <= 0) continue;
      buf[nread] = '\0';
      if (strcmp(buf, "mmap ok") == 0) break;
    }
    close(fbctl);
  }
  else{
    if(*w==0&&*h==0){
      char buf[64];
      _read(4,buf,64);
      sscanf(buf,"WIDTH:%d\nHEIGHT:%d\n",&canvas_w,&canvas_h);
      *w=canvas_w;*h=canvas_h;
    }
    else{
      canvas_w=*w,canvas_h=*h;
    }
    printf("%d\t%d\n",canvas_w,canvas_h);
  }
}

static uint32_t* canvas =NULL;
void NDL_DrawRect(uint32_t *pixels, int x, int y, int w, int h) {
  for(int i = 0;i < h;i ++)
    for(int j = 0;j < w;j ++)
    {
      canvas[(y+i)*canvas_w+x+j] = pixels[i*w+j];
    }
  for(int i = 0;i < canvas_h;i ++)
  {
    //printf("seek %d color = %x\n",4*((i+place_y)*screen_w+place_x),*(canvas+i*canvas_w+canvas_w/2));
    fseek(fb,4*((i+y)*screen_w+x),SEEK_SET);
    fwrite((void*)(canvas+i*canvas_w),1,4*canvas_w,fb);
  }
}

void NDL_OpenAudio(int freq, int channels, int samples) {
}

void NDL_CloseAudio() {
}

int NDL_PlayAudio(void *buf, int len) {
  return 0;
}

int NDL_QueryAudio() {
  return 0;
}

int NDL_Init(uint32_t flags) {
  if (getenv("NWM_APP")) {
    evtdev = 3;
  }
  return 0;
}

void NDL_Quit() {
}
