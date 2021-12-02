#include <sys/time.h>

int main() {
  struct timeval num; 
  num.tv_sec = 0;
  printf("time-test starts begin = %ld\n",num.tv_sec);
  do
  {
    gettimeofday(&num,NULL);
    if(num.tv_usec==500000||num.tv_usec==0)
    printf("sec=%ld usec=%ld\n",num.tv_sec,num.tv_usec);
  } while(1);
}
