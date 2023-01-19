#include"core.h"

int init(){
	initsvga256();
	mouseinit();
	useRGB256Colors();
	textcolor(_WHITE);
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
		drawHome();
		int s, ls = 0;
		Mouse m;
		while(!ls){
			s = homeEvent(&m);
			//判断登录
			switch(s){
				case 1://登陆
					clrmous(m.posX, m.posY);
					ls = login();
					break;
				case -1://退出
					return 0;
			}
			delay(50);
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
		char username[101], password[101];
		Textbox tu;
		Textbox tp;
		Button b;
		tu.posX = tp.posX = 384;
		tu.posY = 420; tp.posY = 500;
		tu.width = tp.width = 256;
		tu.height = tp.height = 32;
		log("login loop time", DBG);
		drawLogin(tu, tp, b);

		int s;
		while(1){
			s = loginEvent(&tu, &tp, &b, &m);
			switch(s){
				case 1:
					goto LOGIN;
					break;
				case -1:
					clrmous(m.posX, m.posY);
					return -1;
					break;
			}
			delay(50);
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
		if(isLogin){

		}
		else{

		}
	}
	return 0;
}

void memu(){
	while(1){
		//绘制背景

		//读取列表
		Memos list;
		MemoNode *currentNode = list.start;

		//若为空，则直接创建第一篇
		if(list.start == NULL){
			MemoNode newMemoNode;
			list.start = (MemoNode huge *)malloc(sizeof(newMemoNode));
			memoDocument(&list.start->content);
			continue;
		}
		//不为空，显示列表
		int n = 0;
		while(n < 5 && currentNode->next != NULL){
			n++;
			
		}

	}
}

void memoDocument(Memo *m){

}

void close(){
	cleardevice();
	closesvga256();
}
