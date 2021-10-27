#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)
#define W 400
#define H 300


void __am_gpu_init(){
  int i;
  int w = W; // TODO: get the correct width
  int h = H; // TODO: get the correct height
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  for (i = 0; i < w * h; i++)fb[i] = i;
  outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = inw(VGACTL_ADDR+2), .height = inw(VGACTL_ADDR),
    .vmemsz = 0
  };
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  uint32_t *fb=(uint32_t*)FB_ADDR;
  int x=ctl->x,y=ctl->y,w=ctl->w,h=ctl->h;
  uint32_t *pixel=ctl->pixels;
  for(int i=0;i<h;i++){
    for(int j=0;j<w;j++){
      fb[(y+i)*W+x+j]=pixel[w*i+j];
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
