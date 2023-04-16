/**
 * @file router.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "router.h"

Router router_new(){
	Router r;
    memset(&r, 0, sizeof(r));
    r.expandButton = button_new(10, 20, 65, 50, "", button_drawDefault);
    r.newMemoButton = button_new(20, 600, 55, 635, "", button_drawDefault);
	sprintf(r.memoFilePath, "data\\%06ld.mem", time(NULL)%1000000);
    return r;
}

void router_draw(Router *r){
	button_draw(&r->expandButton);
}

int router_expand(Router *r){
    while(1){
        int signal = 0;
        mouse_hide();
        bar(0, 0, 350, MAXHEIGHT);
        setcolor(hexd4dfff);
        setlinestyle(0, 1, 2);
        line(350, 0, 350, MAXHEIGHT);
        button_draw(&r->expandButton);
        button_draw(&r->newMemoButton);
        mouse_show();
        digitalClock_getTime();
        while(!signal){
            int k = bioskey(1);
            keybord_eat();
            mouse_update();
            digitalClock_getTime();
            if(button_event(&r->expandButton)){
                signal = 1;
            }
            if(button_event(&r->newMemoButton)){
                signal = 2;
            }
            if(mouse_isClickedInBox(350, 0, MAXWIDTH, MAXHEIGHT) == 1){
                signal = 1;
            }
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = 1;
            }

        }
        switch (signal)
        {
        case 1:
            return 0;
            break;
        case 2:
			sprintf(r->memoFilePath, "data\\%06ld.mem", time(NULL)%1000000);
            return 0;
            break;
        default:
            break;
        }
    }
}

int router_event(Router *r){
    int k;
    if(button_event(&r->expandButton))
        return RouterExpand;
    return 0;
}