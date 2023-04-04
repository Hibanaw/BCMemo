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
	//debug(LOG, "Init.");
	initsvga256();
    useRGB256Colors();
	mouse_init();
	ime_init();
	debug(DEBUG, "Init ends.");
	return ;
}

void destruct(){
	debug(LOG, "Destruct.");
	closesvga256();
}