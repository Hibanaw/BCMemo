#include"log.h"

void log(logtype type = LOG,char *c){
    char *s;
    switch(type){
        case LOG:
            printf("[log]%s", c);
            break;
        case ERROR:
            printf("[err]%s", c);
            break;
        case DEBUG:
            printf("[debug]%s", c);
            break;
    }
    return;
}

void errorlog(char *e){
    log(ERROR, e);
}