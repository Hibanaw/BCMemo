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

AppData *appData(){
    static AppData ad;
    return &ad;
}

void app(){
    Router r = router_new();
    MemoEditor me;
    appData()->displayLastEditUser = 0;
    me = memoEditor_new(r.memoFilePath, appData()->currentUser);
    animation_login();
    while(1){
        int signal = 0;
		mouse_hide();
		debug(LOG, "Main app starts.");
		setfillstyle(1, _WHITE);
		bar(0, 0, MAXWIDTH, MAXHEIGHT);
        setfillstyle(1, hexfffbf0);
		bar(0, 0, MAXWIDTH, 40);
        image_render("res/img/logotxt.bin", 85, 5);
        setfillstyle(1, hexfffbf0);
		bar(0, 0, 75, MAXHEIGHT);
        setcolor(hexd4dfff);
        setlinestyle(0, 1, 2);
        line(73, 0, 73, MAXHEIGHT);
        ime_draw();
        router_draw(&r);
        memoEditor_draw(&me);
        mouse_show();
        digitalClock_getTime();
        while(!signal){
            int k = bioskey(1);
            int mes = 0;
            Mouse *m = mouse();
            int rs;
            keybord_eat();
            mouse_update();
            ime_check();
            digitalClock_getTime();
            mes = memoEditor_event(&me);
            rs = router_event(&r);
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = AppExit;
            }
            if(rs == RouterExpand){
                signal = AppRouterExpand;
            }
            if(mes == 1){
                signal = AppRedraw;
            }
        }
        switch(signal){
            case AppExit:
                memoEditor_distruct(&me);
                router_distrcut();
                return 0;
                break;
            case AppRouterExpand:
				signal = router_expand(&r);
                if(signal == RouterChangeMemo){
                    memoEditor_distruct(&me);
                    me = memoEditor_new(r.memoFilePath, appData()->currentUser);
                }
                break;
            case AppRedraw:
                break;
        }
    }
}