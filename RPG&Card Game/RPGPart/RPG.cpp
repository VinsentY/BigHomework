#include "RPG.h"
using namespace std;

CMusic cmusic;

int main() {

	RPG rpg;
	//�ƶ�����ģ��
	
	rpg.gameStart();

	return 0;
}

void RPG::beforeRound() {

	bool firstDraw = false;
	if (!firstDraw) {
		refreshMap();
		firstDraw = true;
	}
	

	//������д������Ĵ���
	static bool isPrint_1 = false;
	static bool isPrint_2 = false;
	static bool isPrint_3 = false;
	static bool isPrint_4 = false;
	static bool isPrint_5 = false;
	static bool isPrint_6 = false;

// 	if (killNum >= 10) {
// 		printWords(52, 15, "���µ���Ϊֹ��",65);
// 		cutscenes();
// 		goodEnd(65);
// 	}

	if (rounds == 1 && !isPrint_1) {
		printWords(52, 15, "���ʾ��ǰ�������ڵ�λ��(���½�)", 15);
		printWords(57, 17, "��������ѡ�񣬻س�ȷ��", 15);
		printWords(61, 19, "��ʼ���ð�հɣ�", 10);
		isPrint_1 = true;
	} else if (rounds == 10 && !isPrint_2) {
		printWords(52, 15, "�Թ��з�����һ�������Ĳҽ�",65);
		printWords(52, 17, "���ų�΢���ĺ��",65);
		printWords(52, 19, "��ӿ�����ǰ���ĽŲ�",65);

		isPrint_2 = true;
	} else if (rounds == 20 && !isPrint_3) {
		printWords(52, 15, "�����Խ��Խǿ��ǿ",65);
		printWords(52, 17, "��������㶼��������",65);
		printWords(52, 19, "�Թ��еĹ���Ҳ�����������",65);
		
		isPrint_3 = true;
	} else if (rounds == 30 &&  !isPrint_4 ) {
		printWords(52, 15, "���ɹ�ǿ������",65);
		printWords(52, 17, "���﹥����ȫ�� + 1",65);
		character.addAfraid();
		isPrint_4 = true;
	} else if (rounds == 40 && !isPrint_5) {
		printWords(52, 15, "�������ޱȿ���",65);
		printWords(52, 17, "���﹥����ȫ�� + 1",65);
		character.addAfraid();
		isPrint_5 = true;
	} else if (rounds == 50 && !isPrint_6) {
		printWords(52, 15, "�����Ǳ��ƺ�����˹�����ɶ�",65);
		printWords(52, 17, "���﹥����ȫ�� + 1",65);
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
	//Ѫ������
	//����������
	//ʧȥ�ж���
}


void RPG::startAnimation() {

	console.SetColor("07");
	drawVICU(5, 5, "��", 25);
	console.SetColor("70");

	drawVICU(7, 5, "��", 15);

	console.SetColor("07");

	system("cls");

	cmusic.setMediaName("����\\��.wav");
	cmusic.Play();

	for (int i = 0; i < 6; i++) {
		if (kbhit()) {
			getch();
			break;
		}
		drawVICU(7 + i * 2, 5 + i, "��", 0);
		Sleep(250);
		drawVICU(7 + i * 2, 5 + i, "  ", 0);

	}
	cmusic.setMediaName("����\\���ɱ���.mp3");
	cmusic.Play();
	drawVICU(19, 10, "��", 0);


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

	char *words[3] = { "��ʼ��Ϸ", "������Ϸ" , "��������" };

	drawVICU(19, 10, "��", 0);

	console.SetCoord(15, 2);
	cout << "�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k";
	console.SetCoord(15, 35);
	cout << "�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k�k";//�ò�����ʾ������������
	console.SetCoord(65, 32);
	cout << "��";
	console.SetCoord(63, 33);
	cout << "�u";
	console.SetCoord(65, 33);
	cout << "��";
	console.SetCoord(67, 33);
	cout << "�v";
	console.SetCoord(65, 34);
	cout << "��";//�ò�����ʾС��
	console.SetCoord(58, 34);
	cout << "�^";
	console.SetCoord(60, 34);
	cout << "�a";
	console.SetCoord(58, 33);
	cout << "�X";
	console.SetCoord(60, 33);
	cout << "�[";//�ò�����ʾС����
	console.SetCoord(59, 32);
	cout << "��";//��ʾ����������ʺ�

	console.SetCoord(35, 5);
	cout << "ʹ�á��� ѡ����";

	console.SetCoord(30, 20);
	cout << "��";
	console.SetCoord(34, 20);
	cout << words[0];

	console.SetCoord(34, 24);
	cout << words[1];

	console.SetCoord(34, 28);
	cout << words[2];

	setbuf(stdin, NULL);

	while (true) {
		static int i = 0;
		int shineSpeed = 10000;//��ֵ��ʾ��½�����ʺ��������ٶȣ���ֵԽ�������ٶ�Խ��
		if (i < 10000) {
			i++;
			console.SetCoord(59, 32);
			if (i >= 0 && i < (shineSpeed / 2))
				cout << "��";
			if (i >= (shineSpeed / 2) && i < shineSpeed)
				cout << "��";
			if (i == shineSpeed)
				i = 0;
		}//�ò����õ�½����С�����ϵ��ʺ�����

		if (kbhit()) {
			input = getch();
			switch (input) {
			case 72:
				//��
				if (choice == 0) {
					continue;
				}
				choice--;

				break;
			case 80:
				//��
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
					cout << "��";
					cout << "            ";
					printWords(34, 20, words[choice], 35);
				} else {
					cout << "  ";
				}
				console.SetCoord(30, 24);
				if (arr[choice][1] != 0) {
					cout << "��";
					cout << "            ";
					printWords(34, 24, words[choice], 35);
				} else {
					cout << "  ";
				}
				console.SetCoord(30, 28);
				if (arr[choice][2] != 0) {
					cout << "��";
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
	cmusic.setMediaName("����\\���ֻ�L.mp3");
	cmusic.Play();
	printWords_p(25, 8, "������������һλа����ڿ�˹����", sleepTime);

	printWords_p(19, 10, "������ͳ���£�����ˮ����ȣ��������е�ϣ����һλ��ʿ", sleepTime);

	printWords_p(19, 12, "�����¸ҵ�վ����ȥ������λа��Ĺ������������������", sleepTime);

	printWords_p(35, 14, "��������·��....", sleepTime);
	cmusic.Stop();
	setbuf(stdin, nullptr);
	getch();
	sleepTime = temp;
	system("cls");
	cmusic.Play();
	printWords_p(25, 8, "����ǰ��а������ĳǱ���·��", sleepTime);

	printWords_p(14, 10, "������һλ��̫̫��ֻ����������һ�ۣ������������Ұ����˵��", sleepTime);

	printWords_p(9, 14, "��̫̫��������ʿ���մ����ǣ�", sleepTime);

	printWords_p(9, 16, "��ش��(�ݲ�֧������)��", sleepTime);
	cmusic.Stop();

	string name = character.setName();

	cmusic.Play();
	printWords_p(9, 18, "��̫̫��", sleepTime);
	console.SetCoord(17, 18);
	cout << name;
	Sleep(800);

	printWords_p(9, 20, "��̫̫���ǿ����Ǹ����˵�����,�����������ҵĺ��� Lanteen", sleepTime);
	printWords_p(9, 22, "��̫̫����Ҳ����һ����η����ʿ...", sleepTime);
	printWords_p(9, 24, "��̫̫��С���ӣ�����˵а��Ĺ���ʮ��ǿ�󣬲����ҵ���һ�޶�����������ɱ����", sleepTime);
	printWords_p(9, 26, "��̫̫����������һ�� ���������������ıʼǣ�����һ�������ð�ջ��а�����", sleepTime);
	printWords_p(9, 28, "��̫̫����Ұ����������ָ����Ҳ���˻��֣��������˱ʼ�...", sleepTime);
	printWords_p(9, 30, "�س����ıʼ� >> ", sleepTime);
	cmusic.Stop();

	setbuf(stdin, nullptr);
	getch();
	sleepTime = temp;
	system("cls");
	cmusic.Play();
	printWords_p(29, 8, "�ʼ��ϼ�¼���������������", sleepTime);
	printWords_p(24, 10, "ȫ���Ƕ�а����������������ҵ�����仯", sleepTime);
	printWords_p(22, 12, "�㷭�������һҳ��ֻ�������ü��صı�īд����", sleepTime);
	printWords_p(26, 18, "\"����������Ԩ����ԨҲ����������\"", sleepTime);
	cmusic.Stop();
	Sleep(2000);
	cmusic.Play();
	printWords_p(28, 22, "������һЩĪ��������ĸ", sleepTime);
	printWords_p(38, 24, "VICU", sleepTime);  //638547
											  //�����֧	
	printWords_p(24, 28, "��û�п�����д��Щʲô��ֻ�ü���������", sleepTime);
	cmusic.Stop();
	Sleep(1500);
	cmusic.setMediaName("����\\���ر���.mp3");
	cmusic.Play();
	sleepTime = temp;
	system("cls");
	printWords_p(22, 6, "������а��Ǳ��Ĵ�����ǰ����Ϸ��ʽ��ʼ", sleepTime);
	printWords(2, 10, "�ƶ����Ǳ�����(��)���谭�����Ұ���ƶ�����������������һ�غ�", 10);
	printWords(2, 14, "���򣺵�����������Ϊ(��)������ʱ�����Ὺʼ��Ʒ�������������Ʒ�ﹺ������Ҫ�Ķ���", 10);
	printWords(2, 18, "���䣺������������Ϊ(��)�ı���ʱ����ͻ���һ���Ľ����������м��ʻ������װ���͵���", 10);
	printWords(2, 22, "ս����������������Ϊ(��)�Ĺ���ʱ�����ᴥ������ս����һ��һ��Ѫ����Ϊ0��ս�����̽���", 10);
	printWords(2, 26, "Ŀ��: ���ܳǱ��е�а�����( �w )������Ҫ�����ҵ�����ɱ����", 10);
	printWords(32, 30, "�س��ƿ��Ǳ����� >>", sleepTime);

	setbuf(stdin, nullptr);
	getch();
	cmusic.Stop();
	cmusic.setMediaName("����\\����2.mp3");
	cmusic.Play();
	//���빤��

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
					cout << "��";
				} else {
					cout << "  ";
				}
			} else {
				if (j % v2 == 0) {
					cout << "  ";
				} else {
					cout << "��";
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
	cout << "ʹ����Ʒ��";

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
				//��
				if (row == 0) {
					break;
				}
				row--;
				break;
			case 80:
				//��
				if (row == 1) {
					break;
				}
				row++;
				break;
			case 75:
				//��
				if (col == 0) {
					break;
				}
				col--;
				break;
			case 77:
				//��
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
				//��
				if (map[y - 1][x / 2] != WALL + 10) {
					p = UP;
					drawMove(x, y, UP);
				}
				input = ' ';
				break;
			case 80:
				//��
				if (map[y + 1][x / 2] != WALL + 10) {
					p = DOWN;
					drawMove(x, y, DOWN);
				}
				input = ' ';
				break;
			case 75:
				//��
				if (map[y][x / 2 - 1] != WALL + 10) {
					p = LEFT;
					drawMove(x, y, LEFT);
				}
				input = ' ';
				break;
			case 77:
				//��
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

		// 1 ��ҩˮ
		// 2�� �޽�
		// 3�� ����
		// 4�� Ь��
		// 5:  �������

	case MONSETER:
		cutscenes();
		setbuf(stdin, nullptr);
		if (character.fightToMonster()) {
			cutscenes();
			refreshData();
			refreshMap();
			console.SetCoord(51, 16);
			if (character.addItem(*(new Item("���ﱦ��", 5, 6, 0, "Duang~")))) {
				cout << "�����˹������ı���!";
			}		
			console.SetCoord(51, 18);
			srand(time(NULL));
			switch (rand() % 10 + 1) {
			case 1:
			case 2:
				if (character.addItem(*(new Item("С�ͻظ�ҩ��", 1, 0, 3, "ζ����������ĺ���ˮ")))) {
					cout << "������һƿС��HPҩˮ";
				}		
				break;
			case 3:
			case 4:
			case 5:
			case 6:
				if (character.addItem(*(new Item("HPҩˮ", 1, 0, 7, "���Ӵ����HPҩˮ")))) {
					cout << "������һƿHPҩˮ";
				}		
				break;
			case 7:
				if (character.addItem(*(new Item("���տ���", 6, 0, 0, "��ͨ���ѵ���ͨ�ؿ�")))) {
					cout << "������һ�����պؿ�";
				}			
				break;
			case 8:
				if (character.addItem(*(new Item("<For River>", 6, 0, 0, "��һ����û�������ĳ�Ƭ")))) {
					cout << "������һ��<For River>��CD��Ƭ";
				}
				
				break;
			case 9:
				if (character.addItem(*(new Item("��ɫʮ�ּ�", 6, 0, 0, "��������һ���ܺ��Ū������")))) {
					cout << "��������Щȱ�ڵĺ�ɫʮ�ּ�";
				}
				
				break;
			case 10:
				if (character.addItem(*(new Item("�ռ��ظ�ҩˮ", 1, 0, 15, "��������������")))) {
					cout << "�������ռ��ظ�ҩˮ";
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
// 			map[i][j] -= 10;	//��ò��ɼ�			
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
				map[i][j] += 10;	//��ÿɼ�
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

	//�ֲ�ˢ��
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
	cout << "��ǰ�غ�: " << rounds;

	character.printInterface();

}

void RPG::drawMove(int x, int y, Operator p) {

	bool isDraw = false;

	int j = 0;

	console.SetCoord(62, 24);
	cout << "��ɫ�ƶ���";

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
	//������
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
		cout << "��";
		console.SetCoord(65, 15 - n);
		cout << "��";
		console.SetCoord(63, 16 - n);
		cout << "��";
		console.SetCoord(65, 16 - n);
		cout << "��";
		console.SetCoord(67, 16 - n);
		cout << "��";
		console.SetCoord(65, 17 - n);
		cout << "��";//�ò�����ʾС��
		Sleep(sleepTime2);
		if (n != 9) {
			console.SetCoord(65, 14 - n);
			cout << "��";
			console.SetCoord(65, 15 - n);
			cout << "��";
			console.SetCoord(63, 16 - n);
			cout << "��";
			console.SetCoord(65, 16 - n);
			cout << "��";
			console.SetCoord(67, 16 - n);
			cout << "��";
			console.SetCoord(65, 17 - n);
			cout << "��";//�ò��ֲ���С��
		}
		sleepTime2 += 20;
	}




	while (true) {
		static int i = 0;
		int shineSpeed = 30000;//��ֵ��ʾ��������⻷�������ٶȣ���ֵԽ�������ٶ�Խ��
		if (i < shineSpeed) {
			i++;
			console.SetCoord(65, 5);
			if (i >= 0 && i < (shineSpeed / 3))
				cout << "��";
			if (i >= (shineSpeed / 3) && i < shineSpeed)
				cout << "��";
			if (i == shineSpeed)
				i = 0;
		}//�ò�������������С��ͷ�ϵĹ⻷����

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
	cout << "��������";
	int iniy = 5;
	int col = 4;
	for (int n = 20; n > 0; n--) {
		console.SetCoord(8, iniy + n);
		cout << "����     ������������������������������������������������ VICUС��";
		console.SetCoord(8, iniy + n + col);
		cout << "�ܸ����� ������������������������������������������������ ��ܲ��";
		console.SetCoord(8, iniy + n + col * 2);
		cout << "������� ������������������������������������������������ ��־��";
		if (iniy + n + col * 3 < 37) {
			console.SetCoord(8, iniy + n + col * 3);
			cout << "��������������� ���������������������������������������� ����";
		}
		if (iniy + n + col * 4 < 37) {
			console.SetCoord(8, iniy + n + col * 4);
			cout << "���ش��� ������������������������������������������������ ��";
		}
		if (iniy + n + col * 5 < 37) {
			console.SetCoord(8, iniy + n + col * 5);
			cout << "���ų��� ������������������������������������������������ ���غ�����";
		}
		if (iniy + n + col * 6 < 37) {
			console.SetCoord(8, iniy + n + col * 6);
			cout << "            ����������ˮƽ���ޣ�bug�������⣬������Һ�����";
		}
		Sleep(500);
		if (n != 1) {
			console.SetCoord(8, iniy + n);
			cout << "������������������������������������������������������������������";
			console.SetCoord(8, iniy + n + col);
			cout << "������������������������������������������������������������������";
			console.SetCoord(8, iniy + n + col * 2);
			cout << "������������������������������������������������������������������";
			if (iniy + n + col * 3 < 37) {
				console.SetCoord(8, iniy + n + col * 3);
				cout << "������������������������������������������������������������������";
			}
			if (iniy + n + col * 4 < 37) {
				console.SetCoord(8, iniy + n + col * 4);
				cout << "������������������������������������������������������������������  ";
			}
			if (iniy + n + col * 5 < 37) {
				console.SetCoord(8, iniy + n + col * 5);
				cout << "������������������������������������������������������������������  ";
			}
			if (iniy + n + col * 6 < 37) {
				console.SetCoord(8, iniy + n + col * 6);
				cout << "����������������������������������������������������������������";
			}
		}

	}

	getch();
	system("cls");
}


void RPG::goodEnd(int sleepTime) {
	system("cls");
	int temp = sleepTime;
	cmusic.setMediaName("����\\���ֻ�L.mp3");
	cmusic.Play();
	printWords_p(4, 5, "����ķ�����ʮ���������;ߺͱڻ�������ķ�����Ӧ���ڵĵط�", sleepTime); sleepTime = temp;
	printWords_p(4, 7, "�����ﴫ��С���ӵĻ�Ц���÷��������ܰ", sleepTime); sleepTime = temp;
	printWords_p(4, 9, "���㶼���������մ��Ѫ�Ľ��Ͷ���", sleepTime); sleepTime = temp;
	printWords_p(4, 11, "��ʱ���ӷ������߳�һλ��ȶ��˵�Ů�ӣ���һϮ��ɴ��ñ���ϱ��ż���ո�ժ�µ��ʻ���", sleepTime); sleepTime = temp;
	cmusic.Stop();
	cmusic.setMediaName("����\\CV\\��ѽ.mp3");
	cmusic.Play();
	printWords_p(4, 14, "����Ů�ӣ���ѽ����ѽ��", sleepTime); sleepTime = temp;
	Sleep(1000);
	cmusic.setMediaName("����\\CV\\С����.mp3");
	cmusic.Play();
	printWords_p(4, 16, "����Ů�ӣ�С���ᣡ�����д����ˣ�Ӧ��һ��С���ı����������˳���������Ů�Ӻ��棩", sleepTime); sleepTime = temp;
	cmusic.setMediaName("����\\CV\\����.mp3");
	cmusic.Play();
	printWords(4, 18, "����Ů�ӣ����ʿ�������������...\n\n", sleepTime);
	printWords(4, 20, "-------------------------------------\n\n", 0);
	printWords(4, 22, "1.��û�лش�ѡ���˳�Ĭ�۲�\n\n", 0);
	printWords(4, 24, "2.���,������Ůʿ����ش����������\n\n", 0);
	printWords(4, 26, "-------------------------------------\n\n", 0);

	printWords(4, 27, "���ѡ����>>", 0);

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
			cmusic.setMediaName("����\\���ֻ�L.mp3");
			cmusic.Play();
			printWords_p(4, 5, "Ů�Ӷ���ĳ�Ĭ�е�����", sleepTime); sleepTime = temp;
			cmusic.Stop();
			cmusic.setMediaName("����\\CV\\��ǧ��.mp3");
			cmusic.Play();
			printWords_p(4, 7, "����Ů�ӣ���ǧ��Ҫ����������⵱���Լ��ļ�һ��!", sleepTime); sleepTime = temp;
			Sleep(2200);
			cmusic.setMediaName("����\\CV\\��һ��.mp3");
			cmusic.Play();
			printWords_p(4, 9, "����Ů�ӣ�С����!�������ȥ������һ����С���ỹ�Ǻܺ��ߵĶ���Ů�Ӻ��棩", sleepTime); sleepTime = temp;

			printWords(4, 12, "-------------------------------------", 0);
			printWords(4, 14, "1.��û�ж���ͬʱ�ս������д�Ѫ�Ľ�", 0);
			printWords(4, 16, "2.������˼��Ůʿ��Ϊ�ղŵ������ʾ��Ǹ����ش����������", 0);
			printWords(4, 18, "-------------------------------------", 0);
			printWords(4, 19, "���ѡ����>>", 0);

			do {
				cin >> choice;
				if (choice == 1 || choice == 2) {
					inputRight = true;
				}
			} while (!inputRight);

			if (choice == 1) {
				system("cls");
				cmusic.setMediaName("����\\���ֻ�L.mp3");
				cmusic.Play();
				printWords_p(4, 5, "������ܰ�ķ�Χ�£������Ľ����Եø����", sleepTime); sleepTime = temp;
				printWords_p(4, 7, "��������ʱ���ˣ������������������Ů�Ӵ�ȥ", sleepTime); sleepTime = temp;
				printWords_p(4, 9, "���ƺ��Ѿ�������������ı,��Ů�ӱ���˳�ª�Ĺ���", sleepTime); sleepTime = temp;
				printWords_p(4, 11, "���ޱȳ�ª�Ĺ��ﱻ���ɵ��˿���", sleepTime); sleepTime = temp;
				cmusic.Stop();
				printWords(4, 14, "����س���������>", 0);
				getch();
				system("cls");

				int row = 0;
				int col = 0;

				for (int j = 0, i = 0; j < 40; j++, i++) {
					srand(i);
					row = rand() % 30 + 5;
					col = rand() % 80 + 5;

					console.SetCoord(col, row);/* system("mode con cols=86 lines=37");*/
					printf("%d��������", j);
					setbuf(stdin, nullptr);
					getch();

				}

				Sleep(1000);
				cutscenes();
				setbuf(stdin, nullptr);
				system("cls");
				cmusic.setMediaName("����\\���ֻ�L.mp3");
				cmusic.Play();
				printWords(4, 5, "�����ڿ��л���һ���������Ļ���", sleepTime); sleepTime = temp;
				printWords(4, 7, "��û���κε��ɻ�ն�������İ�����ȥ�˵���", sleepTime); sleepTime = temp;
				printWords(4, 9, "������������ȥ����Χ��һ��Ҳ�𽥵���ʧ��ǽ�ϵıڻ������ϵĲ;ߡ�����С���ᡣ", sleepTime); sleepTime = temp;
				printWords(4, 11, "���е�һ�ж���Ϊ�˻ҽ�,�����ڻ�����а��Ĺ������ȴ���Ľ�������ʤ���������ͲƸ���", sleepTime); sleepTime = temp;
				printWords(25, 15, "�ǿ����Ǽ��õ��ض������Լ���˵��", 100);
				cmusic.Stop();
				printWords(40, 17, "THE END", 100);

				getch();

				exit(0);


			}

			break;
		case 2:
			cutscenes();
			system("cls");
			cmusic.setMediaName("����\\���ֻ�L.mp3");
			cmusic.Play();
			printWords_p(4, 5, "�ڻش������ֵ�һ˲�䣬���ƺ��������������Ŀ��", sleepTime); sleepTime = temp;
			cmusic.Stop();
			cmusic.setMediaName("����\\CV\\���Ǹ�.mp3");
			cmusic.Play();
			printWords_p(4, 7, "����Ů�ӣ����Ǹ��¸ҵ����֣���һ���Ǻ����ɷ�һ���¸ҵ���ʿ�ɣ���Ů���۾������Ź⣩", sleepTime); sleepTime = temp;
			Sleep(2300);
			cmusic.setMediaName("����\\CV\\���Ǹ�.mp3");
			cmusic.Play();
			printWords_p(4, 9, "����Ů�ӣ����Ǹ�ʱ����Ҳ����һ���¸���η���Ĵ�ð��", sleepTime); sleepTime = temp;
			Sleep(2800);
			cmusic.setMediaName("����\\CV\\�����.mp3");
			cmusic.Play();
			printWords_p(4, 11, "����Ů�ӣ���...�����...Ӣ�µ���������һ������ս���Ů�ӱ�˵�������ţ�\n\n", sleepTime); sleepTime = temp;
			Sleep(3000);
			cmusic.setMediaName("����\\CV\\����.mp3");
			cmusic.Play();
			printWords_p(4, 13, "С���᣺���壡��Ҳ��������Ща����޵����𣿣���С����ͻȻ̽��ͷ��������ʵ�", sleepTime); sleepTime = temp;
			Sleep(2500);
			cmusic.setMediaName("����\\���ֻ�L.mp3");
			cmusic.Play();
			printWords_p(4, 15, "С������Ľ��Ŀ�������Ů�˿ɰ���΢Ц��ӳ�����������", sleepTime); sleepTime = temp;
			printWords_p(4, 17, "�㱻�뵽�˿��������ģ���������ĵúܿ���\n\n", sleepTime); sleepTime = temp;
			printWords_p(4, 19, "�㲻֪�����Ѿ�������Ϊʲô�Լ�Ҫ������Ժ��ﶼ��������Ӱ\n\n", sleepTime); sleepTime = temp;
			printWords_p(4, 21, "�����������أ����ڵ���ܿ��ģ���С����������Ϸ���ͺ��������Լ��ĺ���һ��", sleepTime); sleepTime = temp;
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
	//0�� ǽ1 ����2 ����3 ����4 ��6 
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
	startAnimation();	//��������

						//��½����
	if (!login()) {
		drama(65);
	}

	while (!game_over) {
		beforeRound();	//�غ�ǰ
		startRound();	//�غ���
		afterRound();	//�غϺ�
	}

 	gameOver(0);
	goodEnd(65);
	return;
}
