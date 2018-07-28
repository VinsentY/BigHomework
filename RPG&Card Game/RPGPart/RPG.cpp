#include "RPG.h"
using namespace std;

CMusic cmusic;

int main() {

	RPG rpg;
	//移动测试模块
	
	rpg.gameStart();

	return 0;
}

void RPG::beforeRound() {

	bool firstDraw = false;
	if (!firstDraw) {
		refreshMap();
		firstDraw = true;
	}
	

	//这是我写过最蠢的代码
	static bool isPrint_1 = false;
	static bool isPrint_2 = false;
	static bool isPrint_3 = false;
	static bool isPrint_4 = false;
	static bool isPrint_5 = false;
	static bool isPrint_6 = false;

// 	if (killNum >= 10) {
// 		printWords(52, 15, "故事到此为止了",65);
// 		cutscenes();
// 		goodEnd(65);
// 	}

	if (rounds == 1 && !isPrint_1) {
		printWords(52, 15, "●表示当前你所处在的位置(左下角)", 15);
		printWords(57, 17, "↑↓←→选择，回车确定", 15);
		printWords(61, 19, "开始你的冒险吧！", 10);
		isPrint_1 = true;
	} else if (rounds == 10 && !isPrint_2) {
		printWords(52, 15, "迷宫中发出了一声异样的惨叫",65);
		printWords(52, 17, "并放出微弱的红光",65);
		printWords(52, 19, "你加快了你前进的脚步",65);

		isPrint_2 = true;
	} else if (rounds == 20 && !isPrint_3) {
		printWords(52, 15, "红光变得越来越强加强",65);
		printWords(52, 17, "这光线让你都睁不开眼",65);
		printWords(52, 19, "迷宫中的怪物也变得异样起来",65);
		
		isPrint_3 = true;
	} else if (rounds == 30 &&  !isPrint_4 ) {
		printWords(52, 15, "红光成功强化怪物",65);
		printWords(52, 17, "怪物攻击力全部 + 1",65);
		character.addAfraid();
		isPrint_4 = true;
	} else if (rounds == 40 && !isPrint_5) {
		printWords(52, 15, "怪物变得无比狂躁",65);
		printWords(52, 17, "怪物攻击力全部 + 1",65);
		character.addAfraid();
		isPrint_5 = true;
	} else if (rounds == 50 && !isPrint_6) {
		printWords(52, 15, "整个城堡似乎变成了怪物狂欢派对",65);
		printWords(52, 17, "怪物攻击力全部 + 1",65);
		character.addAfraid();
		isPrint_6 = true;
	}


}

void RPG::startRound() {
	Operator p;

	if ( (p = selectToMove()) != OPENITEM) {
		character.move(p);
	} else {
		refreshMap();
		choiceItem();
	}
}

void RPG::afterRound() {

	if (!character.is_alive()) {
		game_over = true;
	}
	
	refreshMap();
	analyseState();
	refreshData();


	static int temp = 0;
	temp++;
	if (temp == character.getSpeed()) {
		rounds++;
		temp = 0;
	}

	writeToFile();
	//血量增加
	//攻击力降低
	//失去行动力
}


void RPG::startAnimation() {

	console.SetColor("07");
	drawVICU(5, 5, "☆", 25);
	console.SetColor("70");

	drawVICU(7, 5, "■", 15);

	console.SetColor("07");

	system("cls");

	cmusic.setMediaName("音乐\\叮.wav");
	cmusic.Play();

	for (int i = 0; i < 6; i++) {
		if (kbhit()) {
			getch();
			break;
		}
		drawVICU(7 + i * 2, 5 + i, "■", 0);
		Sleep(250);
		drawVICU(7 + i * 2, 5 + i, "  ", 0);

	}
	cmusic.setMediaName("音乐\\轻松背景.mp3");
	cmusic.Play();
	drawVICU(19, 10, "■", 0);


	console.SetCoord(15, 2);
	cout << "Suprise!";


	printWords(56, 15, "PRESENT", 100);

}




bool RPG::login() {


begin:int arr[3][3];

	arr[0][0] = 1; arr[0][1] = 0; arr[0][2] = 0;
	arr[1][0] = 0; arr[1][1] = 1; arr[1][2] = 0;
	arr[2][0] = 0; arr[2][1] = 0; arr[2][2] = 1;


	char input = ' ';
	int choice = 0;

	char *words[3] = { "开始游戏", "继续游戏" , "关于我们" };

	drawVICU(19, 10, "■", 0);

	console.SetCoord(15, 2);
	cout << "﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌";
	console.SetCoord(15, 35);
	cout << "﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌﹌";//该部分显示上下两条横线
	console.SetCoord(65, 32);
	cout << "●";
	console.SetCoord(63, 33);
	cout << "╱";
	console.SetCoord(65, 33);
	cout << "█";
	console.SetCoord(67, 33);
	cout << "╲";
	console.SetCoord(65, 34);
	cout << "∧";//该部分显示小人
	console.SetCoord(58, 34);
	cout << "╚";
	console.SetCoord(60, 34);
	cout << "╝";
	console.SetCoord(58, 33);
	cout << "╔";
	console.SetCoord(60, 33);
	cout << "╗";//该部分显示小方块
	console.SetCoord(59, 32);
	cout << "？";//显示方块上面的问号

	console.SetCoord(35, 5);
	cout << "使用↑↓ 选择功能";

	console.SetCoord(30, 20);
	cout << "☆";
	console.SetCoord(34, 20);
	cout << words[0];

	console.SetCoord(34, 24);
	cout << words[1];

	console.SetCoord(34, 28);
	cout << words[2];

	setbuf(stdin, NULL);

	while (true) {
		static int i = 0;
		int shineSpeed = 10000;//该值表示登陆界面问号闪动的速度，该值越大闪动速度越慢
		if (i < 10000) {
			i++;
			console.SetCoord(59, 32);
			if (i >= 0 && i < (shineSpeed / 2))
				cout << "？";
			if (i >= (shineSpeed / 2) && i < shineSpeed)
				cout << "　";
			if (i == shineSpeed)
				i = 0;
		}//该部分让登陆动画小方块上的问号闪动

		if (kbhit()) {
			input = getch();
			switch (input) {
			case 72:
				//上
				if (choice == 0) {
					continue;
				}
				choice--;

				break;
			case 80:
				//下
				if (choice == 2) {
					continue;
				}
				choice++;

				break;
			case '\r':
				cutscenes();
				switch (choice) {
				case 0:
					return false;
				case 1:
					readFromFile();
					cmusic.Stop();
					return true;
				case 2:
					aboutUs();
					goto begin;
				}
			}

			if (input == 72 || input == 80) {
				console.SetCoord(30, 20);
				if (arr[choice][0] != 0) {
					cout << "☆";
					cout << "            ";
					printWords(34, 20, words[choice], 35);
				} else {
					cout << "  ";
				}
				console.SetCoord(30, 24);
				if (arr[choice][1] != 0) {
					cout << "☆";
					cout << "            ";
					printWords(34, 24, words[choice], 35);
				} else {
					cout << "  ";
				}
				console.SetCoord(30, 28);
				if (arr[choice][2] != 0) {
					cout << "☆";
					cout << "            ";
					printWords(34, 28, words[choice], 35);
				} else {
					cout << "  ";
				}
			}
			input = ' ';
		}
	}
}

