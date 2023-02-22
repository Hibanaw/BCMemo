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
    if(imgFile == NULL){
        printf("ERR\n");
        return ;
    }
    fread(&w, sizeof(short), 1, imgFile);
	fread(&h, sizeof(short), 1, imgFile);
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++){
			char c = fgetc(imgFile);
            putpixel(x+j, y+i, c);
        }
    }
    fclose(imgFile);
}