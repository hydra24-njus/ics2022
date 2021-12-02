#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include <NDL.h>

int main() {
  struct timeval num; 
  num.tv_sec = 0;
  printf("time-test starts begin = %d\n",num.tv_sec);
  while(1)
  {
    while(num.tv_sec <= sec)
    {
      int t = gettimeofday(&num,NULL);
    }
    printf("sec=%d usec%d\n",num.tv_sec,num.tv_usec);
  } 
}
