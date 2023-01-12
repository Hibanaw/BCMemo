#ifndef _LOG_H_

#define _LOG_H_
#include<stdio.h>


typedef enum{LOG, DEBUG, ERROR} logtype;

void log(char *c, logtype type = LOG); //输出log，传入类型和内容
void errorlog(char *e); //log出错误，传入错误内容

#endif