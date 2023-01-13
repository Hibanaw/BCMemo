#include"core.h"

int init(){
	initsvga256();
	mouseinit();
	
	return 0;
}


/**
 * @brief 主页
 * 
 * @return int 
 */
int home(){
	log("home()");
	homePage();
	while(1){
		//鼠标事件
		int x, y, c;
		mread(&x, &y, &c);
		//键盘事件
		int k = -1;
		if(bioskey(1)){
			k = bioskey(0);
		}
		//进入登陆
		if(c != 0){
			log("clicked %d",DBG, c);
			return 1;
		}
		if(k != -1 && k != ESCAPE){
			log("pressed %x", DBG, k);
		}
		//退出
		if(k == ESCAPE) return -1;
		//判断登录
		switch(status){
			case 1://登陆
				int status = login();
				switch (status){
					case 1:
						//成功登陆
						break;
					case 2:
						//密码错误
						break;
					case -1:
						//点击返回
						break;
				}
				break;
			case -1://退出
				return 0;
		}
		delay(50);
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
	char username[101], password[101];
	Textbox uBox = {username, 0, 100};
	Textbox pBox = {password, 0, 100};
    int s;
	do{
		s = loginPage(&uBox, &pBox);
		//处理退出
		if(s == -1){
			return -1;
		}
		delay(50);
	}while(!s);
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
	return isLogin;
}

void mainLoop(){
	while(1){
		//TODO
	}
}


void close(){
	closesvga256();
}