void RPG::drama(int sleepTime) {

	int temp = sleepTime;

	system("cls");
	cmusic.setMediaName("音乐\\打字机L.mp3");
	cmusic.Play();
	printWords_p(25, 8, "在随机世界里，有一位邪恶的乌克斯国王", sleepTime);

	printWords_p(19, 10, "在他的统治下，人民水深火热，人们迫切地希望有一位勇士", sleepTime);

	printWords_p(19, 12, "他能勇敢地站出来去击败这位邪恶的国王，给人民带来自由", sleepTime);

	printWords_p(35, 14, "于是你上路了....", sleepTime);
	cmusic.Stop();
	setbuf(stdin, nullptr);
	getch();
	sleepTime = temp;
	system("cls");
	cmusic.Play();
	printWords_p(25, 8, "你在前往邪恶国王的城堡的路上", sleepTime);

	printWords_p(14, 10, "遇见了一位老太太，只见她看了你一眼，放下了手里的野花，说道", sleepTime);

	printWords_p(9, 14, "老太太：请问勇士尊姓大名是？", sleepTime);

	printWords_p(9, 16, "你回答道(暂不支持中文)：", sleepTime);
	cmusic.Stop();

	string name = character.setName();

	cmusic.Play();
	printWords_p(9, 18, "老太太：", sleepTime);
	console.SetCoord(17, 18);
	cout << name;
	Sleep(800);

	printWords_p(9, 20, "老太太：那可真是个动人的名字,让我想起了我的孩子 Lanteen", sleepTime);
	printWords_p(9, 22, "老太太：他也曾是一个无畏的勇士...", sleepTime);
	printWords_p(9, 24, "老太太：小伙子，我听说邪恶的国王十分强大，并需找到独一无二的武器才能杀死他", sleepTime);
	printWords_p(9, 26, "老太太：我这里有一本 康纳曾经留下来的笔记，我想一定对你的冒险会有帮助！", sleepTime);
	printWords_p(9, 28, "老太太捧起野花，向你挥手告别，你也挥了挥手，翻阅起了笔记...", sleepTime);
	printWords_p(9, 30, "回车翻阅笔记 >> ", sleepTime);
	cmusic.Stop();

	setbuf(stdin, nullptr);
	getch();
	sleepTime = temp;
	system("cls");
	cmusic.Play();
	printWords_p(29, 8, "笔记上记录着密密麻麻的文字", sleepTime);
	printWords_p(24, 10, "全都是对邪恶国王的描述和自我的心里变化", sleepTime);
	printWords_p(22, 12, "你翻到了最后一页，只见上面用极重的笔墨写道：", sleepTime);
	printWords_p(26, 18, "\"当你凝视深渊，深渊也在凝视着你\"", sleepTime);
	cmusic.Stop();
	Sleep(2000);
	cmusic.Play();
	printWords_p(28, 22, "并留着一些莫名其妙字母", sleepTime);
	printWords_p(38, 24, "VICU", sleepTime);  //638547
											  //剧情分支	
	printWords_p(24, 28, "你没有看懂它写了些什么，只好继续出发了", sleepTime);
	cmusic.Stop();
	Sleep(1500);
	cmusic.setMediaName("音乐\\神秘背景.mp3");
	cmusic.Play();
	sleepTime = temp;
	system("cls");
	printWords_p(22, 6, "你来到邪恶城堡的大门面前，游戏正式开始", sleepTime);
	printWords(2, 10, "移动：城堡迷雾(□)会阻碍你的视野，移动力消耗完后则进入下一回合", 10);
	printWords(2, 14, "购买：当你遇见符号为(﹩)的商人时，即会开始商品购买，你可以在商品里购买你想要的东西", 10);
	printWords(2, 18, "宝箱：当你遇见符号为(☆)的宝箱时，你就会获得一定的奖励，并且有几率获得特殊装备和道具", 10);
	printWords(2, 22, "战斗：当你遇见符号为(Ω)的怪物时，即会触发卡牌战斗，一旦一方血量降为0，战斗立刻结束", 10);
	printWords(2, 26, "目标: 击败城堡中的邪恶国王( ╳ )，你需要尽快找到并击杀他！", 10);
	printWords(32, 30, "回车推开城堡大门 >>", sleepTime);

	setbuf(stdin, nullptr);
	getch();
	cmusic.Stop();
	cmusic.setMediaName("音乐\\开门2.mp3");
	cmusic.Play();
	//对齐工作

	cutscenes();
	system("cls");
}

void RPG::cutscenes() {
	srand(time(NULL));
	int v1 = rand() % 4 + 1;
	int v2 = rand() % 4 + 1;

	for (int i = 0; i < 43; i++) {
		for (int j = 0; j < 37; j++) {

			console.SetCoord(i * 2, j);
			if (i % v1 == 0) {
				if (j % v2 == 0) {
					cout << "■";
				} else {
					cout << "  ";
				}
			} else {
				if (j % v2 == 0) {
					cout << "  ";
				} else {
					cout << "■";
				}
			}
		}
		Sleep(25);	
	}
	system("cls");
}

