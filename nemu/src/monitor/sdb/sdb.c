#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include<memory/vaddr.h>
static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}
static int cmd_help(char *args);
static int cmd_q(char *args) {
  return -1;
}

//单步执行
static int cmd_si(char *args) {
  int step=1;
  if(args==NULL)step=1;
  else sscanf(args,"%d",&step);
  //printf("%s\t%d\n",args,step);
  cpu_exec(step);
  return 0;
}


//打印程序状态
static int cmd_info(char *args) {
  if(args==NULL){
    printf("too few arguments.\n");
    return 1;
  }
  char *arg=strtok(args," ");
  printf("%s\n",arg);
  if(strcmp(arg,"r")==0){
    isa_reg_display();
  }
  //print watchpoint
  if(strcmp(arg,"w")==0){
    //to be completed.
  }
  return 0;
}
//扫描内存
static int cmd_x(char *args) {
  int n=atoi(strtok(args," "));
  char* expr=strtok(NULL," ");
  int addr;
  sscanf(expr,"0x%x",&addr);
  
  for(int i=0;i<n;i++){
  printf("0x%08x\t",vaddr_read(addr+i*4,4));
  printf("0x %02x %02x %02x %02x\n",vaddr_read(addr+i*4+3,1),vaddr_read(addr+i*4+2,1),vaddr_read(addr+i*4+1,1),vaddr_read(addr+i*4,1));
  }
  return 0;
}
//表达式求值
static int cmd_p(char *args) {
  cpu_exec(-1);
  return 0;
}
//设置监视点
static int cmd_w(char *args) {
  cpu_exec(-1);
  return 0;
}
//删除监视点
static int cmd_d(char *args) {
  cpu_exec(-1);
  return 0;
}

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display informations about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
  { "si", "单步执行", cmd_si },
  { "info", "打印程序状态", cmd_info },
  { "x", "扫描内存", cmd_x },
  { "p", "表达式求值", cmd_p },
  { "w", "设置监视点", cmd_w },
  { "d", "删除监视点", cmd_d },

  /* TODO: Add more commands */

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
