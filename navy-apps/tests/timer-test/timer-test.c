#include <sys/time.h>

int main() {
  struct timeval num; 
  num.tv_sec = 0;
  printf("time-test starts begin = %ld\n",num.tv_sec);
  while(0)
  {
    while(num.tv_usec%1000000==500000)
    {
      gettimeofday(&num,NULL);
    }
    printf("sec=%ld usec=%ld\n",num.tv_sec,num.tv_usec);
  } 
}
