#include <sys/time.h>

int main() {
  struct timeval num; 
  num.tv_sec = 0;
  int second=1;
  printf("time-test starts begin = %ld\n",num.tv_sec);
  do
  {
    gettimeofday(&num,NULL);
    if(num.tv_sec==second){
      printf("sec=%ld usec=%ld\n",num.tv_sec,num.tv_usec);
      second++;
    }
  } while(1);
}
