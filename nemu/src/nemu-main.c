#include <common.h>

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
char *ReadData(FILE *fp, char *buf)
{
return fgets(buf, 35399, fp);//读取一行到buf
}
void someprocess(char *buf)
{
printf("%s\n", buf);//这里的操作你自己定义
}



void init_monitor(int, char *[]);
void am_init_monitor();
void engine_start();
int is_exit_status_bad();

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
#ifdef CONFIG_TARGET_AM
  am_init_monitor();
#else
  init_monitor(argc, argv);
#endif

char buf[35399], *p;
FILE *fp =fopen("/home/ics2021/nemu/tools/gen-expr/input","r");

while (1) {
p = ReadData(fp, buf);//每次调用文件指针fp会自动后移一行
if (!p)//文件读取结束则跳出循环
break;
someprocess(buf);
}



  /* Start engine. */
  engine_start();
  return is_exit_status_bad();
}
