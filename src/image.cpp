#include"image.h"

void putImage(int x, int y, const char* imagePath){
    log("put image %s", LOG, imagePath);
    FILE *imgFile = fopen(imagePath, "rb");
    if(imgFile == NULL){
        log("file open error", ERR);
    }
    int i, j;
    short w, h, c;
    fread(&w, sizeof(w), 1, imgFile);
	fread(&h, sizeof(h), 1, imgFile);
    
    puthz((x+w-7*18)/2,(y+h-20),"Õº∆¨º”‘ÿ÷–°≠°≠",16, 18, _RED);
    for(i = 0; i < h; i++){
        for(j = 0; j < w; j++){
            c = fgetc(imgFile);
            putpixel(x+j, y+i, c);
        }
    }
}