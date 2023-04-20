/**
 * @file addimage.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "addimage.h"

int addImage(char *path){
    while(1){
        int signal = 0;
        Button b = button_new(680, 150, 770, 190, "插入", button_drawWINUIAccent);
        Button bb = button_new(570, 150, 660, 190, "取消", button_drawWINUI);
        TextInput t = textinput_newDefault(
                    "请输入图片路径", 
                    320, 100,
                    780, 140,
                    path);
                    
        Text terror = text_newSmall("路径不合法",
            690, 110
        );
        terror.font.fontColor = _RED;
        t.textbox.font.fontSize = 16;
        t.textbox.maxLength = 20;
        mouse_hide();
        setfillstyle(1, hexfffbf0);
        bar(300, 72, 800, 200);
        button_draw(&b);
        button_draw(&bb);
        textinput_drawDefault(&t);
        mouse_show();
        while(!signal){
            int k = bioskey(1);
            int bs = 0, bbs = 0, ts = 0;
            keybord_eat();
            ime_check();
            digitalClock_getTime();
            mouse_update();
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = -1;
            }
            ts = textinput_event(&t);
            bs = button_event(&b);
            bbs = button_event(&bb);
            if(bbs){
                signal = -1;
            }
            if(bs || ts==1){
                if(image_illegal(path)){
                    text_display(terror);
                    continue;
                }
                else
                signal = 1;
            }
        }
        switch (signal)
        {
        case -1:
            return 1;
            break;
        
        case 1:
            
                return 0;
            break;
        }
    }
    
}