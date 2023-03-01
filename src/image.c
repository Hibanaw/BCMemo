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

void image_render(string filePath, int x, int y){
    const char *path = filePath;
    FILE *imgFile = fopen(path, "rb");
    int i, j;
    short w, h;
    log(LOG, "Start rendering image.");
    if(imgFile == NULL){
        log(ERROR, "Image load error!");
        return ;
    }
    fread(&w, sizeof(short), 1, imgFile);
	fread(&h, sizeof(short), 1, imgFile);
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++){
			char c;
            c = fgetc(imgFile);
            putpixel(x+j, y+i, c);
        }
    }
    fclose(imgFile);
    log(DEBUG, "Image rendering ends.");
}

void image_renderEmerge(string filePath, int x, int y){
    const char *path = filePath;
    FILE *imgFile;
    int i, j, k, l;
    short w, h;
    int step = 4;
    log(LOG, "Start rendering image with emerge effect.");

    for(l = 0; l < step; l++){
        FILE *p = fopen(path, "rb");
        if(imgFile == NULL){
            log(ERROR, "Image load error!");
            return ;
        }
        fread(&w, sizeof(short), 1, p);
        fread(&h, sizeof(short), 1, p);
        for(i = 0; i < h; i++){
            for(j = 0; j < w; j++){
                char c;
                c = fgetc(p);
                if((j+x) % step == l || (i+y) % step == l)
					putpixel(x+j, y+i, c);
            }
        }
        fclose(p);
    }
    fclose(imgFile);
    log(DEBUG, "Image rendering ends.");
}
