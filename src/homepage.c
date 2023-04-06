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
    char textInputBuffer[50];
    memset(textInputBuffer, 0, sizeof(textInputBuffer));
    while(1){
        int signal = 0;
        Button b = button_new(550, 500,
            850, 550,
			"登 录",
			button_drawWithText);
		TextInput t = textinput_newDefault(
            "请输入用户名", 
            550, 400,
            850, 450,
            textInputBuffer);
        t.textbox.maxLength = 10;
		//draw
        mouse_hide();
		debug(LOG, "Homepage starts.");
        setfillstyle(1, hexaa3f00);
        bar(0, 0, MAXWIDTH, MAXHEIGHT);
        image_render("res\\img\\hpbg.bin", 0, 0);
        setfillstyle(1, hexd4bfaa);
        bar(315, 0, MAXWIDTH, MAXHEIGHT);
        image_render("res\\img\\hpf.bin", 0, 0);
		button_draw(&b);
        textinput_drawDefault(&t);
        ime_draw();
        mouse_show();
        digitalClock_getTime();
        //event
        while(1){
			int k, bs, tbs;
            Mouse *m = mouse();
            mouse_update();
            digitalClock_getTime();
            ime_check();
            keybord_eat();
			k = bioskey(1);
			bs = button_event(&b);
            tbs = textbox_event(&t.textbox);
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = -1;
                break;
            }
			if(bs||tbs){
                //uid check
                debug(DEBUG, "UID check.");
				if(strlen(t.textbox.content) < 3){
                    Text tw = text_newDefault("用户名过短！", 550, 460, 0, 0);
                    tw.font.fontColor = _RED;
                    text_display(tw);
                    continue;
                }
                else{
                    signal = 1;
                    break;
                }
            }
        }
        switch (signal){
        case 1:
            debug(DEBUG, "Jump to app.");
			app_data()->uid = t.textbox.content;
            app();
            break;
        case -1:
            debug(DEBUG, "EXIT.");
            return;
            break;
        }
    }
    
}
