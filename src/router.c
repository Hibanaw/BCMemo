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
    return r;
}

void router_draw(Router *r){
	button_draw(&r->expandButton);
}

int router_expand(){
    while(1){
        int signal = 0;
        mouse_hide();
        bar(0, 0, 200, MAXHEIGHT);
        mouse_show();
        while(!signal){
            int k = bioskey(1);
            keybord_eat();
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