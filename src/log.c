#include"log.h"

void log(char *c, logtype type = LOG){
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
    log(e, ERROR);
}