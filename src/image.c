/**
 * @file image.c
 * @author Hibanaw Hu (hibanaw@qq.com)
 * @brief 
 * @date 2023-02-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "image.h"

void image_render(char * filePath, int x, int y){
    const char *path = filePath;
    FILE *imgFile = fopen(path, "rb");
    int i, j;
    short w, h;
    debug(LOG, "Start rendering image.");
    if(imgFile == NULL){
        debug(ERROR, "Image load error!");
        return ;
    }
    fread(&w, sizeof(short), 1, imgFile);
	fread(&h, sizeof(short), 1, imgFile);
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++){
			char p, cp;
            p = fgetc(imgFile);
			cp = getpixel(x+j, y+i);
            if(p != cp)
				putpixel(x+j, y+i, p);
        }
    }
    fclose(imgFile);
    debug(DEBUG, "Image rendering ends.");
}

void image_getSize(char *filePath, int *width, int *height){
    const char *path = filePath;
    FILE *imgFile = fopen(path, "rb");
    short w, h;
    if(imgFile == NULL){
        debug(ERROR, "Image load error!");
        return ;
    }
    fread(&w, sizeof(short), 1, imgFile);
	fread(&h, sizeof(short), 1, imgFile);
    *width = w;
    *height = h;
    fclose(imgFile);
}