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

void app_init(){
    AppData *ad = app_data();
    ad -> leftBar = true;
}

void app(){
    while(1){
        int signal = 0;
        AppData *ad = app_data();
        log(LOG, "Main app starts.");        
        setcolor(_WHITE);
        bar(0, 0, MAXWIDTH, MAXHEIGHT);

        mouse_pageUpdate();
        if(ad -> leftBar){
            setcolor(_GRAY);
            bar(0, 0, 200, MAXHEIGHT);
        }

        while(1){
            int k = keybord_getKey();
            Mouse * m = mouse();
            mouse_update();
            if(keybord_isESCAPE(k)){
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