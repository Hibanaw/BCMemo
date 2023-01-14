#ifndef _LOG_H_

#define _LOG_H_

#define LOGLEVEL 0
#define LOGFILEMOD 1

#include<stdio.h>
#include<stdarg.h>
#include<string.h>


typedef enum{LOG, DBG, ERR} logtype;

int log(char *c, logtype type = LOG, ...); //���log���������ͺ�����
#endif