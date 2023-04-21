/**
 * @file user.c
 * @author wywgwt (2504133124@qq.com)
 * @brief 
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "user.h"

int length_judge(char *p, char *q)
{
    if ((strlen(p) < 3) && (strlen(q) < 3))
    {
        return 0;
        // account wrong,password wrong
    }
    if ((strlen(p) < 3) && !(strlen(q) < 3))
    {
        return 1;
        // account wrong,password right
    }
    if (!(strlen(p) < 3) && (strlen(q) < 3))
    {
        return 2;
        // account right,password wrong
    }
    if (!(strlen(p) < 3) && !(strlen(q) < 3))
    {
        return 3;
    }
}
// }
// void user_Datainput(char *p, char *q)
// {
//     FILE *fp;
//     Userdata *a;
//     if ((fp = fopen("res\\user.dat", "ab+")) == NULL)
//     {
//         exit(1);
//     }
//     fseek(fp,0,2);
//     strcpy(a.account, p);
//     strcpy(a.password, q);
//     fwrite(&a, sizeof(Userdata), 1, fp);
//     fclose(fp);
// }
int user_login(char *p, char *q, int k)
{
    
    if (k == 0)
    {
        FILE *fp;
        int m = 0;
        int k;
        int signal = 0;
        Userdata a;
        if ((fp = fopen("data\\user.dat", "rb+")) == NULL)
        {
            fp = fopen("data\\user.dat", "wb+");
        }
        rewind(fp);
        while (1)
        {
            fread(&a, sizeof(Userdata), 1, fp);
            if (strcmp(a.account, p) == 0)
            {
                if (strcmp(a.password, q) == 0)
                {
                    m++;
                    k=4;
                    fclose(fp);
                    break;
                    // account right,password right
                }
                else
                {
                    m++;
                    k=5;
                    fclose(fp);
                    break;
                    // account right,password wrong
                }
            }
            if (feof(fp) != 0)
            {
                k= 6;
                fclose(fp);
                break;
            }
        }
        return k;
    }
    if (k == 1)
    {
        FILE *fp;
        Userdata a;
        if ((fp = fopen("data\\user.dat", "ab+")) == NULL)
        {
            fp=fopen("data\\user.dat","wb+");
        }
        fseek(fp, 0, 2);
        strcpy(a.account, p);
        strcpy(a.password, q);
        fwrite(&a, sizeof(Userdata), 1, fp);
        fclose(fp);
    }
}