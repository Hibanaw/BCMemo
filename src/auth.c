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
    sprintf(filePath, "data\\auth\\%s.AUT", filename);
    fp = fopen(filePath, "rb");
    if (fp == NULL) {
        return 1;
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
            while(!feof(fp)){
                AuthUser user;
                fread(&user, sizeof(user), 1, fp);
                if(!strcmp(user, uid)){
                    fclose(fp);
                    return 1;
                }
            }
        }
        return 0;
        fclose(fp);
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
    if (fp != NULL) {
        fwrite(&a, sizeof(a), 1, fp);
        fclose(fp);
    }
    return 0;
}

int auth_addWhiteList(char *filename, char *uid){
    
}