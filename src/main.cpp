/**
 * @file main.cpp
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 一个使用BC构建的DOS环境下的备忘录
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
