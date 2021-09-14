#include <isa.h>
#include<memory/vaddr.h>
/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256, TK_EQ,TK_ADDR,TK_HEX,TK_NUM,

  /* TODO: Add more token types */

};

static struct rule {
  const char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */
  //根据查询的优先级顺序填写。
  {"\\*0x[0-9a-fA-F]+",TK_ADDR},    //地址（十六进制）
  {"\\0x[0-9a-fA-F]+",TK_HEX},     //十六进制数
  {"[0-9]+",TK_NUM},    //十进制数字
  //reg
  {" +", TK_NOTYPE},    // spaces
  {"\\+",'+'},         // plus
  {"\\-",'-'},
  {"\\*",'*'},
  {"\\/",'/'},
  {"\\%",'%'},
  {"\\(",'('},
  {"\\)",')'},


};

#define NR_REGEX ARRLEN(rules)

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    // 这个函数把指定的正则表达式rules[i].regex编译成一种特定的数据格式re[i]，
    // regexec这样可以使匹配更有效。执行成功返回０。 
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;
  
  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        //  一旦用regcomp()成功地编译了正则表达式，接下来就可以调用regexec()完成模式匹配：
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */
        //按顺序匹配type，猜测nr_token用于计数
        switch (rules[i].token_type){
        case TK_NOTYPE:
          break;
        default:
          tokens[nr_token].type = rules[i].token_type;
          strncpy(tokens[nr_token].str,substr_start,substr_len);
          //printf("%s\n",tokens[nr_token].str);
          nr_token++;
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

bool Match_Error=false;

//括号匹配函数，判断一个字串是否被括号包裹
bool check_p(int p,int q){
  //前后是否都是括号
  if(tokens[p].type!='('||tokens[q].type!=')'){
    return false;
  }

  else{
    //从左至右遍历，同时记录括号的数量，左括号++，右括号--。如果在中途变为0则说明不匹配。
    int count=0;
    for(int i=p;i<=q;i++){
      if(count==0&&i!=p&&i!=q)return false;
      if(tokens[i].type=='(')count++;
      else if(tokens[i].type==')')count--;
    }
    if(count==0)return true;
  }
  Match_Error=false;
  return false;
}

//寻找与右括号对应的左括号
int find_pp(int p,int q){
  //输入非法-->最右侧不是')'
  if(tokens[q].type!=')'){
    return -1;
  }
  int cnt=1;
  for(int i=q-1;i>=p;i++){
    if(tokens[i].type==')')cnt++;
    else if(tokens[i].type=='(')cnt--;
    if(cnt==0)return i;
  }
  //表达式不正确-->没有与之匹配的左括号
  return -2;
}

//设定优先级
int set_level(int i){
  if(tokens[i].type=='+')return 1;
  else if(tokens[i].type=='-')return 1;
  else if(tokens[i].type=='*')return 10;
  else if(tokens[i].type=='/')return 10;
  return 100;
}

//寻找主运算符 从右至左优先级最低的符号
int find_main_poerator(int p,int q){
  int op_location=p;
  int op_level=100;
  for(int i=q;i>=p;i--){
    //括号内一定不是。
    if(tokens[i].type==')'){
      int pair_p=0;
      while(pair_p){
        if(tokens[i].type==')')pair_p++;
        else if(tokens[i].type=='(')pair_p--;
        i--;
      }
    }
    //数字一定不是
    else if(tokens[i].type==TK_NUM||tokens[i].type==TK_ADDR||tokens[i].type==TK_HEX)continue;
    else{
      if(set_level(i)<op_level){
        op_level=set_level(i);
        op_location=i;
      }
    }
  }
  return op_location;
}

int eval(int p,int q){
  int ans;
  if(p>q);
  else if(p==q){
    if(tokens[p].type==TK_NUM){
      sscanf(tokens[p].str,"%d",&ans);
      return ans;

    }
    else if(tokens[p].type==TK_HEX){
      sscanf(tokens[p].str,"0x%x",&ans);
      return ans;
    }
    else if(tokens[p].type==TK_ADDR){
      sscanf(tokens[p].str,"*0x%x",&ans);
      return vaddr_read(ans,1);
    }
    //其他规则（寄存器等）待添加


  }
    //判断是否括号
  else if(check_p(p,q)){
      return eval(p+1,q-1);
  }
  //寻找主运算符并递归求解
  else{
      int i=find_main_poerator(p,q);
      switch(tokens[i].type){
        case '+':
        return eval(p,i-1)+eval(i+1,q);
        case '-':
        return eval(p,i-1)-eval(i+1,q);
        case '*':
        return eval(p,i-1)*eval(i+1,q);
        case '/':
        return eval(p,i-1)/eval(i+1,q);
      }
    }
  Match_Error=true;
  return -1;
}

word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }
  *success=true;
  /* TODO: Insert codes to evaluate the expression. */
  int ans=eval(0,nr_token-1);
  *success=!Match_Error;
  return ans;
}
