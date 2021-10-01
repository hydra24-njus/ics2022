#ifndef __SDB_H__
#define __SDB_H__

#include <common.h>

word_t expr(char *e, bool *success);

typedef struct watchpoint {
  int NO;//监视点序号
  struct watchpoint *next;//指针
  char wexpr[36355];//表达式
  uint32_t lastval;//表达式最近一次的值
  /* TODO: Add more members if necessary */

} WP;
WP* new_wp();
void free_wp(WP *wp);


#endif
