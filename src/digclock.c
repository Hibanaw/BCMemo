/**
 * @file digclock.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-03
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "digclock.h"

void digitalClock_getTime(){
    static time_t t;
    time_t tn = time(NULL);
    char times[25];
    if(t != tn){
        t = tn;
        strftime(times, 20, "%H:%M:%S", localtime(&tn));
        mouse_hide();
        setfillstyle(1, _BLACK);
        bar(920, 0, 1024, 20);
        setfillstyle(1, _WHITE);
        bar(921, 1, 1022, 19);
        settextstyle(3, 0, 1);
        setcolor(_BLACK);
        settextjustify(LEFT_TEXT, 2);
        outtextxy(930, -3, times);
        mouse_show();
    }
}