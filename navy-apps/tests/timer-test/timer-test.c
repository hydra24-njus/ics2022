#include <sys/time.h>
#include <stdio.h>
#include <NDL.h>
int main() {
  struct timeval dut;struct timezone tz;
  //不使用ndl
  /*
  dut.tv_sec = 0;dut.tv_usec = 0;
  struct timeval ref;
  ref.tv_sec = 0;ref.tv_usec = 500000;
  printf("time-test starts begin = %ld\n",dut.tv_sec);
  while(1){
    gettimeofday(&dut,&tz);
    if(dut.tv_sec==ref.tv_sec){
      if(ref.tv_usec==0&&ref.tv_usec<dut.tv_usec){
        printf("sec:%d  usec:%d\n",ref.tv_sec,ref.tv_usec);
        ref.tv_usec=500000;
      }
      else if(ref.tv_usec==500000&&ref.tv_usec<dut.tv_usec){
        printf("sec:%d  usec:%d\n",ref.tv_sec,ref.tv_usec);
        ref.tv_usec=0;
        ref.tv_sec++;
      }
    }
  }*/
  
  //使用ndl
  uint32_t time_now=0;uint32_t time_ms=0;
  int sec=0;int msec=500;
  NDL_Init(0);
  while(1){
    time_now=NDL_GetTicks()/1000;
    time_ms =NDL_GetTicks()%1000;
    if(sec==time_now){
      if(msec==0&&time_us>msec){
      	printf("%d second,%d msecond.\n",sec,msec);
      	msec=500;
      }
      else if(msec==500&&time_us>msec){
        printf("%d second,%d msecond.\n",sec,msec);
        msec=0;sec++;
      }
      
    }
  }
  return 0;
}
