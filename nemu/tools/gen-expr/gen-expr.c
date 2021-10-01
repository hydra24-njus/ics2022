#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  signed result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";
int cnt=0;
int choose(int n){
  return rand()%n;
}
static void gen(char s){
  buf[cnt]=s;
  cnt++;
  buf[cnt]='\0';
}
void gen_num(){
  switch(choose(10)){
    case 0:gen('0');break;
    case 1:gen('1');break;
    case 2:gen('2');break;
    case 3:gen('3');break;
    case 4:gen('4');break;
    case 5:gen('5');break;
    case 6:gen('6');break;
    case 7:gen('7');break;
    case 8:gen('8');break;
    case 9:gen('9');break;
  }
}
void gen_rand_op(){
    switch(choose(3)){
    case 0:gen('+');break;
    case 1:gen('-');break;
    case 2:gen('*');break;
    //case 3:gen('3');break;

  }
}
void gen_rand_expr() {
  switch (choose(3)) {
    case 0: gen_num(); break;
    case 1: gen('('); gen_rand_expr(); gen(')'); break;
    default: gen_rand_expr(); gen_rand_op(); gen_rand_expr(); break;
  }
}


int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);
  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    cnt=0;
    memset(buf,0,sizeof(buf));
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }
  return 0;
}
