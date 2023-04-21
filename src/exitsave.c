/**
 * @file exitsave.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "exitsave.h"

int exitsave(MemoEditor *me){
    Button saveButton = button_new(690, 140, 780, 180, "����", button_drawWINUIAccent);
    Button exitButton = button_new(580, 140, 670, 180, "������", button_drawWINUI);
    Button cancelButton = button_new(470, 140, 560, 180, "ȡ��", button_drawWINUI);
    Text title = text_newDefault("����Դ��ļ����ĸ��ģ�", 320, 90, 0, 0);
    
    if(!me->unSaved){
        return -1;
    }
    mouse_hide();
    setfillstyle(1, hexfffbf0);
    bar(300, 72, 800, 190);
    button_draw(&exitButton);
    button_draw(&saveButton);
    button_draw(&cancelButton);
    text_display(title);

    mouse_show();
    while(1){
        mouse_update();
        keybord_eat();
        if(button_event(&exitButton))
            return -1;
        if(button_event(&saveButton))
            return 1;
        if(button_event(&cancelButton))
            return 0;

    }
}