void RPG::drawVICU(int x, int y, char * symbol,int sleepTime) {
	printWords_p(x, y,symbol,sleepTime);
	
	printWords_p(x += 1, ++y,symbol,sleepTime);
	
	printWords_p(x += 1, ++y,symbol,sleepTime);
	
	printWords_p(x += 1, ++y,symbol,sleepTime);
	
	printWords_p(x += 1, ++y,symbol,sleepTime);
	
	printWords_p(x += 1, ++y,symbol,sleepTime);
	
	printWords_p(x += 1, --y,symbol,sleepTime);
	
	printWords_p(x += 1, --y,symbol,sleepTime);
	
	printWords_p(x += 1, --y,symbol,sleepTime);
	
	printWords_p(x += 1, --y,symbol,sleepTime);
	
	printWords_p(x += 1, --y,symbol,sleepTime);
	

	// 	printWords_p(x += 6, y,symbol,sleepTime); 
	// 	printWords_p(x += 2, y,symbol,sleepTime); 
	// 	printWords_p(x += 2, y,symbol,sleepTime); 
	// 	printWords_p(x += 2, y,symbol,sleepTime); 
	// 	printWords_p(x -= 4, ++y,symbol,sleepTime); 
	// 	printWords_p(x , ++y,symbol,sleepTime); 
	// 	printWords_p(x , ++y,symbol,sleepTime); 
	// 	printWords_p(x, ++y,symbol,sleepTime); 
	// 	printWords_p(x, ++y,symbol,sleepTime); 
	// 	printWords_p(x -= 4, y,symbol,sleepTime); 
	// 	printWords_p(x += 2, y,symbol,sleepTime); 
	// 	printWords_p(x += 2, y,symbol,sleepTime); 
	// 	printWords_p(x += 2, y,symbol,sleepTime); 
	// 	printWords_p(x += 2, y,symbol,sleepTime); 

	printWords_p(x += 4, y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 


	printWords_p(x += 4, y -= 5,symbol,sleepTime); 
	printWords_p(x += 2, y,symbol,sleepTime); 
	printWords_p(x += 2, y,symbol,sleepTime); 
	printWords_p(x += 2, y,symbol,sleepTime); 
	printWords_p(x -= 6, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x += 2, y,symbol,sleepTime); 
	printWords_p(x += 2, y,symbol,sleepTime); 
	printWords_p(x += 2, y,symbol,sleepTime); 

	printWords_p(x += 4, y -= 5,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x, ++y,symbol,sleepTime); 
	printWords_p(x += 2, y,symbol,sleepTime); 
	printWords_p(x += 2, y,symbol,sleepTime); 
	printWords_p(x += 2, y,symbol,sleepTime); 

	printWords_p(x, --y,symbol,sleepTime); 
	printWords_p(x, --y,symbol,sleepTime); 
	printWords_p(x, --y,symbol,sleepTime); 
	printWords_p(x, --y,symbol,sleepTime); 
	printWords_p(x, --y,symbol,sleepTime); 
}

void RPG::choiceItem() {

	int row = 0;
	int col = 0;

	char input = ' ';
	int bfrow = row;
	int bfcol = col;

	console.SetCoord(62, 24);
	cout << "使用物品中";

	console.SetCoord(6 + col * 30, 30 + row * 2);
	cout << symbolChoice;

	bool end = false;
	while (!end) {

		if (kbhit()) {

			bfcol = col;
			bfrow = row;

			input = getch();

			switch (input) {
			case 72:
				//上
				if (row == 0) {
					break;
				}
				row--;
				break;
			case 80:
				//下
				if (row == 1) {
					break;
				}
				row++;
				break;
			case 75:
				//左
				if (col == 0) {
					break;
				}
				col--;
				break;
			case 77:
				//右
				if (col == 2) {
					break;
				}
				col++;
				break;
			case '\r':
				character.useItem(row, col);
				refreshMap();
				break;
			case 27:
				end = true;
				break;
			}	

			console.SetCoord(6 + col * 30, 30 + row * 2);
			cout << symbolChoice;

			if (bfrow != row || bfcol != col) {
				console.SetCoord(6 + bfcol * 30, 30 + bfrow * 2);
				cout << "  ";	
			}
			input = ' ';
		}

		
	}
}

Operator RPG::selectToMove() {

	const int* arr = character.getPosition();

	int x = arr[0];
	int y = arr[1];

	Operator p = NOMOVE;

	char input;

	setbuf(stdin,nullptr);

	while (p == NOMOVE) {

		if (kbhit()) {
			input = getch();
			switch (input) {
			case 72:
				//上
				if (map[y - 1][x / 2] != WALL + 10) {
					p = UP;
					drawMove(x, y, UP);
				}
				input = ' ';
				break;
			case 80:
				//下
				if (map[y + 1][x / 2] != WALL + 10) {
					p = DOWN;
					drawMove(x, y, DOWN);
				}
				input = ' ';
				break;
			case 75:
				//左
				if (map[y][x / 2 - 1] != WALL + 10) {
					p = LEFT;
					drawMove(x, y, LEFT);
				}
				input = ' ';
				break;
			case 77:
				//右
				if (map[y][x / 2 + 1] != WALL + 10) {
					p = RIGHT;
					drawMove(x, y, RIGHT);
				}
				input = ' ';
				break;
			case 'e':
			case 'E':
				p = OPENITEM;	
			}
		
		}
	}

	return p;
}

void RPG::analyseState() {

	const int *arr = character.getPosition();

	switch (map[arr[1]][arr[0] / 2] - 10) {
	case SELLER:

		seller.sellItem(character);
		break;

	case TREASURE:

		character.openTreasure();
		break;

		// 1 ：药水
		// 2： 巨剑
		// 3： 盾牌
		// 4： 鞋子
		// 5:  随机宝箱

	case MONSETER:
		cutscenes();
		setbuf(stdin, nullptr);
		if (character.fightToMonster()) {
			cutscenes();
			refreshData();
			refreshMap();
			console.SetCoord(51, 16);
			if (character.addItem(*(new Item("怪物宝箱", 5, 6, 0, "Duang~")))) {
				cout << "你获得了怪物掉落的宝箱!";
			}		
			console.SetCoord(51, 18);
			srand(time(NULL));
			switch (rand() % 10 + 1) {
			case 1:
			case 2:
				if (character.addItem(*(new Item("小型回复药剂", 1, 0, 3, "味道像极了妈妈的红糖水")))) {
					cout << "你获得了一瓶小型HP药水";
				}		
				break;
			case 3:
			case 4:
			case 5:
			case 6:
				if (character.addItem(*(new Item("HP药水", 1, 0, 7, "更加纯真的HP药水")))) {
					cout << "你获得了一瓶HP药水";
				}		
				break;
			case 7:
				if (character.addItem(*(new Item("生日快乐", 6, 0, 0, "普通朋友的普通贺卡")))) {
					cout << "你获得了一张生日贺卡";
				}			
				break;
			case 8:
				if (character.addItem(*(new Item("<For River>", 6, 0, 0, "是一张你没有听过的唱片")))) {
					cout << "你获得了一张<For River>的CD唱片";
				}
				
				break;
			case 9:
				if (character.addItem(*(new Item("黑色十字架", 6, 0, 0, "他的主人一定很后悔弄丢它了")))) {
					cout << "你获得了有些缺口的黑色十字架";
				}
				
				break;
			case 10:
				if (character.addItem(*(new Item("终极回复药水", 1, 0, 15, "喝完后你充满力量")))) {
					cout << "你获得了终极回复药水";
				}
								
				break;
			}
			killNum++;
			if (killNum % 3 == 0) {
				character.levelUp();
			}
			
			Sleep(1500);
			setbuf(stdin, nullptr);
		} else {
			game_over = true;
		}
		break;
	case ENTRANCE:
		goodEnd(65);
	}


}

void RPG::refreshData() {
	const int *arr = character.getPosition();

// 	for (int i = character_y - 1; i <= character_y + 1; i++) {
// 		for (int j = character_x / 2 - 1; j <= character_x / 2 + 1; j++) {			
// 			map[i][j] -= 10;	//变得不可见			
// 		}
// 	}
	
	if (character_x != arr[0] || character_y != arr[1]) {
		map[character_y][character_x / 2] = EMPTY;
		character_x = arr[0];
		character_y = arr[1];
		map[character_y][character_x / 2] = CHARACTER;
	}

	for (int i = character_y - 1; i <= character_y + 1; i++) {
		for (int j = character_x / 2 - 1; j <= character_x / 2 + 1; j++) {
			if (map[i][j] < 10) {
				map[i][j] += 10;	//变得可见
			}
		}
	}


}

void RPG::refreshMap() {

	int x = 0;
	int y = 0;

	console.SetCoord(0, 0);
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < column; c++) {
			if (map[r][c] >= 10) {
				switch (map[r][c] - 10) {
				case WALL:
					cout << symbolWall;
					break;
				case CHARACTER:
					cout << symbolCharacter;
					break;
				case MONSETER:
					cout << symbolMonster;
					break;
				case TREASURE:
					cout << symbolTreasure;
					break;
				case SELLER:
					cout << symbolSeller;
					break;
				case EMPTY:
					cout << "  ";
					break;
				case ENTRANCE:
					cout << symbolTEntrance;
				}	
			} else {
				cout << symbolFog;
			}

		}
		y += 1;
		cout << endl;
	}

	//局部刷新
	for (int i = 1; i <= 25; i++) {
		console.SetCoord(50, i);
		for (int j = 1; j <= 35; j++) {
			cout << " ";
		}
	}

	for (int i = 26; i <= 36; i++) {
		console.SetCoord(0, i);
		for (int j = 1; j <= 86; j++) {
			cout << " ";
		}
	}
	console.SetCoord(5, 25);
	cout << "当前回合: " << rounds;

	character.printInterface();

}

