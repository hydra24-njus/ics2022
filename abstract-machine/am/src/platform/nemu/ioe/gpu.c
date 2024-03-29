#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)
#define W 400
#define H 300


void __am_gpu_init(){

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
  uint32_t *pixel=ctl->pixels;
  for(int i=0;i<ctl->h;i++){
    for(int j=0;j<ctl->w;j++){
      fb[(ctl->y+i)*W+ctl->x+j]=pixel[ctl->w*i+j];
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
