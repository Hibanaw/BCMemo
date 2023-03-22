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
        Button b = {
            550, 500,
            850, 550,
            ButtonDefault
		};
        Textbox t = {
			"Input your username here.",
            550, 400,
            850, 450,
        };
		//draw
		log(LOG, "Homepage starts.");
        image_render("res\\img\\hpbg.bin", 0, 0);
        image_render("res\\img\\hpf.bin", 0, 0);
		button_draw(&b);
        textbox_draw(&t);
        //event
        while(1){
			int k, bs;
            Mouse *m = mouse();
            mouse_update();
			k = keybord_getKey();
			bs = button_event(&b);
            if(keybord_isESCAPE(k)){
                signal = -1;
                break;
            }
			if(bs){
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
        case -1:
            log(DEBUG, "EXIT.");
            return;
            break;
        }
    }
    
}