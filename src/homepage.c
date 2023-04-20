/**
 * @file homepage.c
 * @author wywgwt (2504133124@qq.com), Hibanaw Hu (hibanaw@qq.com)
 * @brief
 * @date 2023-02-12
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "homepage.h"

void homepage()
{
    char textInputBuffer1[50];
    char textInputBuffer2[50];
    memset(textInputBuffer1, 0, sizeof(textInputBuffer1));
    memset(textInputBuffer2, 0, sizeof(textInputBuffer2));
    mouse_hide();
    setfillstyle(1, _BLACK);
    bar(0, 0, MAXWIDTH, MAXHEIGHT);
    delay(1000);
    animation_homepage1();
    setfillstyle(1, hexaa3f00);
    bar(0, 0, MAXWIDTH, MAXHEIGHT);
    image_render("res\\img\\hpbg.bin", 0, 0);
    animation_homepage2();
    setfillstyle(1, hexd4bfaa);
    bar(315, 0, MAXWIDTH, MAXHEIGHT);
    mouse_show();
    while (1)
    {
        Text tw;
        Text tw1;
        Text tc1, tc2, tc3;
        int signal = 0;
        Button b = button_new(640, 550,
                              760, 600,
                              "µÇÂ¼",
                              button_drawWINUI);
        TextInput t = textinput_newDefault(
                        "ÇëÊäÈëÓÃ»§Ãû",
                        550, 370,
                        850, 420,
                        textInputBuffer1);
        TextInput t1 = textinput_newDefault(
                        "ÇëÊäÈëÃÜÂë",
                        550, 450,
                        850, 500,
                        textInputBuffer2);
        Button exitButton = button_newExitButton();
        t1.textbox.maxLength = 8;
        t.textbox.maxLength = 8;
        tw = text_newDefault("ÓÃ»§Ãû¹ý¶Ì£¡", 700, 410, 1000, 460);
        tw.font.fontColor = _RED;
        tw1 = text_newDefault("ÃÜÂë¹ý¶Ì£¡", 700, 510, 1000, 560);
        tw1.font.fontColor = _RED;
        tc1 = text_newDefault("»¶Ó­µÇÂ¼£¡", 600, 560, 1000, 610);
        tc1.font.fontColor = _RED;
        tc2 = text_newDefault("ÃÜÂë´íÎó£¡", 600, 560, 1000, 610);
        tc2.font.fontColor = _RED;
        tc3 = text_newDefault("×¢²á³É¹¦£¡", 600, 560, 1000, 610);
        tc3.font.fontColor = _RED;
        // draw
        mouse_hide();
        image_render("res\\img\\hpf.bin", 0, 0);
        button_draw(&b);
        textinput_drawDefault(&t);
        textinput_drawDefault(&t1);
        ime_draw();
        button_draw(&exitButton);
        mouse_show();
        digitalClock_getTime();
        // event
        while (!signal)
        {
            int k, bs, tbs, tbs1, lgs, ebs;
            int ly = 3;
            Mouse *m = mouse();
            mouse_update();
            digitalClock_getTime();
            ime_check();
            keybord_eat();
            k = bioskey(1);
            bs = button_event(&b);
            tbs = textbox_event(&t.textbox);
            tbs1 = textbox_event(&t1.textbox);
            ebs = button_event(&exitButton);
            if (keybord_isESCAPE(k))
            {
                bioskey(0);
                signal = -1;
                break;
            }
            if(ebs){
                signal = -1;
                break;
            }
            if (bs || ((tbs == 1) && (tbs1 == 1)))
            {
                if (bs)
                {
                    ly = length_judge(t.textbox.content, t1.textbox.content);
                    if (ly == 3)
                    {
                        lgs = user_login(t.textbox.content, t1.textbox.content,0);
                        switch (lgs)
                        {
                        case 4:
                            text_display(tc1);
                            delay(100);
                            strcpy(appData()->uid[0],t.textbox.content);
                            appData()->currentUser = appData()->uid[0];
                            signal = 1;
                            break;
                        case 5:
                            text_display(tc2);
                            delay(100);
                            break;
                        case 6:
                            text_display(tc3);
                            user_login(t.textbox.content,t1.textbox.content,1);
                            strcpy(appData()->uid[0],t.textbox.content);
                            appData()->currentUser = appData()->uid[0];
                            delay(100);
                            signal = 1;
                            break;
                        }
                        break;
                    }
                }
            }
            switch (ly)
            {
            case 0:
                if (!(textbox_event(&t)))
                {
                    text_display(tw);
                }
                if (!(textbox_event(&t1)))
                {
                    text_display(tw1);
                }
                break;
            case 1:
                if (!(textbox_event(&t)))
                {
                    text_display(tw);
                }
                break;
            case 2:
                if (!(textbox_event(&t1)))
                {
                    text_display(tw1);
                }
                break;
            }
        }
        switch (signal)
        {
        case 1:
            app();
            break;
        case -1:
            debug(DEBUG, "EXIT.");
            return;
            break;
        }
    }
}