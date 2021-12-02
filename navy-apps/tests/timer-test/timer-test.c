#include <sys/time.h>
#include <stdio.h>
int main() {
  struct timeval dut; 
  dut.tv_sec = 0;dut.tv_usec = 0;
  struct timeval ref;
  ref.tv_sec = 0;ref.tv_usec = 500000;
  printf("time-test starts begin = %ld\n",dut.tv_sec);
  do
  {
    gettimeofday(&dut,NULL);
    if(dut.tv_sec==ref.tv_sec){
      switch(ref.tv_usec){
      	case      0:if(dut.tv_usec>ref.tv_usec)printf("0.0s\n");ref.tv_usec=500000;break;
      	case 500000:if(dut.tv_usec>ref.tv_usec)printf("0.5s\n");ref.tv_usec=0;ref.tv_sec++;break;
      }
    }
  } while(1);
}
