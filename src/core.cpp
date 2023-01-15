#include"core.h"

int init(){
	initsvga256();
	mouseinit();
	useRGB256Colors();
	textcolor(_WHITE);
	return 0;
}


/**
 * @brief ��ҳ
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
			//�жϵ�¼
			switch(s){
				case 1://��½
					clrmous(m.posX, m.posY);
					ls = login();
					break;
				case -1://�˳�
					return 0;
			}
			delay(10);
		}
	}
}

/**
 * 
 * @brief ��½
 * 
 * @return int -1Ϊ�˳���1Ϊ�ɹ�
 */
int login(){
	log("login()");
	Mouse m;
	while(1){
		char username[101], password[101];
		Textbox tu;
		Textbox tp;
		Button b;
		tu.posX = tp.posX = 384;
		tu.posY = 420; tp.posY = 500;
		tu.width = tp.width = 256;
		tu.height = tp.height = 32;
		log("login loop time", DBG);
		pageLogin(tu, tp, b);

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
		//��֤
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
				//�ɹ���½
				break;
			case 2:
				//�������
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
	cleardevice();
	closesvga256();
}
