#ifndef _LOG_H_

#define _LOG_H_
#include<stdio.h>


typedef enum{LOG, DEBUG, ERROR} logtype;

void log(char *c, logtype type = LOG); //���log���������ͺ�����
void errorlog(char *e); //log�����󣬴����������

#endif