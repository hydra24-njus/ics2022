#include <stdio.h>
#include <sys/time.h>
#include <assert.h>
#include <NDL.h>

int main() {
  struct timeval num; 
  num.tv_sec = 0;
  printf("time-test starts begin = %d\n",num.tv_sec);
  int sec = 1;
  while(1)
  {
    if(num.tv_usec%5000000==0)
    printf("time: seconds = %d   sec=%d usec=%d\n",sec,num.tv_sec,num.tv_usec);
    sec++;
  } 
}
