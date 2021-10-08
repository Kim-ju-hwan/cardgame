#define _CRT_SECURE_NO_WARNINGS
#include <bangtal>
using namespace bangtal;

#include<cstdlib>
#include<ctime>

static int player, com;
static int round_num = 1;
static int p_score = 0, c_score = 0;

//승패를 판별해주는 함수
void win_lose(int p,int  c) {
	char path[90];
	if (c == p) {
		p_score += 1;
		c_score += 1;
		sprintf(path, "%d라운드 결과 무승부!! 컴퓨터:%d, 플레이어:%d", round_num, c_score, p_score);
		showMessage(path);
	}
	else if (c == 4 &&p==3) {
		c_score += 2;
		sprintf(path, "%d라운드 결과 컴퓨터가 조커로 승리!! 컴퓨터:%d, 플레이어:%d", round_num, c_score, p_score);
		showMessage(path);
	}
	else if (c==3 && p==4) {
		p_score += 2;
		sprintf(path, "%d라운드 결과 플레이어가 조커로 승리!! 컴퓨터:%d, 플레이어:%d", round_num, c_score, p_score);
		showMessage(path);
	}
	else if(c==4){
		p_score += 1;
		sprintf(path, "%d라운드 결과 플레이어 승리!! 컴퓨터:%d, 플레이어:%d", round_num, c_score, p_score);
		showMessage(path);
	}
	else if (p == 4) {
		c_score += 1;
		sprintf(path, "%d라운드 결과 컴퓨터 승리!! 컴퓨터:%d, 플레이어:%d", round_num, c_score, p_score);
		showMessage(path);
	}
	else if (c > p) {
		c_score += 1;
		sprintf(path, "%d라운드 결과 컴퓨터 승리!! 컴퓨터:%d, 플레이어:%d", round_num, c_score, p_score);
		showMessage(path);
	}
	else {
		p_score += 1;
		sprintf(path, "%d라운드 결과 플레이어 승리!! 컴퓨터:%d, 플레이어:%d", round_num, c_score, p_score);
		showMessage(path);
	}
	round_num += 1;
	if (round_num == 6) {
		if (p_score > c_score) {
			sprintf(path, "최종결과 %d : %d로 플레이어의 승리!!" ,c_score, p_score);
			showMessage(path);
		}
		else if (c_score > p_score) {
			sprintf(path, "최종결과 %d : %d로 컴퓨터의 승리!!", c_score, p_score);
			showMessage(path);
		}
		else {
			showMessage("최종결과 무승부!!");
		}
	}
}
int main()
{
	auto scene = Scene::create("카드게임", "image/배경.png");
	char path[50];
	ObjectPtr comcard[5], usercard[5];
	int x[5] = { 300,400,500,600,700 };


	//선택한 카드가 보여지는 곳
	auto comshow= Object::create("image/빈칸.jpg", scene, x[0]+10, 600);
	comshow->setScale(1.1f);
	auto usershow = Object::create("image/빈칸.jpg", scene, x[3]+10, 600);
	usershow->setScale(1.1f);

	//타이머로 점수판생성
	int time1 = 0;
	auto timer1 = Timer::create(time1);
	showTimer(timer1);
	//일반 카드 생성
	for (int i = 0;i < 4;i++) {
		sprintf(path, "image/카드_00%d.jpg", i + 1);
		usercard[i] = Object::create(path, scene, x[i], 400);
		usercard[i]->setScale(0.55f);		
		comcard[i]= Object::create("image/카드뒷면.jpg", scene, x[i], 900);
		comcard[i]->setScale(0.4f);
	}
	//조커 생성
	usercard[4]= Object::create("image/카드_009.jpg", scene, x[4], 400);
	usercard[4]->setScale(0.176f);
	comcard[4] = Object::create("image/카드뒷면.jpg", scene, x[4], 900);
	comcard[4]->setScale(0.4f);

	//컴퓨터의 카드선택(랜덤으로 섞는다.)
	int com_pick[5] = { 0,1,2,3,4 };
	srand(time(NULL));
	int temp;
	int r;
	for (int i = 0; i < 5; i++) {
		r = rand() % 5;
		temp = com_pick[i]; 
		com_pick[i] = com_pick[r];
		com_pick[r] = temp;
	}

	//플레이어의 카드마다 클릭시 컴퓨터의 카드와 비교해서 승패결정후 출력
	usercard[0]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		player = 0;
		usershow->setImage("image/카드_001.jpg");
		usershow->setScale(1.1f);
		usercard[0]->hide();
		com = com_pick[0];
		sprintf(path, "image/카드_00%d.jpg", com+5 );
		if (com == 4) {
			comshow->setImage(path);
			comshow->setScale(0.352f);
			comcard[com]->hide();
		}
		else {
			comshow->setImage(path);
			comshow->setScale(1.1f);
			comcard[com]->hide();
		}		
		win_lose(player, com);
		time1 = 60 * c_score + p_score;
		timer1->set(time1);
		return true;
		});

	usercard[1]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		player = 1;
		usershow->setImage("image/카드_002.jpg");
		usershow->setScale(1.1f);
		usercard[1]->hide();
		com = com_pick[1];
		sprintf(path, "image/카드_00%d.jpg", com + 5);
		if (com == 4) {
			comshow->setImage(path);
			comshow->setScale(0.352f);
			comcard[com]->hide();
		}
		else {
			comshow->setImage(path);
			comshow->setScale(1.1f);
			comcard[com]->hide();
		}
		win_lose(player, com);
		time1 = 60 * c_score + p_score;
		timer1->set(time1);
		return true;
		});

	usercard[2]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		player = 2;
		usershow->setImage("image/카드_003.jpg");
		usershow->setScale(1.1f);
		usercard[2]->hide();
		com = com_pick[2];
		sprintf(path, "image/카드_00%d.jpg", com + 5);
		if (com == 4) {
			comshow->setImage(path);
			comshow->setScale(0.352f);
			comcard[com]->hide();
		}
		else {
			comshow->setImage(path);
			comshow->setScale(1.1f);
			comcard[com]->hide();
		}
		win_lose(player, com);
		time1 = 60 * c_score + p_score;
		timer1->set(time1);
		return true;
		});

	usercard[3]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		player = 3;
		usershow->setImage("image/카드_004.jpg");
		usershow->setScale(1.1f);
		usercard[3]->hide();
		com = com_pick[3];
		sprintf(path, "image/카드_00%d.jpg", com + 5);
		if (com == 4) {
			comshow->setImage(path);
			comshow->setScale(0.352f);
			comcard[com]->hide();
		}
		else {
			comshow->setImage(path);
			comshow->setScale(1.1f);
			comcard[com]->hide();
		}
		win_lose(player, com);
		time1 = 60 * c_score + p_score;
		timer1->set(time1);
		return true;
		});
	
	usercard[4]->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		player = 4;
		usershow->setImage("image/카드_009.jpg");
		usershow->setScale(0.352f);
		usercard[4]->hide();
		com = com_pick[4];
		sprintf(path, "image/카드_00%d.jpg", com + 5);
		if (com == 4) {
			comshow->setImage(path);
			comshow->setScale(0.352f);
			comcard[com]->hide();
		}
		else {
			comshow->setImage(path);
			comshow->setScale(1.1f);
			comcard[com]->hide();
		}
		win_lose(player, com);
		time1 = 60 * c_score + p_score;
		timer1->set(time1);
		return true;
		});

	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	
	showMessage("카드를 선택하세요!!");
	startGame(scene);
	return 0;
}