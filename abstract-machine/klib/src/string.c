#include <klib.h>
#include <klib-macros.h>
#include <stdint.h>

#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

size_t strlen(const char *s) {
  size_t len=0;
  while(s[len]!='\0')len++;
  return len;
}

char *strcpy(char *dst, const char *src) {
  size_t i;
  for(i=0;src[i]!='\0';i++){
    dst[i]=src[i];
  }
  dst[i]='\0';
  return dst;
}

char *strncpy(char *dst, const char *src, size_t n) {
  size_t i;
  for(i=0;src[i]!='\0'&&i<n;i++){
    dst[i]=src[i];
  }
  for (; i < n; i++) dst[i] = '\0';
  return dst;
}
//直接使用ansi c函数库的代码
char *strcat(char *dst, const char *src){
  char *tmp = dst;
  while (*dst) dst++;
  while ((*dst++ = *src++) != '\0');
  return tmp;
}

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)){
    ++s1;
    ++s2;
  }
  return *s1 - *s2;
}

int strncmp(const char *s1, const char *s2, size_t n) {
  int tmp = 0;
  size_t i = 0;
  for (i = 0; *s1 && *s2 && i < n && tmp != 0; i++){
    s1++;
    s2++;
    tmp = *s1 - *s2;
  }
  return tmp;
}

void *memset(void *s, int c, size_t n) {
  panic("Not implemented");
}

void *memmove(void *dst, const void *src, size_t n) {
  panic("Not implemented");
}

void *memcpy(void *out, const void *in, size_t n) {
  panic("Not implemented");
}

int memcmp(const void *s1, const void *s2, size_t n) {
  panic("Not implemented");
}

#endif
