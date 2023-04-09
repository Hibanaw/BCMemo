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

void app(char *uid){
    while(1){
        int signal = 0;
        MemoEditor me;
		mouse_hide();
		debug(LOG, "Main app starts.");
        // animation_login();
		setfillstyle(1, _WHITE);
		bar(0, 0, MAXWIDTH, MAXHEIGHT);
        setfillstyle(1, hexfffbf0);
		bar(0, 0, MAXWIDTH, 40);
        image_render("res/img/logotxt.bin", 85, 5);
        setfillstyle(1, hexfffbf0);
		bar(0, 0, 75, MAXHEIGHT);
        setcolor(hexd4dfff);
        setlinestyle(0, 0, 5);
        line(73, 0, 73, MAXHEIGHT);
        ime_draw();
        mouse_show();
        digitalClock_getTime();
        me = memoEditor_new("etc/1.mem", uid);
        while(1){
            int k = bioskey(1);
            int mes = 0;
            Mouse *m = mouse();
            keybord_eat();
            mouse_update();
            ime_check();
            digitalClock_getTime();
            mes = memoEditor_event(&me);
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = -1;
                break;
            }
            switch (mes){
				case 1:
                    signal = 1;
                    break;
            
                default:
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