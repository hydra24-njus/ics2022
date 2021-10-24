#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)

//参考了stdio库函数



int printf(const char *fmt, ...) {
  panic("Not implemented");
}

//使用参数列表fmt发送格式化输出到out
int vsprintf(char *out, const char *fmt, va_list ap) {
  panic("Not implemented");
}
//发送指定内容到out所指的字符串
int sprintf(char *out, const char *fmt, ...) {
    va_list args;
	int val=0;
	//这里对参数进行解构，将输出存入out在sprintf中完成。
	va_start(args, fmt);
	val = vsprintf(out, fmt, args);//to be completed
	va_end(args);

	return val;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
