#include"image.h"

void putImage(int x, int y, const char* imagePath){
    log("put image %s", LOG, imagePath);
    FILE *imgFile = fopen(imagePath, "rb");
    if(imgFile == NULL){
        log("file open error", ERR);
    }
    short w, h, c;
    fread(&w, sizeof(w), 1, imgFile);
	fread(&h, sizeof(h), 1, imgFile);
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            c = fgetc(imgFile);
            putpixel(x+j, y+i, c);
        }
    }
}