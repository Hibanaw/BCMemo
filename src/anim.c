/**
 * @file anim.c
 * @author wywgwt (2504133124@qq.com)
 * @brief
 * @date 2023-04-03
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "anim.h"

void animation_login()
{
    clock_t t0 = clock();
    clock_t t = t0;
    float k = 0.4;
    float l=2;
    clock_t t1;
    while ((t - t0) < (k * CLK_TCK))
    {
        t = clock();
        if ((t - t0) < k*1 * CLK_TCK / 6)
        {
            setfillstyle(1, hexaa3f00);
            bar(0, 0, 315, 768);
        }
        if (((t - t0) > k*1 * CLK_TCK / 6) && ((t - t0) <k* 2 * CLK_TCK / 6))
        {
            setfillstyle(1, hex7f1f00);
            bar(0, 0, 315, 768);
        }
        if (((t - t0) > k*2 * CLK_TCK / 6) && ((t - t0) < k*3 * CLK_TCK / 6))
        {
            setfillstyle(1, hex551f00);
            bar(0, 0, 315, 768);
        }
        if (((t - t0) > k*3 * CLK_TCK / 6) && ((t - t0) <k* 4 * CLK_TCK / 6))
        {
            setfillstyle(1, hex550000);
            bar(0, 0, 315, 768);
        }
        if (((t - t0) > k*4 * CLK_TCK / 6) && ((t - t0) <k* 5 * CLK_TCK / 6))
        {
            setfillstyle(1, hex2a0000);
            bar(0, 0, 315, 768);
        }
        if (((t - t0) > k*5 * CLK_TCK / 6) && ((t - t0) < k*6 * CLK_TCK / 6))
        {
            setfillstyle(1, hex000000);
            bar(0, 0, 315, 768);
        }
        if ((t - t0) < k*1 * CLK_TCK / 12)
        {
            setfillstyle(1, hexd4bfaa);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*1 * CLK_TCK / 12) && ((t - t0) < k*2 * CLK_TCK / 12))
        {
            setfillstyle(1, hexaabfaa);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*2 * CLK_TCK / 12) && ((t - t0) < k*3 * CLK_TCK / 12))
        {
            setfillstyle(1, hexaa9faa);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*3 * CLK_TCK / 12) && ((t - t0) < k*4 * CLK_TCK / 12))
        {
            setfillstyle(1, hexa0a0a4);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*4 * CLK_TCK / 12) && ((t - t0) < k*5 * CLK_TCK / 12))
        {
            setfillstyle(1, hexa0a0a4);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*5 * CLK_TCK / 12) && ((t - t0) < k*6 * CLK_TCK / 12))
        {
            setfillstyle(1, hex808080);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*6 * CLK_TCK / 12) && ((t - t0) < k*7 * CLK_TCK / 12))
        {
            setfillstyle(1, hex7f7f55);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*7 * CLK_TCK / 12) && ((t - t0) < k*8 * CLK_TCK / 12))
        {
            setfillstyle(1, hex7f5f55);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*8 * CLK_TCK / 12) && ((t - t0) < k*9 * CLK_TCK / 12))
        {
            setfillstyle(1, hex555f55);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*9 * CLK_TCK / 12) && ((t - t0) < k*10 * CLK_TCK / 12))
        {
            setfillstyle(1, hex553f55);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*10 * CLK_TCK / 12) && ((t - t0) < k*11 * CLK_TCK / 12))
        {
            setfillstyle(1, hex2a1f55);
            bar(315, 0, 1024, 768);
        }
        if (((t - t0) > k*11 * CLK_TCK / 12) && ((t - t0) < k*12 * CLK_TCK / 12))
        {
            setfillstyle(1, hex000000);
            bar(315, 0, 1024, 768);
        }
    }
    t0 = clock();
    t = t0;
    setfillstyle(1, _BLACK);
    bar(0, 0, 1024, 768);
    while (((t - t0) < 5 * CLK_TCK))
    {
        t = clock();
        if ((t - t0) < 3 * CLK_TCK)
        {
            setfillstyle(1, hex000000);
            bar(400, 400, 600, 768);
            setcolor(_WHITE);
            circle(512, 300, 60);
            circle(512, 282, 15);
            arc(512, 352.5, 28, 150, 55.5);
            if((t-t0)<1*CLK_TCK)
            {
                arc(512,450,2*(float)((t-t0)*(t-t0)),2*(float)((t-t0)*(t-t0))+270,30);
            }
            if(((t-t0)>1*CLK_TCK)&&((t-t0)<2*CLK_TCK))
            {
                arc(512,450,2*(float)(2*(t-t0))+16*18,2*(float)(2*(t-t0))+16*18+270,30);
            }
            if(((t-t0)>2*CLK_TCK)&&((t-t0)<3*CLK_TCK))
            {
                arc(512,450,2*(float)(108*(t-t0)-(t-t0)*(t-t0)-62*36),2*(float)(108*(t-t0)-(t-t0)*(t-t0)-62*36)+270,30);
            }
           // arc(512,450,100*cos((float)(t-t0)/6),100*cos((float)(t-t0)/6)+270,30);
            //arc(512, 450, (float)(2 * (t - t0) / 32 - 8 * (t - t0) * (t - t0) * (t - t0) / 192), ((float)(2 * (t - t0) / 32 - 8 * (t - t0) * (t - t0) * (t - t0) / 192)) + 270, 30);
            delay(100);
        }
    
    if (((t - t0) > 3 * CLK_TCK) && ((t - t0) < (3+1/l) * CLK_TCK))
    {
        setfillstyle(1, hex000000);
        bar(0, 0, 1024, 768);
        setcolor(_WHITE);
        circle(512-l*2*(256-75/4)*((t-t0-3*CLK_TCK)/CLK_TCK)-35,300-l*2*(150-75/4)*((t-t0-3*CLK_TCK)/CLK_TCK)-18,40-l*2*(20-75/4)*((t-t0-3*CLK_TCK)/CLK_TCK));
        circle(512-l*2*(256-75/4)*(t-t0-3*CLK_TCK)/CLK_TCK-35,288-l*2*(144-14*75/80)*(t-t0-3*CLK_TCK)/CLK_TCK-18,10-l*2*(5-5*75/80)*(t-t0-3*CLK_TCK)/CLK_TCK);
        arc(512-l*2*(256-75/4)*(t-t0-3*CLK_TCK)/CLK_TCK-35,335-l*2*(335-75*75/80)*(t-t0-3*CLK_TCK)/(2*CLK_TCK)-18,28,150,37-l*2*(37-75*37/80)*(t-t0-3*CLK_TCK)/(2*CLK_TCK));
        delay(50);
    }
    
    }
}
