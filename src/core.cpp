#include"core.h"

int init(){
	graphInit();
#ifndef _WIN32
	mouseinit();
#endif
	
	return 0;
}


/**
 * @brief ��ҳ
 * 
 * @return int 
 */
int home(){
	log("home()");
	setbkcolor(RED);
	while(1){
		int status = homePage();
		//�жϵ�¼
		switch(status){
			case 1://��½
				int status = login();
				switch (status){
					case 1:
						//�ɹ���½
						break;
					case 2:
						//�������
						break;
					case -1:
						//�������
						break;
				}
				break;
			case -1://�˳�
				return 0;
		}
		delay(50);
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
	char username[101], password[101];
	Textbox uBox = {username, 0, 100};
	Textbox pBox = {password, 0, 100};
    int s;
	do{
		s = loginPage(&uBox, &pBox);
		//�����˳�
		if(s == -1){
			return -1;
		}
	}while(!s);
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
	return isLogin;
}

void mainLoop(){
	while(1){
		//TODO
	}
}


void close(){
#ifndef _WIN32
	graphClose();
#endif
}
