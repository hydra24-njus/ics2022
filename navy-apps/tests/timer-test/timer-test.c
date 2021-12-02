#include <stdio.h>
#include <sys/time.h>
#include <assert.h>

int main() {
  struct timeval num; 
  num.tv_sec = 0;
  printf("time-test starts begin = %d\n",num.tv_sec);
  while(1)
  {
    while(num.tv_usec%1000000==500000)
    {
      int t = gettimeofday(&num,NULL);
    }
    printf("sec=%d usec%d\n",num.tv_sec,num.tv_usec);
  } 
}
