/**
 * @file main.cpp
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief һ��ʹ��BC������DOS�����µı���¼
 * @date 2023-01-12
 * @details encoding:gb2312
 * 
 */
#include<stdio.h>
#include"core.h"


int main(){
	init();
	while(home());
	getchar();
	close();
	return 0;
}
