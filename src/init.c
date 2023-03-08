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
	//log(LOG, "Init.");
	initsvga256();
    useRGB256Colors();
	mouse_init();
	log(DEBUG, "Init ends.");
	return ;
}

void destruct(){
	closesvga256();
	log(LOG, "Destruct ends.");
}