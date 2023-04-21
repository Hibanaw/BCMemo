/**
 * @file auth.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "auth.h"

/**
 * @brief Determine auth.
 * 
 * @param filename 
 * @param uid 
 * @return int 1 for can be open, 0 for cannot be open.
 */
int auth_check(char *filename, char *uid){
    char filePath[30];
    FILE *fp;
    Auth a;
    memset(&a, 0, sizeof(a));
    sprintf(filePath, "data\\auth\\%s.AUT", filename);
    fp = fopen(filePath, "rb");
    if (fp == NULL) {
        return -1;
    }
    else {
        fread(&a, sizeof(a), 1, fp);
        if(a.type == AUTHPUBLIC){
            fclose(fp);
            return 1;
        }
        if(a.type == AUTHPRIVATE){
            if(!strcmp(a.owner, uid)){
                fclose(fp);
                return 1;
            }
            else{
                fclose(fp);
                return 0;
            }
        }
        if(a.type == AUTHWHITELIST){
            if(!strcmp(a.owner, uid)){
                fclose(fp);
                return 1;
            }
            while(!feof(fp)){
                AuthUser user;
                memset(user, 0, sizeof(AuthUser));
                fread(user, 1, sizeof(user), fp);
                if(!strcmp(user, uid)){
                    fclose(fp);
                    return 1;
                }
            }
        }
        fclose(fp);
        return 0;
    }
}

int auth_set(char *filename, char * uid, enum AuthType type){
    char filePath[30];
    FILE *fp;
    Auth a;
    sprintf(filePath, "data\\auth\\%s.AUT", filename);
    strcpy(a.owner, uid);
    a.type = type;
    fp = fopen(filePath, "wb");
    fwrite(&a, sizeof(a), 1, fp);
    fclose(fp);
    return 0;
}

int auth_addWhiteList(char *filename, char *uid){
    char filePath[30];
    FILE *fp;
    Auth a;
    sprintf(filePath, "data\\auth\\%s.AUT", filename);
    fp = fopen(filePath, "rb+");
    if(fp == NULL){
        return -1;
    }
    fread(&a, sizeof(Auth), 1, fp);
    switch(a.type){
        case AUTHPRIVATE:
            return -1;
        case AUTHPUBLIC:
            return -1;
        case AUTHWHITELIST:{
                AuthUser usr;
                while(!feof(fp)){
                    memset(usr, 0, sizeof(AuthUser));
                    fread(&usr, sizeof(AuthUser), 1, fp);
                    if(!strcmp(usr, uid)){
                        fclose(fp);
                        return 1;
                    }
                }
                strcpy(usr, uid);
                fwrite(usr, 1, sizeof(AuthUser), fp);
            }
            break;
    }
    fclose(fp);
    return 0;
}

Auth auth_get(char *filename){
    char filePath[30];
    FILE *fp;
    Auth a;
    memset(&a, 0, sizeof(a));
    sprintf(filePath, "data\\auth\\%s.AUT", filename);
    fp = fopen(filePath, "rb");
    if (fp == NULL) {
        return a;
    }
    fread(&a, sizeof(a), 1, fp);
    fclose(fp);
    return a;
}