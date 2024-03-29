#include "sdb.h"

#define NR_WP 32

/*typedef struct watchpoint {
  int NO;//监视点序号
  struct watchpoint *next;//指针
  char* wexpr;//表达式
  uint32_t lastval;//表达式最近一次的值
   TODO: Add more members if necessary 

} WP;*/

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
    wp_pool[i].lastval=0;
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */
WP* new_wp(char *s,bool* success){
  WP *p;
  if(free_==NULL){
    printf("watchpoint is already full\n");
    assert(0);
  }
  
  else if(head==NULL){
    
    p=free_;
    free_=free_->next;
    head=p;
    head->next=NULL;
    head->lastval=expr(s,success);
    strcpy(head->wexpr,s);
  }
  else{
    
    //p为从free释放的监视点
    p=free_;
    free_=free_->next;
    p->next=NULL;
    p->lastval=expr(s,success);
    strcpy(p->wexpr,s);
    //q为head中最后一个监视点
    WP *q=head;
    while(q->next!=NULL)q=q->next;
    q->next=p;
    
  }
  return p;
}

void free_wp(int no){
WP *p;
if(head==NULL){
  printf("watchpoint pool is empty\n");
  return;
}
//p是将被释放的监视点
else if(head->NO==no){
  p=head;
  head=head->next;
}
else{
  //q是head中p的前一个监视点
  WP *q = head;
  bool flag = false;
  while (q->next != NULL){
    if (q->next->NO == no){
      p = q->next;
      q->next = p->next;
      flag = true;
      break;
    }
    q = q->next;
  }
  if (flag == false){
    printf("no such watchpoint\n");
    return;
  }
}

//p是被释放的监视点
//添加到free中
if(free_==NULL){
  free_=p;
  free_->next=NULL;
}
else{
  WP *q=free_;
  p->next=q;
  free_=p;
}
return;
}

void info_w(){
  WP *p=head;
  if(p==NULL){
    printf("no watchpoint\n");
    return;
  }
  while(p!=NULL){
    printf("NO.%d\texpr:%s\tval:%d\n",p->NO,p->wexpr,p->lastval);
    p=p->next;
  }

}

bool check_wp(){
  WP *p=head;
  bool success=true,flag=true;
  int n;
  while(p!=NULL){
    n=expr(p->wexpr,&success);
    if(n!=p->lastval){
      printf("NO.%d\tposition:%s\toldval:%d\tnowval:%d\n",p->NO,p->wexpr,p->lastval,n);
      p->lastval=n;
      flag=false;
    }
    p=p->next;
  }
  return flag;
}