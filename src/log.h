#include<stdio.h>


typedef enum{LOG, DEBUG, ERROR} logtype;

void log(logtype type = LOG,char *c); //输出log，传入类型和内容
void errorlog(char *e); //输出错误，传入错误内容