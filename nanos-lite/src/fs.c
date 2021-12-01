#include <fs.h>

typedef size_t (*ReadFn) (void *buf, size_t offset, size_t len);
typedef size_t (*WriteFn) (const void *buf, size_t offset, size_t len);

typedef struct {
  char *name;
  size_t size;
  size_t disk_offset;
  ReadFn read;
  WriteFn write;
} Finfo;

enum {FD_STDIN, FD_STDOUT, FD_STDERR, FD_FB};

size_t invalid_read(void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

size_t invalid_write(const void *buf, size_t offset, size_t len) {
  panic("should not reach here");
  return 0;
}

/* This is the information about all files in disk. */
static Finfo file_table[] __attribute__((used)) = {
  [FD_STDIN]  = {"stdin", 0, 0, invalid_read, invalid_write},
  [FD_STDOUT] = {"stdout", 0, 0, invalid_read, invalid_write},
  [FD_STDERR] = {"stderr", 0, 0, invalid_read, invalid_write},
#include "files.h"
};

void init_fs() {
  // TODO: initialize the size of /dev/fb
}


//begin
//进行一些预处理
const int FD_SIZE=sizeof(file_table)/sizeof(file_table[0]);
#define check_filesize (file_table[fd].disk_offset+count>file_table[fd].size)
#define reset_count if(check_filesize)count=file_table[fd].size-file_table[fd].disk_offset
//忽略flags和mode
int fs_open(const char *pathname/*, int flags, mode_t mode*/){
  for(int i=FD_FB;i<FD_SIZE;i++){
    if(strcmp(pathname,file_table[i].name)==0)return i;
  }
  assert(0);
  return 0;
}
size_t fs_read(int fd,void *buf,size_t count){
  if(fd<3)return 0;//忽略in，out，error
  reset_count;
  
  return count;
}
int fs_close(int fd){
  file_table[fd].read=0;
  return 0;
}