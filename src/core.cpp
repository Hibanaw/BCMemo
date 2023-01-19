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
		drawHome();
		int s, ls = 0;
		Mouse m;
		while(!ls){
			s = homeEvent(&m);
			//�жϵ�¼
			switch(s){
				case 1://��½
					clrmous(m.posX, m.posY);
					ls = login();
					break;
				case -1://�˳�
					return 0;
			}
			delay(50);
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
		if(isLogin){

		}
		else{

		}
	}
	return 0;
}

void memu(){
	while(1){
		//���Ʊ���

		//��ȡ�б�
		Memos list;
		MemoNode *currentNode = list.start;

		//��Ϊ�գ���ֱ�Ӵ�����һƪ
		if(list.start == NULL){
			MemoNode newMemoNode;
			list.start = (MemoNode huge *)malloc(sizeof(newMemoNode));
			memoDocument(&list.start->content);
			continue;
		}
		//��Ϊ�գ���ʾ�б�
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
