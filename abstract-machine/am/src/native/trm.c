#include <am.h>
#include <stdio.h>
#include<klib-macros.h>

void __am_platform_dummy();
void __am_exit_platform(int code);

void trm_init() {
  __am_platform_dummy();
}

void putch(char ch) {
  putchar(ch);
}

void halt(int code) {
  //printf("Exit (%d)\n", code);
  const char *fmt = "Exit code = 40h\n";
  for (const char *p = fmt; *p; p++) {
    char ch = *p;
    if (ch == '0' || ch == '4') {
      ch = "0123456789abcdef"[(code >> (ch - '0')) & 0xf];
    }
    putch(ch);
  }
  __am_exit_platform(code);
  //printf("Should not reach here!\n");
  putstr("Should not reach here!\n");
  while (1);
}

Area heap = {};
