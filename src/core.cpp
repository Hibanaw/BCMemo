#include"core.h"
#include"frontend.h"

int init(){
	mouseinit();
	initGraph();
}

int initGraph(){
#ifndef _WIN32
	int gd = VGA, gm = VGAHI;
	initgraph(&gd, &gm, "C:\\BORLANDC\\BGI");
#else
	initgraph(1024, 768);
#endif
	return 0;
}

void home(){
	while(1){
		login();
	}
}

int login(){
	int status = loginPage();
	int isLogin = 0;
	FILE* userfile = fopen("./users","r");
	char inputusernm[101], inputpasswd[101];
	char readusernm[101], readpasswd[101];
	//输入
	
	while(fscanf(userfile, "u:%sp:%s", readusernm, readpasswd)!=EOF){
		if(readusernm == inputusernm && readpasswd == inputpasswd){
			isLogin = 1;
			break;
		}
	}
	if(isLogin){
		mainLoop();
	}
}

void mainLoop(){
	while(1){
		//TODO
	}
}

