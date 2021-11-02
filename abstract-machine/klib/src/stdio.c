#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)


//使用参数列表fmt发送格式化输出到out
int vsprintf(char *out, const char *fmt, va_list ap) {
	int cnt=0;
	char* tmp=out;
	for(;*fmt;fmt++){
		if(*fmt!='%'){
			*tmp++=*fmt;cnt++;
			continue;
		}
		else{
			fmt++;
			switch(*fmt){
				case 's':{
					char* t=va_arg(ap,char*);
					int len=strlen(t);cnt+=len;
					for(int i=0;i<len;i++)*tmp++=*t++;
					break;
				}
				case 'd':{
					int n=va_arg(ap,int);
					if(n==0){
						*tmp++='0';cnt++;
						break;
					}
					else if(n<0){
						*tmp++='-';cnt++;
						n=-n;
					}
					char *num='\0';int i=0;
					while(n!=0){
						*num++='0'+n%10;i++;
						n/=10;
					}
					cnt+=i;
					for(;i>0;i--){
						*tmp++=*num--;
					}
					break;
				}
			}
		}
	}
	*tmp='\0';
	return cnt;
}
//利用sprintf返回的out字符串进行输出
int printf(const char *fmt, ...) {
	
	char out[1024];//上限1024个字符（应该够吧
	int len=0;
	va_list ap;
	va_start(ap,fmt);
	len=vsprintf(out,fmt,ap);
	va_end(ap);
	int i=0;
	while(out[i++]!='\0'){
		putch(out[i]);
	}
	return len;
}
//发送指定内容到out所指的字符串
int sprintf(char *out, const char *fmt, ...) {
    va_list args;
	int len=0;
	//这里对参数进行解构，将输出存入out在sprintf中完成。
	va_start(args, fmt);
	len = vsprintf(out, fmt, args);//to be completed
	va_end(args);
	return len;
}

int snprintf(char *out, size_t n, const char *fmt, ...) {
  panic("Not implemented");
}

int vsnprintf(char *out, size_t n, const char *fmt, va_list ap) {
  panic("Not implemented");
}

#endif
