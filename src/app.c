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
    appData()->currentUser=appData()->uid[0];
    me = memoEditor_new(r.memoName, appData()->currentUser);
    appData()->userCount = 1;
    animation_login();
    while(1){
        int signal = 0;
        Button eb = button_newExitButton();
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
        button_draw(&eb);
        memoEditor_draw(&me);
        mouse_show();
        digitalClock_getTime();
        while(!signal){
            int k = bioskey(1);
            int mes = 0;
            Mouse *m = mouse();
            int rs;
            int ebs;
            keybord_eat();
            mouse_update();
            ime_check();
            digitalClock_getTime();
            mes = memoEditor_event(&me);
            rs = router_event(&r);
            ebs = button_event(&eb);
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = AppExit;
            }
            if(ebs){
                signal = AppExit;
            }
            switch (rs)
            {
            case RouterExpand:
                signal = AppRouterExpand;
                break;
			case RouterChangeMemo:{
                int t = exitsave(&me);
                if(t == 1){
                    memoEditor_save(&me);
                }
                if(t==0){
                    break;
                }
                memoEditor_distruct(&me);
                me = memoEditor_new(r.memoName, appData()->currentUser);
                signal = AppRedraw;
            }
                break;
            case RouterUserPage:
                signal = AppUserPage;
                break;
            }
            if(mes == 1){
                signal = AppRedraw;
            }
        }
        switch(signal){
            case AppExit:{
                int t = exitsave(&me);
                if(t == 1){
                    memoEditor_save(&me);
                }
                if(t==0){
                    break;
                }
                memoEditor_distruct(&me);
                router_distrcut();
            }
                return 0;
                break;
            case AppRouterExpand:
				signal = router_expand(&r);
                if(signal == RouterChangeMemo){
                    int t = exitsave(&me);
                    if(t == 1){
                        memoEditor_save(&me);
                    }
                    if(t==0){
                        break;
                    }
                    memoEditor_distruct(&me);
                    me = memoEditor_new(r.memoName, appData()->currentUser);
                }
                if(signal == RouterUserPage){
                    if(userpage()){
                        memoEditor_distruct(&me);
                        r = router_new();
                        me = memoEditor_new(r.memoName, appData()->currentUser);
                    }
                }
                break;
            case AppRedraw:
                break;
            case AppUserPage:
                if(userpage()){
                    memoEditor_distruct(&me);
                    r = router_new();
                    me = memoEditor_new(r.memoName, appData()->currentUser);
                }
                break;
        }
    }
}