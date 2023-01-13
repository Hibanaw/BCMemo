#include"log.h"

/**
 * @brief ����̨���log
 * 
 * @param str ��ʽ��
 * @param type log����
 * @param ... ������
 * @return int �Ƿ����
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