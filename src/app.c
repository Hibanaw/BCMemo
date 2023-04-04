/**
 * @file app.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-27
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "app.h"

AppData *app_data(){
    static AppData d;
    return &d;
}

void app(){
	_app_init();
    while(1){
        int signal = 0;
        AppData *ad = app_data();
        Textbox tb = textbox_newDefault("ÐÂµÄ¶ÎÂä", 120, 30, MAXWIDTH, 100);
		// Button b;
		mouse_hide();
		log(LOG, "Main app starts.");
		setfillstyle(1, _WHITE);
		bar(0, 0, MAXWIDTH, MAXHEIGHT);
        setfillstyle(1, _BLACK);
		bar(0, 0, MAXWIDTH, 20);
        setfillstyle(1, _GRAY);
		bar(0, 0, 75, MAXHEIGHT);
		textbox_draw(&tb);
        ime_draw();
        mouse_show();
        digitalClock_getTime();
        while(1){
            int k = bioskey(1);
            Mouse * m = mouse();
            keybord_eat();
            mouse_update();
            ime_check();
            textbox_event(&tb);
            digitalClock_getTime();
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = -1;
                break;
            }
        }
        switch(signal){
        case -1:
            return 0;
            break;
        }
    }
}


void _app_init(){
    AppData *ad = app_data();
    ad -> leftBar = true;
}