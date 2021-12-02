#include <sys/time.h>
#include <stdio.h>
int main() {
  struct timeval num; 
  num.tv_sec = 0;num.tv_usec = 0;
  long int usecond=500000;
  printf("time-test starts begin = %ld\n",num.tv_sec);
  do
  {
    gettimeofday(&num,NULL);
    if(usecond<10000000*num.tv_sec+num.tv_usec){
      printf("sec:%d  usec:%d\n",num.tv_sec,num.tv_usec);
      usecond+=500000;
    }
  } while(1);
}
