#include <sys/time.h>
#include <stdio.h>
int main() {
  struct timeval dut; 
  dut.tv_sec = 0;dut.tv_usec = 0;
  struct timeval ref;
  ref.tv_sec = 1;ref.tv_usec = 0;
  printf("time-test starts begin = %ld\n",dut.tv_sec);
  while(1){
    gettimeofday(&dut,NULL);
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
  }
}
