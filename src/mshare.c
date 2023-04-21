/**
 * @file share.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-04-20
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "mshare.h"


void share_page(char *memoName){
    char strBuffer[30];
    char shareCodeBuffer[20];
    ShareRadioBoxArea sr;
    memset(strBuffer, 0, sizeof(strBuffer));
    sr = share_newRadioBoxArea(strBuffer);
    while(1){
        Button exitButton = button_new(690, 300, 780, 340, "关闭", button_drawWINUI);
        Button shareButton = button_new(320, 230, 410, 270, "获取", button_drawWINUI);
        Text title = text_newDefault("新建共享…", 486, 80, 0, 0);
		Text expire = text_newSmall("有效期：", 350, 120);
        Text expireTime1 = text_newSmall("永久有效     10分钟     1天", 390, 150);
        Text expireTime2 = text_newSmall("自定义：", 390, 190);
        int signal = 0;
        int selecetMode = 1;
        expire.font.fontColor = _BLACK;
        mouse_hide();
        setfillstyle(1, hexfffbf0);
        bar(300, 72, 800, 360);
        button_draw(&exitButton);
        button_draw(&shareButton);
        text_display(expireTime1);
        text_display(expireTime2);
        text_display(title);
        text_display(expire);
        share_drawRadioBoxArea(&sr);
        mouse_show();
        while(!signal){
            int k = bioskey(1);
            int bs = button_event(&exitButton), sbs = button_event(&shareButton);
            int ras = 0;
            digitalClock_getTime();
            keybord_eat();
            mouse_update();
            ras = share_radioBoxAreaEvent(&sr);
            if(ras){
                selecetMode = ras;
            }
            if(keybord_isESCAPE(k)){
                bioskey(0);
                signal = -1;
            }
            if(bs){
                signal = -1;
            }
            if(sbs){
                time_t nowTime = time(NULL);
                time_t expireTime;
                Text shareCodeText = text_newDefault(shareCodeBuffer, 430, 230, 650, 270);
                char *p;
                switch (ras)
                {
                case 1:
                    expireTime = 0;
                    break;
                case 2:
                    expireTime = nowTime + 10*60;
                    break;
                case 3:
                    expireTime = nowTime + 24*60*60;
                    break;
                case 4:
                    for(p = strBuffer; *p != 0; p++){
                        if(*p < '0' || *p > '9'){
                            Text errorT = text_newSmall(
                                "内容不合法",
                                600, 185
                            );
                            text_display(errorT);
                            break;
                        }
                    }
                    expireTime = nowTime + 60*atoi(strBuffer);
                    break;
                }
                if(!share_add(memoName, shareCodeBuffer, expireTime)){
                    setfillstyle(1, hexfffbf0);
                    bar(430, 230, 650, 270);
                    text_display(shareCodeText);
                }
            }
        }
        switch (signal)
        {
        case -1:
            return;
            break;
        
        default:
            break;
        }
    }
}

int share_add(char *memoName, char *shareCodeBuffer, time_t expireTime){
    Share sd;
    int i;
    FILE *fp;
    memset(&sd, 0, sizeof(Share));
    strcpy(sd.memoName, memoName);
    srand(time(NULL));
    for(i = 0; i < 6; i++){
        int r = rand()%62;
        if(r < 26){
            sd.code[i] = 'a'+r;
        }
        else if(r < 52){
            sd.code[i] = 'A'+r-26;
        }
        else{
            sd.code[i] = '0'+r-52;
        }
    }
    sd.code[i] = 0;
    sd.expiryTime = expireTime;
    fp = fopen("data/share.dat", "ab+");
    if(fp == NULL){
        return 1;
    }
    fwrite(&sd, sizeof(Share), 1, fp);
    fclose(fp);
    strcpy(shareCodeBuffer, sd.code);
    return 0;
}

int share_determine(char *shareCode, char *uid){

}

ShareRadioBoxArea share_newRadioBoxArea(char *buffer){
    ShareRadioBoxArea ra;
    int i;
    for(i = 0; i < 3; i++){
        ra.radioBox[i] = button_new(360+i*144, 150, 380+i*144, 170, 0, button_checkboxDraw);
    }
    ra.radioBox[3] = button_new(360, 190, 380, 210, 0, button_checkboxDraw);
    ra.radioBox[0].content = 1;
    buffer[0] = 0;
    ra.textInput = textinput_newDefault("自定义（分钟）", 460, 185, 660, 215, buffer);
    ra.textInput.textbox.font.fontSize = 16;
    ra.textInput.textbox.posY1 = 190;
    ra.textInput.textbox.posY2 = 210;
    return ra;
}

void share_drawRadioBoxArea(ShareRadioBoxArea *sr){
    int i;
    for(i = 0; i < 4; i++){
        button_draw(sr->radioBox+i);
    }
	textinput_draw(&sr->textInput);
}

int share_radioBoxAreaEvent(ShareRadioBoxArea *sr){
    int k = 0;
    int lf, nf;
    int i;
    int tls = sr->textInput.textbox.status;
    for(i = 0; i < 4; i++){
        if((int)(sr->radioBox[i].content) == 1){
            lf = i;
        } 
        if(button_event(sr->radioBox+i) == 1){
            k = 1;
            nf = i;
        }
    }
	textinput_event(&sr->textInput);
    if(tls != TextboxSelected && sr->textInput.textbox.status == TextboxSelected){
        k = 1;
        nf = 3;
    }
    if(k && nf != lf){
        sr->radioBox[lf].content = 0;
        sr->radioBox[nf].content = 1;
        mouse_hide();
        share_drawRadioBoxArea(sr);
        mouse_show();
    }
    return nf+1;
}