#include"core.h"

int init(){
	initsvga256();
	mouseinit();
	useRGB256Colors();
	return 0;
}


/**
 * @brief 主页
 * 
 * @return int 
 */
int home(){
	log("home()");
	while(1){
		pageHome();
		int s, ls = 0;
		Mouse m;
		while(!ls){
			s = listenerHome(&m);
			//判断登录
			switch(s){
				case 1://登陆
					clrmous(m.posX, m.posY);
					ls = login();
					break;
				case -1://退出
					return 0;
			}
			delay(10);
		}
	}
}

/**
 * 
 * @brief 登陆
 * 
 * @return int -1为退出，1为成功
 */
int login(){
	log("login()");
	Mouse m;
	while(1){
		Textbox tu;
		Textbox tp;
		Button b;
		log("login loop time", DBG);
		pageLogin(tu, tp, b);
		char username[101], password[101];

		int s;
		while(1){
			s = listenerLogin(&tu, &tp, &b, &m);
			switch(s){
				case 1:
					goto LOGIN;
					break;
				case -1:
					clrmous(m.posX, m.posY);
					return -1;
					break;
			}
			delay(10);
		}
		LOGIN:
		//验证
		int isLogin = 0;
		FILE* userfile = fopen("./users","r");
		char inputusernm[101], inputpasswd[101];
		char readusernm[101], readpasswd[101];
		strcpy(readusernm, username);
		strcpy(readpasswd, password);
		while(1){
			fscanf(userfile, "u:%s", readusernm);
			fscanf(userfile, "p:%s", readpasswd);
			if(readusernm == inputusernm && readpasswd == inputpasswd){
				isLogin = 1;
				break;
			}
		}
		switch (isLogin){
			case 1:
				//成功登陆
				break;
			case 2:
				//密码错误
				break;
		}	
	}
	return 0;
}

void mainLoop(){
	while(1){
		//TODO
	}
}


void close(){
	closesvga256();
}
