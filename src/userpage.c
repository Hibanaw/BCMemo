#include "userpage.h"
void memoeiditor_button_draw1(Button *b)
{
    int x1 = b->posX1, y1 = b->posY1,
        x2 = b->posX2, y2 = b->posY2;
    Text t;
    t.content = b->content;
    button_drawDefault(b);
    setcolor(_BLACK);
    setlinestyle(0, 0, THICK_WIDTH);
    circle(x1 + 15, (y1 + y2) / 2, 15);
}
void memoeditor_button_draw2(Button *b)
{
    int x1 = b->posX1, y1 = b->posY1,
        x2 = b->posX2, y2 = b->posY2;
    Text t = text_newDefault("添加用户", x1 + 100, y1, x2, y2);
    if (b->status == ButtonSelected)
    {
        t.font.fontColor = hex555f55;
    }
    button_drawDefault(b);
    text_display(t);
    setcolor(_BLACK);
    setlinestyle(0, 0, THICK_WIDTH);
    circle(x1 + 15 + 5, (y1 + y2) / 2, 15);
    line(x1 + 15 + 5, y1, x1 + 15 + 5, y2);
    line(x1 + 5, y1 + 15, x1 + 30 + 5, y1 + 15);
}
void memoeditor_button_draw3(Button *b)
{
    int x1 = b->posX1, y1 = b->posY1,
        x2 = b->posX2, y2 = b->posY2;
    setcolor(_BLACK);
    button_drawDefault(b);
    line(x1,y1,x2,y2);
    line(x2,y1,x1,y2);

}
int userpage_deleteuser(int j, int k)
{
    int i;
    for (i = k; i < j; i++)
    {
        strcpy(appData()->uid[i], appData()->uid[i + 1]);
    }
    appData()->userCount--;
    return (j - 1);
} // 删除uid[k],j为有几个用户；
int userpage_login(int j)
{
    char textInputBuffer1[50];
    char textInputBuffer2[50];
    memset(textInputBuffer1, 0, sizeof(textInputBuffer1));
    memset(textInputBuffer2, 0, sizeof(textInputBuffer2));
    while (1)
    {
        Text tc1, tc2, tc3, tw, tw1;
        int signal = 0;
        int x1, x2, y1, y2, c0, c10;
        Button b = button_new(350, 400,
                              650, 450,
                              "登 录",
                              button_drawWithText);
        TextInput t = textinput_newDefault(
            "请输入用户名",
            350, 200,
            650, 250,
            textInputBuffer1);
        TextInput t1 = textinput_newDefault(
            "请输入密码",
            350, 300,
            650, 350,
            textInputBuffer2);
        t1.textbox.maxLength = 8;
        t.textbox.maxLength = 8;
        tw = text_newDefault("用户名过短！", 500, 210, 800, 260);
        tw.font.fontColor = _RED;
        tw1 = text_newDefault("密码过短！", 500, 310, 800, 360);
        tw1.font.fontColor = _RED;
        tc1 = text_newDefault("账号已存在！", 400, 360, 800, 410);
        tc1.font.fontColor = _RED;
        tc2 = text_newDefault("账号已存在！", 400, 360, 800, 410);
        tc2.font.fontColor = _RED;
        tc3 = text_newDefault("注册成功！", 400, 360, 800, 410);
        tc3.font.fontColor = _RED;
        // Button b=button_new()
        mouse_hide();
        x1 = 412 - 60 - 20;
        x2 = 612 + 60 + 20;
        y1 = 234 - 90;
        y2 = 384 + 240;
        c0 = hex808080;
        c10 = hexd4bfaa;
        setfillstyle(1, c10);
        setcolor(c10);
        bar(x1 + 6, y1, x2 - 6, y2);
        bar(x1, y1 + 6, x2, y2 - 6);
        pieslice(x1 + 6, y1 + 6, 90, 180, 6);
        pieslice(x1 + 6, y2 - 6, 180, 270, 6);
        pieslice(x2 - 6, y1 + 6, 0, 90, 6);
        pieslice(x2 - 6, y2 - 6, 270, 360, 6);
        setcolor(c0);
        setlinestyle(0, 1, 3);
        line(x1 + 6, y1, x2 - 6, y1);
        line(x1 + 6, y2, x2 - 6, y2);
        line(x1, y1 + 6, x1, y2 - 6);
        line(x2, y1 + 6, x2, y2 - 6);
        arc(x1 + 6, y1 + 6, 90, 180, 6);
        arc(x1 + 6, y2 - 6, 180, 270, 6);
        arc(x2 - 6, y1 + 6, 0, 90, 6);
        arc(x2 - 6, y2 - 6, 270, 360, 6);
        button_draw(&b);
        textinput_drawDefault(&t);
        textinput_drawDefault(&t1);
        mouse_show();
        while (!signal)
        {
            int k, bs, tbs, tbs1, lgs, ly1, ly2, ly3, ly4;
            int ly = 3;
            Text ta1, ta2, ta3, ta4;
            Mouse *m = mouse();
            mouse_update();
            digitalClock_getTime();
            ime_check();
            keybord_eat();
            ly1 = mouse_isClickedInBox(0, 0, 1024, y1);
            ly2 = mouse_isClickedInBox(0, y1, x1, y2);
            ly3 = mouse_isClickedInBox(x2, y1, 1024, y2);
            ly4 = mouse_isClickedInBox(0, y2, 1024, 768);
            k = bioskey(1);
            bs = button_event(&b);
            tbs = textbox_event(&t.textbox);
            tbs1 = textbox_event(&t1.textbox);
            if (keybord_isESCAPE(k))
            {
                bioskey(0);
                signal = -1;
                break;
            }
            if (ly1 == 1)
            {
                return;
            }
            if (ly2 == 1)
            {
                return;
            }
            if (ly3 == 1)
            {
                return;
            }
            if (ly4 == 1)
            {
                return;
            }
            if (bs || ((tbs == 1) && (tbs1 == 1)))
            {
                if (bs)
                {
                    ly = length_judge(t.textbox.content, t1.textbox.content);
                    if (ly == 3)
                    {
                        lgs = user_login(t.textbox.content, t1.textbox.content, 0);
                        switch (lgs)
                        {
                        case 4:
                            text_display(tc1);
                            delay(1000);
                            break;
                            return 0;
                        case 5:
                            text_display(tc2);
                            delay(1000);
                            break;
                        case 6:
                            text_display(tc3);
                            user_login(t.textbox.content, t1.textbox.content, 1);
                            strcpy(appData()->uid[j], t.textbox.content);
                            delay(1000);
                            signal = 1;
                            return 1;
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
            return 1;
            break;
        case -1:
            debug(DEBUG, "EXIT.");
            return;
            break;
        }
    }
}

void userpage()
{
    char textInputBuffer[50];
    int n = 1;
    memset(textInputBuffer, 0, sizeof(textInputBuffer));
    while (1)
    { 
        int j=appData()->userCount;
        int buttonCount = 1;
        int signal = 0;
        int p;
        int j1 =0;
        int p1 = -1;
        int x1, x2, y1, y2, c0, c10;
        int y3 = 410;
        int m;
        Text b[6];
        Button d[6];
        // Text t = text_newDefault("用 户:", 340, 380, 440, 580);
        Button c;
        Text t1 = text_newDefault(appData()->uid[0], 350, 380, 640, 580);
        b[0] = text_newDefault(appData()->uid[0], 350, 380, 640, 580);
        // for (p = 1; p < 6; p++)
        // {
        //     b[p] = button_new(340, 380 + 30 * (p - 1), 690, 410 + 30 * (p - 1), " ", memoeditor_button_draw1);
        // }
        mouse_hide();
        c0 = hex808080;
        c10 = _LIGHTGRAY;
        x1 = 412 - 60 - 20;
        x2 = 612 + 60 + 20;
        y1 = 234 - 90;
        y2 = 384 + 240;
        setfillstyle(1, c10);
        setcolor(c10);
        bar(x1 + 6, y1, x2 - 6, y2);
        bar(x1, y1 + 6, x2, y2 - 6);
        pieslice(x1 + 6, y1 + 6, 90, 180, 6);
        pieslice(x1 + 6, y2 - 6, 180, 270, 6);
        pieslice(x2 - 6, y1 + 6, 0, 90, 6);
        pieslice(x2 - 6, y2 - 6, 270, 360, 6);
        setcolor(c0);
        setlinestyle(0, 1, 3);
        line(x1 + 6, y1, x2 - 6, y1);
        line(x1 + 6, y2, x2 - 6, y2);
        line(x1, y1 + 6, x1, y2 - 6);
        line(x2, y1 + 6, x2, y2 - 6);
        arc(x1 + 6, y1 + 6, 90, 180, 6);
        arc(x1 + 6, y2 - 6, 180, 270, 6);
        arc(x2 - 6, y1 + 6, 0, 90, 6);
        arc(x2 - 6, y2 - 6, 270, 360, 6);
        setcolor(_WHITE);
        circle(512, 300, 60);
        circle(512, 282, 15);
        arc(512, 352.5, 27, 153, 55.5);
        if (j < 5)
        {
            y3 += 30 * (j - 1);
            c = button_new(340, y3, 690, y3 + 30, " ", memoeditor_button_draw2);
            button_draw(&c);
        }
        for(p=0;p<5;p++)
        {
                b[p] = text_newDefault(appData()->uid[p], 350, 380 + 30 * p, 640, 580 + 30 * p);
                d[p] = button_new(650, 385 + 30 * p, 670, 405 + 30 * p, "", memoeditor_button_draw3);
                text_display(b[p]);
        }
        //  else
        //  {
        //     for(p=0;p<j;p++)
        //     {
        //         text_display(b[p]);
        //     }
        //  }
        mouse_show();
        digitalClock_getTime();
        while (!signal)
        {
            int k, a = 0;
            int i = 0;
            int be[5] = {0};
            int ly1, ly2, ly3, ly4;
            int tbs;
            Mouse *m = mouse();
            // Text b[5];
            // for(i=0;i<5;i++)
            // {
            //     b[i]=text_newDefault(appData()->uid[i], 470, 380+30*i, 620, 580+30*i);
            // }
            mouse_update();
            keybord_eat();
            ly1 = mouse_isClickedInBox(0, 0, 1024, y1);
            ly2 = mouse_isClickedInBox(0, y1, x1, y2);
            ly3 = mouse_isClickedInBox(x2, y1, 1024, y2);
            ly4 = mouse_isClickedInBox(0, y2, 1024, 768);
            // be = button_event(&b[n]);
            if (j == 1)
            {
                // text_display(t);
                text_display(t1);
            }
            if (j < 5)
            {
                a = button_event(&c);
            }
            // isEditing = 0;
            if (a == 1)
            {
                if (userpage_login(j))
                {
                    j++;
                    appData()->userCount++;
                    break;
                }
                // break;
            }
            // for (p = 0; p < j; p++)
            // {
            //     b[p] = text_newDefault(appData()->uid[p], 350, 380 + 30 * p, 640, 580 + 30 * p);
            //     d[p] = button_new(650, 385 + 30 * p, 670, 405 + 30 * p, "", memoeditor_button_draw3);
            //     text_display(b[p]);
            // }
            for (p = 0; p < j; p++)
            {
                if (button_event(d + p))
                {
                    p1 = p;
                    j1 = userpage_deleteuser(j, p1);
                    j = j1;
                    signal =2;
                }
            }
            // if(p1+1)
            // {
            // j1=userpage_deleteuser(j,p1);
            // j=j1;
            // for(p=0;p<j;p++)
            // {
            //   b[p]=text_newDefault(appData()->uid[p],350, 380+30*p, 640, 580+30*p);
            //   text_display(b[p]);
            // }
            // }
            // for (i = 1; i < j + 1 ; i++)
            // {
            //     be[i - 1] = button_event(&b[i]);
            //     if (be[i - 1] == 1)
            //     {
            //         appData()->currentUser = appData()->uid[i];
            //         break;
            //     }
            // }
            digitalClock_getTime();
            // m = Button_event(&b);
            k = bioskey(1);
            if (keybord_isESCAPE(k))
            {
                bioskey(0);
                signal = -1;
                break;
            }
            if (ly1 == 1)
            {
                signal = 1;
                return;
            }
            if (ly2 == 1)
            {
                signal = 1;
                return;
            }
            if (ly3 == 1)
            {
                signal = 1;
                return;
            }
            if (ly4 == 1)
            {
                signal = 1;
                return;
            }
        }
        switch (signal)
        {
        case -1:
            return 0;
            break;
        case 1:
            return;
            break;
        case 2:
        break;
            // case 2:
            //     strcpy(appData()->uid[button_num], t1.textbox.content);
            //     // isEditing =0;
            //     break;
        }
    }
}