void RPG::drawMove(int x, int y, Operator p) {

	bool isDraw = false;

	int j = 0;

	console.SetCoord(62, 24);
	cout << "角色移动中";

	console.SetCoord(x, y - 1);
	if (j == p) {
		cout << symbolCharacterMove;
		isDraw = true;
	} else if (map[y - 1][x / 2] == SELLER) {
		cout << symbolSeller;
	} else if (map[y - 1][x / 2] == WALL) {
		cout << symbolWall;
	} else if (map[y - 1][x / 2] == TREASURE) {
		cout << symbolTreasure;
	} else if (map[y - 1][x / 2] == MONSETER) {
		cout << symbolMonster;
	} else {
		cout << "  ";
	}
	j++;
	console.SetCoord(x, y + 1);
	if (!isDraw && j == p) {
		cout << symbolCharacterMove;
		isDraw = true;
	} else if (map[y + 1][x / 2] == SELLER) {
		cout << symbolSeller;
	} else if (map[y + 1][x / 2] == WALL) {
		cout << symbolWall;
	} else if (map[y + 1][x / 2] == TREASURE) {
		cout << symbolTreasure;
	} else if (map[y + 1][x / 2] == MONSETER) {
		cout << symbolMonster;
	} else {
		cout << "  ";
	}
	j++;
	console.SetCoord(x - 2, y);
	if (!isDraw && j == p) {
		cout << symbolCharacterMove;
		isDraw = true;
	} else if (map[y][x / 2 - 1] == WALL) {
		cout << symbolWall;
	} else if (map[y][x / 2 - 1] == SELLER) {
		cout << symbolSeller;
	} else if (map[y][x / 2 - 1] == TREASURE) {
		cout << symbolTreasure;
	} else if (map[y][x / 2 - 1] == MONSETER) {
		cout << symbolMonster;
	} else {
		cout << "  ";
	}
	j++;
	console.SetCoord(x + 2, y);
	if (!isDraw && j == p) {
		cout << symbolCharacterMove;
		isDraw = true;
	} else if (map[y][x / 2 + 1] == WALL) {
		cout << symbolWall;
	} else if (map[y][x / 2 + 1] == SELLER) {
		cout << symbolSeller;
	} else if (map[y][x / 2 + 1] == TREASURE) {
		cout << symbolTreasure;
	} else if (map[y][x / 2 + 1] == MONSETER) {
		cout << symbolMonster;
	} else {
		cout << "  ";
	}
}

void RPG::gameOver(int sleepTime) {
	system("cls");

	int x = 5;
	int y = 5;
	//锦上添花
	//Y
	printWords(x, y, symbol, sleepTime);
	printWords(x += 1, y += 1, symbol, sleepTime);
	printWords(x += 2, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 2, y -= 3, symbol, sleepTime);
	printWords(x += 1, y -= 1, symbol, sleepTime);
	//O
	printWords(x += 4, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x -= 4, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x, y -= 1, symbol, sleepTime);
	printWords(x, y -= 1, symbol, sleepTime);
	printWords(x, y -= 1, symbol, sleepTime);
	//U
	printWords(x += 4, y -= 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	//printWords(x += 2, y, symbol, sleepTime);
	printWords(x, y -= 1, symbol, sleepTime);
	printWords(x, y -= 1, symbol, sleepTime);
	printWords(x, y -= 1, symbol, sleepTime);
	printWords(x, y -= 1, symbol, sleepTime);
	//A
	printWords(x -= 8, y += 13, symbol, sleepTime);
	printWords(x += 1, y -= 1, symbol, sleepTime);
	printWords(x += 1, y -= 1, symbol, sleepTime);
	printWords(x += 1, y -= 1, symbol, sleepTime);
	printWords(x += 1, y -= 1, symbol, sleepTime);
	printWords(x += 1, y += 1, symbol, sleepTime);
	printWords(x += 1, y += 1, symbol, sleepTime);
	printWords(x += 1, y += 1, symbol, sleepTime);
	printWords(x += 1, y += 1, symbol, sleepTime);
	printWords(x -= 5, y -= 1, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);

	//R
	printWords(x += 4, y -= 3, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x -= 2, y += 1, symbol, sleepTime);
	printWords(x -= 2, y, symbol, sleepTime);
	printWords(x -= 2, y, symbol, sleepTime);
	printWords(x, y -= 2, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 6, y, symbol, sleepTime);

	//E
	printWords(x += 4, y -= 4, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x -= 6, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x -= 6, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);

	//D
	printWords(x -= 10, y += 5, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 2, y -= 4, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x -= 2, y += 1, symbol, sleepTime);
	printWords(x -= 2, y, symbol, sleepTime);


	//E
	printWords(x += 8, y -= 4, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x -= 6, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x -= 6, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);

	//A
	printWords(x += 4, y, symbol, sleepTime);
	printWords(x += 1, y -= 1, symbol, sleepTime);
	printWords(x += 1, y -= 1, symbol, sleepTime);
	printWords(x += 1, y -= 1, symbol, sleepTime);
	printWords(x += 1, y -= 1, symbol, sleepTime);
	printWords(x += 1, y += 1, symbol, sleepTime);
	printWords(x += 1, y += 1, symbol, sleepTime);
	printWords(x += 1, y += 1, symbol, sleepTime);
	printWords(x += 1, y += 1, symbol, sleepTime);
	printWords(x -= 5, y -= 1, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);

	//D
	printWords(x += 4, y -= 3, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x += 2, y -= 4, symbol, sleepTime);
	printWords(x += 2, y, symbol, sleepTime);
	printWords(x += 2, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x, y += 1, symbol, sleepTime);
	printWords(x -= 2, y += 1, symbol, sleepTime);
	printWords(x -= 2, y, symbol, sleepTime);
	int sleepTime2 = 200;
	for (int n = 0; n < 10; n++) {
		console.SetCoord(65, 14 - n);
		cout << "◎";
		console.SetCoord(65, 15 - n);
		cout << "●";
		console.SetCoord(63, 16 - n);
		cout << "◥";
		console.SetCoord(65, 16 - n);
		cout << "■";
		console.SetCoord(67, 16 - n);
		cout << "◤";
		console.SetCoord(65, 17 - n);
		cout << "∧";//该部分显示小人
		Sleep(sleepTime2);
		if (n != 9) {
			console.SetCoord(65, 14 - n);
			cout << "　";
			console.SetCoord(65, 15 - n);
			cout << "　";
			console.SetCoord(63, 16 - n);
			cout << "　";
			console.SetCoord(65, 16 - n);
			cout << "　";
			console.SetCoord(67, 16 - n);
			cout << "　";
			console.SetCoord(65, 17 - n);
			cout << "　";//该部分擦除小人
		}
		sleepTime2 += 20;
	}




	while (true) {
		static int i = 0;
		int shineSpeed = 30000;//该值表示死亡界面光环闪动的速度，该值越大闪动速度越慢
		if (i < shineSpeed) {
			i++;
			console.SetCoord(65, 5);
			if (i >= 0 && i < (shineSpeed / 3))
				cout << "　";
			if (i >= (shineSpeed / 3) && i < shineSpeed)
				cout << "◎";
			if (i == shineSpeed)
				i = 0;
		}//该部分让死亡界面小人头上的光环闪动

	}
}

void RPG::readFromFile() {
	ifstream in("data.txt");
	
	in >> character;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			in >> map[i][j];
		}
	}
	in >> rounds >> game_over
		>> character_x >> character_y >> killNum;
	in.close();
	
}

