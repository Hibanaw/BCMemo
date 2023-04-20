#ifndef __USER_H__
#define __USER_H__
#include<stdio.h>
#include<string.h>
typedef struct
{
  char account[20];
  char password[20];
}Userdata;

int user_login(char *p,char *q,int k);

// void user_Datainput(char *p,char *q);

int length_judge(char *p,char *q);

#endif