#include"log.h"

/**
 * @brief 控制台输出log
 * 
 * @param str 格式串
 * @param type log类型
 * @param ... 填充变量
 * @return int 是否被输出
 */
int log(char *str, logtype type, ...){
    va_list args;
    va_start(args, str);
    char c[101];
	vsprintf(c, str, args);
	va_end(args);
	if(LOGLEVEL <= type)
		switch(type){
			case LOG:
				printf("[log]%s\n", c);
				break;
			case ERR:
				printf("[err]%s\n", c);
				break;
			case DBG:
				printf("[debug]%s\n", c);
				break;
		}
	return LOGLEVEL <= type;
}