void RPG::writeToFile() {
	ofstream out("data.txt");

	out << character;

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 25; j++) {
			out << map[i][j] << " ";
		}
	}

	out << rounds << " " << game_over << " "
		<< character_x << " " << character_y << " " << killNum << " ";

	out.close();
}

void RPG::aboutUs() {
	system("cls");
	console.SetCoord(36, 3);
	cout << "关于我们";
	int iniy = 5;
	int col = 4;
	for (int n = 20; n > 0; n--) {
		console.SetCoord(8, iniy + n);
		cout << "制作     ———————————————————————— VICU小组";
		console.SetCoord(8, iniy + n + col);
		cout << "总负责人 ———————————————————————— 孙懿恺";
		console.SetCoord(8, iniy + n + col * 2);
		cout << "卡牌设计 ———————————————————————— 汪志成";
		if (iniy + n + col * 3 < 37) {
			console.SetCoord(8, iniy + n + col * 3);
			cout << "不改需求会死星人 ———————————————————— 彭晨涛";
		}
		if (iniy + n + col * 4 < 37) {
			console.SetCoord(8, iniy + n + col * 4);
			cout << "隐藏大佬 ———————————————————————— 橘";
		}
		if (iniy + n + col * 5 < 37) {
			console.SetCoord(8, iniy + n + col * 5);
			cout << "声优出演 ———————————————————————— 神秘黑衣人";
		}
		if (iniy + n + col * 6 < 37) {
			console.SetCoord(8, iniy + n + col * 6);
			cout << "            由于制作组水平有限，bug在所难免，有望玩家海涵！";
		}
		Sleep(500);
		if (n != 1) {
			console.SetCoord(8, iniy + n);
			cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　";
			console.SetCoord(8, iniy + n + col);
			cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　";
			console.SetCoord(8, iniy + n + col * 2);
			cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　";
			if (iniy + n + col * 3 < 37) {
				console.SetCoord(8, iniy + n + col * 3);
				cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　";
			}
			if (iniy + n + col * 4 < 37) {
				console.SetCoord(8, iniy + n + col * 4);
				cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　  ";
			}
			if (iniy + n + col * 5 < 37) {
				console.SetCoord(8, iniy + n + col * 5);
				cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　  ";
			}
			if (iniy + n + col * 6 < 37) {
				console.SetCoord(8, iniy + n + col * 6);
				cout << "　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　　";
			}
		}

	}

	getch();
	system("cls");
}


