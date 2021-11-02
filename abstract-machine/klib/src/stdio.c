#include <am.h>
#include <klib.h>
#include <klib-macros.h>
#include <stdarg.h>
#if !defined(__ISA_NATIVE__) || defined(__NATIVE_USE_KLIB__)


//使用参数列表fmt发送格式化输出到out
int vsprintf(char *out, const char *fmt, va_list ap) {
	int length;
  const char* t;
  char *str=out;
  for(; *fmt; fmt++){
    if(*fmt!='%'){
      *str++=*fmt;
      continue;
    }
    fmt++;
    switch(*fmt){
      case 's':{
        t=va_arg(ap,char*);
        length=strlen(t);
        for(int i=0;i<length;i++){
          *str++=*t++;
        }
        break;
      }
      case 'd':{
        int num=va_arg(ap,int);
        int i=0;
        char c;
        if(num==0)*str++='0';
        else{
          if(num<0){
            *str++='-';
            num=(-num);
          }
          while(num!=0){
            *str++=num%10+'0';
            i++;
            num/=10;
          }
        }
        for(int j=1;j<=(i/2);j++){
          c=*(str-j);
          *(str-j)=*(str-(i-j+1));
          *(str-(i-j+1))=c;
        }
        break;
      }
      default:break;
    }
  }
  *str='\0';
  return 0;
	/*char*tmp=out;
	for(;*fmt;fmt++){
		if(*fmt!='%'){
			*tmp++=*fmt;
			continue;
		}
			fmt++;
			switch(*fmt){
				case 's':{
					char *t=va_arg(ap,char*);
        			int len=strlen(t);
        			for(int i=0;i<len;i++){
          				*tmp++=*t++;
        			}
        			break;
				}
				case 'd':{
					int n=va_arg(ap,int);
					if(n==0){
						*tmp++='0';
						break;
					}
					else if(n<0){
						*tmp++='-';
						n=-n;
					}
					int _n=0;
					while(n!=0){
						_n+=n%10;
						_n*=10;n/=10;
					}
					while(_n!=0){
						*tmp++='0'+_n%10;
						_n/=10;
					}
					break;
				}
				default:break;
			}
	}
	*tmp='\0';
	return 0;*/
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
	while(out[i]!='\0'){
		putch(out[i++]);
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
