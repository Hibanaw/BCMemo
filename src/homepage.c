/**
 * @file homepage.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "homepage.h"

void homepage(){
    while(1){
        int signal = 0;
		//draw
		string bg = "res\\img\\hpbg.bin";

		log(LOG, "Homepage starts.");
		mouse_setVisibility(1);
        image_render(bg, 0, 0);
        
        //event
        mouse_pageUpdate();
        while(1){
			int k = keybord_getKey();
            Mouse *m = mouse();
			if(keybord_isESCAPE(k)) return;
			mouse_update();
			if(m->click == ClickLeft){
                signal = 1;
                break;
            }
        }
        switch (signal){
        case 1:
            log(DEBUG, "Jump to app.");
            app_init();
            app();
            break;
        default:
            log(DEBUG, "EXIT.");
            break;
        }
    }
    
}