void RPG::goodEnd(int sleepTime) {
	system("cls");
	int temp = sleepTime;
	cmusic.setMediaName("音乐\\打字机L.mp3");
	cmusic.Play();
	printWords_p(4, 5, "顶层的房间里十分明亮，餐具和壁画被整齐的放在它应该在的地方", sleepTime); sleepTime = temp;
	printWords_p(4, 7, "房间里传来小孩子的欢笑声让房间充满温馨", sleepTime); sleepTime = temp;
	printWords_p(4, 9, "让你都想放下手里沾满血的剑和盾牌", sleepTime); sleepTime = temp;
	printWords_p(4, 11, "这时，从房间里走出一位婀娜多姿的女子，她一袭白纱，帽子上别着几朵刚刚摘下的鲜花。", sleepTime); sleepTime = temp;
	cmusic.Stop();
	cmusic.setMediaName("音乐\\CV\\哎呀.mp3");
	cmusic.Play();
	printWords_p(4, 14, "神秘女子：哎呀，哎呀！", sleepTime); sleepTime = temp;
	Sleep(1000);
	cmusic.setMediaName("音乐\\CV\\小兰提.mp3");
	cmusic.Play();
	printWords_p(4, 16, "神秘女子：小兰提！快来招待客人（应声一个小孩蹦蹦跳跳地走了出来，躲在女子后面）", sleepTime); sleepTime = temp;
	cmusic.setMediaName("音乐\\CV\\请问.mp3");
	cmusic.Play();
	printWords(4, 18, "神秘女子：请问客人您的名字是...\n\n", sleepTime);
	printWords(4, 20, "-------------------------------------\n\n", 0);
	printWords(4, 22, "1.你没有回答，选择了沉默观察\n\n", 0);
	printWords(4, 24, "2.你好,美丽的女士！你回答了你的名字\n\n", 0);
	printWords(4, 26, "-------------------------------------\n\n", 0);

	printWords(4, 27, "你的选择是>>", 0);

	int choice = 0;
	bool inputRight = false;

	do {
		cin >> choice;
		if (choice == 1 || choice == 2) {
			inputRight = true;
		}
	} while (!inputRight);

	while (true) {
		switch (choice) {
		case 1:
			system("cls");
			cmusic.setMediaName("音乐\\打字机L.mp3");
			cmusic.Play();
			printWords_p(4, 5, "女子对你的沉默感到不解", sleepTime); sleepTime = temp;
			cmusic.Stop();
			cmusic.setMediaName("音乐\\CV\\您千万.mp3");
			cmusic.Play();
			printWords_p(4, 7, "神秘女子：您千万不要客气，请把这当作自己的家一样!", sleepTime); sleepTime = temp;
			Sleep(2200);
			cmusic.setMediaName("音乐\\CV\\坐一坐.mp3");
			cmusic.Play();
			printWords_p(4, 9, "神秘女子：小兰提!快带客人去客厅坐一坐（小兰提还是很害羞的躲在女子后面）", sleepTime); sleepTime = temp;

			printWords(4, 12, "-------------------------------------", 0);
			printWords(4, 14, "1.你没有动身，同时握紧了手中带血的剑", 0);
			printWords(4, 16, "2.不好意思，女士我为刚才的无礼表示抱歉！你回答了你的名字", 0);
			printWords(4, 18, "-------------------------------------", 0);
			printWords(4, 19, "你的选择是>>", 0);

			do {
				cin >> choice;
				if (choice == 1 || choice == 2) {
					inputRight = true;
				}
			} while (!inputRight);

			if (choice == 1) {
				system("cls");
				cmusic.setMediaName("音乐\\打字机L.mp3");
				cmusic.Play();
				printWords_p(4, 5, "在这温馨的氛围下，锋利的剑刃显得格格不入", sleepTime); sleepTime = temp;
				printWords_p(4, 7, "你心想是时候了，你快速提起利剑，向女子刺去", sleepTime); sleepTime = temp;
				printWords_p(4, 9, "你似乎已经看穿了她的阴谋,让女子变成了丑陋的怪物", sleepTime); sleepTime = temp;
				printWords_p(4, 11, "这无比丑陋的怪物被击飞到了空中", sleepTime); sleepTime = temp;
				cmusic.Stop();
				printWords(4, 14, "输入回车进行连击>", 0);
				getch();
				system("cls");

				int row = 0;
				int col = 0;

				for (int j = 0, i = 0; j < 40; j++, i++) {
					srand(i);
					row = rand() % 30 + 5;
					col = rand() % 80 + 5;

					console.SetCoord(col, row);/* system("mode con cols=86 lines=37");*/
					printf("%d连击！！", j);
					setbuf(stdin, nullptr);
					getch();

				}

				Sleep(1000);
				cutscenes();
				setbuf(stdin, nullptr);
				system("cls");
				cmusic.setMediaName("音乐\\打字机L.mp3");
				cmusic.Play();
				printWords(4, 5, "剑刃在空中划出一道道完美的弧线", sleepTime); sleepTime = temp;
				printWords(4, 7, "你没有任何的疑惑，斩钉截铁的把她送去了地狱", sleepTime); sleepTime = temp;
				printWords(4, 9, "伴随着她的死去，周围的一切也逐渐的消失，墙上的壁画、桌上的餐具、还有小兰提。", sleepTime); sleepTime = temp;
				printWords(4, 11, "所有的一切都化为了灰烬,你现在击败了邪恶的国王，等待你的将是数不胜数的名誉和财富，", sleepTime); sleepTime = temp;
				printWords(25, 15, "那可真是极好的呢对于你自己来说。", 100);
				cmusic.Stop();
				printWords(40, 17, "THE END", 100);

				getch();

				exit(0);


			}

			break;
		case 2:
			cutscenes();
			system("cls");
			cmusic.setMediaName("音乐\\打字机L.mp3");
			cmusic.Play();
			printWords_p(4, 5, "在回答完名字的一瞬间，你似乎忘记了来这里的目的", sleepTime); sleepTime = temp;
			cmusic.Stop();
			cmusic.setMediaName("音乐\\CV\\真是个.mp3");
			cmusic.Play();
			printWords_p(4, 7, "神秘女子：真是个勇敢的名字，您一定是和我丈夫一样勇敢的勇士吧！（女子眼睛里闪着光）", sleepTime); sleepTime = temp;
			Sleep(2300);
			cmusic.setMediaName("音乐\\CV\\想那个.mp3");
			cmusic.Play();
			printWords_p(4, 9, "神秘女子：想那个时候，他也和你一样勇敢无畏，四处冒险", sleepTime); sleepTime = temp;
			Sleep(2800);
			cmusic.setMediaName("音乐\\CV\\但最后.mp3");
			cmusic.Play();
			printWords_p(4, 11, "神秘女子：但...但最后...英勇地牺牲在了一次卫国战争里（女子边说边哽咽着）\n\n", sleepTime); sleepTime = temp;
			Sleep(3000);
			cmusic.setMediaName("音乐\\CV\\叔叔.mp3");
			cmusic.Play();
			printWords_p(4, 13, "小兰提：叔叔！你也是消灭那些邪恶怪兽的人吗？！（小兰提突然探出头来好奇地问到", sleepTime); sleepTime = temp;
			Sleep(2500);
			cmusic.setMediaName("音乐\\打字机L.mp3");
			cmusic.Play();
			printWords_p(4, 15, "小兰提羡慕的目光和神秘女人可爱的微笑都映入了你的眼帘", sleepTime); sleepTime = temp;
			printWords_p(4, 17, "你被请到了客厅里闲聊，你和她很聊得很开心\n\n", sleepTime); sleepTime = temp;
			printWords_p(4, 19, "你不知不觉已经忘记了为什么自己要来这里，脑海里都是她的身影\n\n", sleepTime); sleepTime = temp;
			printWords_p(4, 21, "不过，管他呢！现在的你很开心，和小兰提做着游戏，就好像他是自己的孩子一样", sleepTime); sleepTime = temp;
			cmusic.Stop();
			printWords(35, 24, "THE END", 100);

			getch();

			exit(0);
		}
	}
}


