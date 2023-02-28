/**
 * @file init.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "init.h"

void init(){
	initsvga256();
    useRGB256Colors();
	mouse_init();
	return ;
}

void destruct(){
	closesvga256();
}