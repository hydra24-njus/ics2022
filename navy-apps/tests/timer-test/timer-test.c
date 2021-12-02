#include <sys/time.h>

int main() {
  struct timeval num; 
  num.tv_sec = 0;
  int second=1;
  int usecond=500000;int flag=1;
  printf("time-test starts begin = %ld\n",num.tv_sec);
  do
  {
    gettimeofday(&num,NULL);
    if(second==num.tv_sec&&num.tv_sec<500000&&flag==0){
      printf("sec:%d usec:%d\n",num.tv_sec,num.tv_usec);
      flag=1;
    }
    if(second==num.tv_sec&&num.tv_sec>500000&&flag==1){
      printf("sec:%d usec:%d\n",num.tv_sec,num.tv_usec);
      flag=0;
      second++;
    }
  } while(1);
}