RPG::RPG() {

	

	system("mode con cols=86 lines=37");

	map[0][0] = 11, map[0][1] = 11, map[0][2] = 11;  map[0][3] = 11, map[0][4] = 11, map[0][5] = 11;  map[0][6] = 11, map[0][7] = 11, map[0][8] = 11; map[0][9] = 11, map[0][10] = 11, map[0][11] = 11; map[0][12] = 11, map[0][13] = 11, map[0][14] = 11; map[0][15] = 11, map[0][16] = 11, map[0][17] = 11; map[0][18] = 11, map[0][19] = 11, map[0][20] = 11; map[0][21] = 11, map[0][22] = 11, map[0][23] = 11, map[0][24] = 11;
	map[1][0] = 11, map[1][1] = 2, map[1][2] = 0;  map[1][3] = 0, map[1][4] = 0, map[1][5] = 0;  map[1][6] = 0, map[1][7] = 0, map[1][8] = 0; map[1][9] = 0, map[1][10] = 0, map[1][11] = 0; map[1][12] = 0, map[1][13] = 4, map[1][14] = 0; map[1][15] = 0, map[1][16] = 3, map[1][17] = 0; map[1][18] = 0, map[1][19] = 0, map[1][20] = 0; map[1][21] = 0, map[1][22] = 0, map[1][23] = 0, map[1][24] = 11;
	map[2][0] = 11, map[2][1] = 0, map[2][2] = 1;  map[2][3] = 0, map[2][4] = 1, map[2][5] = 1;  map[2][6] = 1, map[2][7] = 1, map[2][8] = 1; map[2][9] = 1, map[2][10] = 1, map[2][11] = 1; map[2][12] = 1, map[2][13] = 1, map[2][14] = 1; map[2][15] = 1, map[2][16] = 1, map[2][17] = 1; map[2][18] = 1, map[2][19] = 1, map[2][20] = 1; map[2][21] = 1, map[2][22] = 1, map[2][23] = 0, map[2][24] = 11;
	map[3][0] = 11, map[3][1] = 0, map[3][2] = 1;  map[3][3] = 4, map[3][4] = 0, map[3][5] = 1;  map[3][6] = 0, map[3][7] = 0, map[3][8] = 0; map[3][9] = 4, map[3][10] = 0, map[3][11] = 0; map[3][12] = 0, map[3][13] = 0, map[3][14] = 0; map[3][15] = 0, map[3][16] = 0, map[3][17] = 4; map[3][18] = 0, map[3][19] = 0, map[3][20] = 0; map[3][21] = 0, map[3][22] = 1, map[3][23] = 1, map[3][24] = 11;
	map[4][0] = 11, map[4][1] = 0, map[4][2] = 1;  map[4][3] = 0, map[4][4] = 1, map[4][5] = 1;  map[4][6] = 1, map[4][7] = 1, map[4][8] = 1; map[4][9] = 1, map[4][10] = 1, map[4][11] = 0; map[4][12] = 0, map[4][13] = 1, map[4][14] = 2; map[4][15] = 0, map[4][16] = 1, map[4][17] = 1; map[4][18] = 1, map[4][19] = 1, map[4][20] = 0; map[4][21] = 0, map[4][22] = 3, map[4][23] = 2, map[4][24] = 11;
	map[5][0] = 11, map[5][1] = 0, map[5][2] = 1;  map[5][3] = 2, map[5][4] = 0, map[5][5] = 0;  map[5][6] = 0, map[5][7] = 0, map[5][8] = 0; map[5][9] = 0, map[5][10] = 1, map[5][11] = 0; map[5][12] = 0, map[5][13] = 1, map[5][14] = 4; map[5][15] = 1, map[5][16] = 1, map[5][17] = 17; map[5][18] = 2, map[5][19] = 1, map[5][20] = 0; map[5][21] = 0, map[5][22] = 0, map[5][23] = 2, map[5][24] = 11;
	map[6][0] = 11, map[6][1] = 0, map[6][2] = 1;  map[6][3] = 1, map[6][4] = 1, map[6][5] = 1;  map[6][6] = 1, map[6][7] = 1, map[6][8] = 1; map[6][9] = 2, map[6][10] = 1, map[6][11] = 4; map[6][12] = 0, map[6][13] = 1, map[6][14] = 1; map[6][15] = 1, map[6][16] = 4, map[6][17] = 2; map[6][18] = 0, map[6][19] = 1, map[6][20] = 1; map[6][21] = 1, map[6][22] = 1, map[6][23] = 0, map[6][24] = 11;
	map[7][0] = 11, map[7][1] = 0, map[7][2] = 1;  map[7][3] = 0, map[7][4] = 0, map[7][5] = 0;  map[7][6] = 2, map[7][7] = 0, map[7][8] = 1; map[7][9] = 4, map[7][10] = 1, map[7][11] = 0; map[7][12] = 0, map[7][13] = 0, map[7][14] = 2; map[7][15] = 1, map[7][16] = 1, map[7][17] = 1; map[7][18] = 0, map[7][19] = 1, map[7][20] = 0; map[7][21] = 0, map[7][22] = 4, map[7][23] = 0, map[7][24] = 11;
	map[8][0] = 11, map[8][1] = 0, map[8][2] = 1;  map[8][3] = 1, map[8][4] = 1, map[8][5] = 1;  map[8][6] = 1, map[8][7] = 0, map[8][8] = 1; map[8][9] = 1, map[8][10] = 1, map[8][11] = 1; map[8][12] = 1, map[8][13] = 1, map[8][14] = 0; map[8][15] = 1, map[8][16] = 4, map[8][17] = 1; map[8][18] = 3, map[8][19] = 1, map[8][20] = 0; map[8][21] = 1; map[8][22] = 0, map[8][23] = 0, map[8][24] = 11;
	map[9][0] = 11, map[9][1] = 0, map[9][2] = 0;  map[9][3] = 2, map[9][4] = 1, map[9][5] = 0;  map[9][6] = 0, map[9][7] = 0, map[9][8] = 4; map[9][9] = 0, map[9][10] = 0, map[9][11] = 0; map[9][12] = 0, map[9][13] = 1, map[9][14] = 0; map[9][15] = 1, map[9][16] = 2, map[9][17] = 1; map[9][18] = 0, map[9][19] = 1, map[9][20] = 0; map[9][21] = 1, map[9][22] = 0, map[9][23] = 0, map[9][24] = 11;
	//0空 墙1 怪物2 商人3 宝箱4 人6 
	map[10][0] = 11, map[10][1] = 3, map[10][2] = 0; map[10][3] = 1, map[10][4] = 1, map[10][5] = 1; map[10][6] = 1, map[10][7] = 1, map[10][8] = 0; map[10][9] = 0, map[10][10] = 0, map[10][11] = 0; map[10][12] = 4, map[10][13] = 1, map[10][14] = 0; map[10][15] = 1, map[10][16] = 0, map[10][17] = 1; map[10][18] = 4, map[10][19] = 0, map[10][20] = 0; map[10][21] = 1, map[10][22] = 2, map[10][23] = 4, map[10][24] = 11;
	map[11][0] = 11, map[11][1] = 0, map[11][2] = 0; map[11][3] = 0, map[11][4] = 0, map[11][5] = 0; map[11][6] = 4, map[11][7] = 1, map[11][8] = 1; map[11][9] = 0, map[11][10] = 1, map[11][11] = 0; map[11][12] = 0, map[11][13] = 1, map[11][14] = 4; map[11][15] = 0, map[11][16] = 0, map[11][17] = 1; map[11][18] = 1, map[11][19] = 1, map[11][20] = 1; map[11][21] = 1, map[11][22] = 1, map[11][23] = 1, map[11][24] = 11;
	map[12][0] = 11, map[12][1] = 0, map[12][2] = 1; map[12][3] = 1, map[12][4] = 1, map[12][5] = 1; map[12][6] = 1, map[12][7] = 1, map[12][8] = 1; map[12][9] = 0, map[12][10] = 1, map[12][11] = 0; map[12][12] = 0, map[12][13] = 1, map[12][14] = 0; map[12][15] = 1, map[12][16] = 1, map[12][17] = 1; map[12][18] = 4, map[12][19] = 3, map[12][20] = 1; map[12][21] = 0, map[12][22] = 0, map[12][23] = 2, map[12][24] = 11;
	map[13][0] = 11, map[13][1] = 0, map[13][2] = 0; map[13][3] = 2, map[13][4] = 0, map[13][5] = 0; map[13][6] = 0, map[13][7] = 4, map[13][8] = 1; map[13][9] = 0, map[13][10] = 1, map[13][11] = 2; map[13][12] = 2, map[13][13] = 1, map[13][14] = 0; map[13][15] = 1, map[13][16] = 2, map[13][17] = 0; map[13][18] = 0, map[13][19] = 0, map[13][20] = 0; map[13][21] = 0, map[13][22] = 1, map[13][23] = 0, map[13][24] = 11;
	map[14][0] = 11, map[14][1] = 1, map[14][2] = 1; map[14][3] = 0, map[14][4] = 1, map[14][5] = 1; map[14][6] = 1, map[14][7] = 0, map[14][8] = 1; map[14][9] = 0, map[14][10] = 1, map[14][11] = 0; map[14][12] = 0, map[14][13] = 1, map[14][14] = 0; map[14][15] = 1, map[14][16] = 0, map[14][17] = 1; map[14][18] = 1, map[14][19] = 1, map[14][20] = 1; map[14][21] = 0, map[14][22] = 1, map[14][23] = 0, map[14][24] = 11;
	map[15][0] = 11, map[15][1] = 2, map[15][2] = 1; map[15][3] = 0, map[15][4] = 1, map[15][5] = 0; map[15][6] = 1, map[15][7] = 0, map[15][8] = 0; map[15][9] = 0, map[15][10] = 1, map[15][11] = 3; map[15][12] = 0, map[15][13] = 1, map[15][14] = 0; map[15][15] = 1, map[15][16] = 0, map[15][17] = 1; map[15][18] = 2, map[15][19] = 1, map[15][20] = 1; map[15][21] = 0, map[15][22] = 1, map[15][23] = 4, map[15][24] = 11;
	map[16][0] = 11, map[16][1] = 0, map[16][2] = 1; map[16][3] = 0, map[16][4] = 1, map[16][5] = 0; map[16][6] = 1, map[16][7] = 3, map[16][8] = 1; map[16][9] = 1, map[16][10] = 1, map[16][11] = 1; map[16][12] = 0, map[16][13] = 1, map[16][14] = 0; map[16][15] = 1, map[16][16] = 0, map[16][17] = 1; map[16][18] = 0, map[16][19] = 0, map[16][20] = 0; map[16][21] = 0, map[16][22] = 1, map[16][23] = 1, map[16][24] = 11;
	map[17][0] = 11, map[17][1] = 0, map[17][2] = 1; map[17][3] = 0, map[17][4] = 0, map[17][5] = 0; map[17][6] = 1, map[17][7] = 0, map[17][8] = 1; map[17][9] = 0, map[17][10] = 0, map[17][11] = 1; map[17][12] = 0, map[17][13] = 1, map[17][14] = 0; map[17][15] = 0, map[17][16] = 4, map[17][17] = 1; map[17][18] = 0, map[17][19] = 1, map[17][20] = 1; map[17][21] = 1, map[17][22] = 1, map[17][23] = 4, map[17][24] = 11;
	map[18][0] = 11, map[18][1] = 3, map[18][2] = 0; map[18][3] = 0, map[18][4] = 1, map[18][5] = 1; map[18][6] = 1, map[18][7] = 1, map[18][8] = 1; map[18][9] = 1, map[18][10] = 4, map[18][11] = 1; map[18][12] = 0, map[18][13] = 1, map[18][14] = 1; map[18][15] = 1, map[18][16] = 1, map[18][17] = 1; map[18][18] = 0, map[18][19] = 1, map[18][20] = 3; map[18][21] = 0, map[18][22] = 0, map[18][23] = 2, map[18][24] = 11;
	map[19][0] = 11, map[19][1] = 0, map[19][2] = 0; map[19][3] = 4, map[19][4] = 0, map[19][5] = 0; map[19][6] = 0, map[19][7] = 1, map[19][8] = 0; map[19][9] = 1, map[19][10] = 0, map[19][11] = 1; map[19][12] = 0, map[19][13] = 0, map[19][14] = 0; map[19][15] = 0, map[19][16] = 1, map[19][17] = 1; map[19][18] = 0, map[19][19] = 1, map[19][20] = 0; map[19][21] = 0, map[19][22] = 0, map[19][23] = 0, map[19][24] = 11;
	map[20][0] = 11, map[20][1] = 1, map[20][2] = 1; map[20][3] = 1, map[20][4] = 1, map[20][5] = 1; map[20][6] = 0, map[20][7] = 1, map[20][8] = 0; map[20][9] = 0, map[20][10] = 2, map[20][11] = 1; map[20][12] = 1, map[20][13] = 1, map[20][14] = 1; map[20][15] = 0, map[20][16] = 1, map[20][17] = 1; map[20][18] = 0, map[20][19] = 1, map[20][20] = 1; map[20][21] = 4, map[20][22] = 1, map[20][23] = 1, map[20][24] = 11;
	map[21][0] = 11, map[21][1] = 4, map[21][2] = 0; map[21][3] = 0, map[21][4] = 0, map[21][5] = 1; map[21][6] = 0, map[21][7] = 1, map[21][8] = 0; map[21][9] = 1, map[21][10] = 0, map[21][11] = 1; map[21][12] = 3, map[21][13] = 4, map[21][14] = 1; map[21][15] = 4, map[21][16] = 0, map[21][17] = 0; map[21][18] = 0, map[21][19] = 0, map[21][20] = 0; map[21][21] = 0, map[21][22] = 0, map[21][23] = 1, map[21][24] = 11;
	map[22][0] = 11, map[22][1] = 10, map[22][2] = 11; map[22][3] = 1, map[22][4] = 0, map[22][5] = 1; map[22][6] = 0, map[22][7] = 1, map[22][8] = 0; map[22][9] = 1, map[22][10] = 0, map[22][11] = 1; map[22][12] = 0, map[22][13] = 0, map[22][14] = 1; map[22][15] = 1, map[22][16] = 1, map[22][17] = 1; map[22][18] = 1, map[22][19] = 1, map[22][20] = 0; map[22][21] = 1, map[22][22] = 0, map[22][23] = 2, map[22][24] = 11;
	map[23][0] = 11, map[23][1] = 16, map[23][2] = 10; map[23][3] = 0, map[23][4] = 3, map[23][5] = 0; map[23][6] = 2, map[23][7] = 0, map[23][8] = 0; map[23][9] = 1, map[23][10] = 0, map[23][11] = 0; map[23][12] = 0, map[23][13] = 0, map[23][14] = 4; map[23][15] = 0, map[23][16] = 0, map[23][17] = 0; map[23][18] = 2, map[23][19] = 1, map[23][20] = 2; map[23][21] = 1, map[23][22] = 2, map[23][23] = 4, map[23][24] = 11;
	map[24][0] = 11, map[24][1] = 11, map[24][2] = 11; map[24][3] = 11, map[24][4] = 11, map[24][5] = 11; map[24][6] = 11, map[24][7] = 11, map[24][8] = 11; map[24][9] = 11, map[24][10] = 11, map[24][11] = 11; map[24][12] = 11, map[24][13] = 11, map[24][14] = 11; map[24][15] = 11, map[24][16] = 11, map[24][17] = 11; map[24][18] = 11, map[24][19] = 11, map[24][20] = 11; map[24][21] = 11, map[24][22] = 11, map[24][23] = 11, map[24][24] = 11;
	

	pixel[0][0] = 1, pixel[0][2] = 0, pixel[0][3] = 0; pixel[0][1] = 0;

	pixel[1][0] = 0, pixel[1][2] = 0, pixel[1][3] = 0; pixel[1][1] = 1;

	pixel[2][0] = 0, pixel[2][2] = 1, pixel[2][3] = 0; pixel[2][1] = 0;

	pixel[3][0] = 0, pixel[3][2] = 0, pixel[3][3] = 1; pixel[3][1] = 0;

	character_x = *character.getPosition();
	character_y = *(character.getPosition() + 1);

	console.HideCursor(true);
}

void RPG::gameStart() {
	startAnimation();	//开场动画

						//登陆界面
	if (!login()) {
		drama(65);
	}

	while (!game_over) {
		beforeRound();	//回合前
		startRound();	//回合中
		afterRound();	//回合后
	}

 	gameOver(0);
	goodEnd(65);
	return;
}
