/**
 * @file auth.h
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef __AUTH_H__
#define __AUTH_H__

enum AuthType{
    AUTHPRIVATE,
    AUTHPUBLIC,
    AUTHWHITELIST
};

typedef char AuthUser[30];

typedef struct
{
    AuthUser owner;
    enum AuthType type;
    
}Auth;

int auth_check(char *filename, char *uid);
int auth_set(char *filename, char * uid, enum AuthType type);

#include <stdio.h>
#include <string.h>

#endif