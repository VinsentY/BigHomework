#include "Character.h"
#include"GAME.h"
#include "Monster.h"
using namespace std;

bool Character::fightToMonster() {

	GAME game(this);
	game.start();
	game.draw();
	bool isWin = game.play();

	console.SetColor("07");

	return isWin;
}

int Character::buyItemFromSeller(vector<Item> commodities) {
	int choice = 0;

	bool inputRight = false;
		
	do {
		console.SetCoord(81, 19);
		setbuf(stdin, nullptr);
		choice = getch() - '0';
		if (choice == 0) {
			return choice;
		} else if (choice > 0 && choice <= commodities.size()) {
			inputRight = true;
		} else {
			console.SetCoord(51, 19);
			cout << "��������ȷ��ѡ��(0��Ž�������)   ";
		}	
	} while (!inputRight);
	

	int price = commodities[choice - 1].getPrice();


	console.SetCoord(51, 20);
	if (goldCoin >= price && addItem(commodities[choice - 1])) {
		goldCoin -= price;
		cout << "����ɹ�";
	} else {
		cout << "����ʧ��";
	}
	console.SetCoord(51, 21);
	cout << "������ :" << goldCoin << endl;

	console.SetCoord(35, 35);
	cout << "������: " << goldCoin << "  ";
	getch();
	return choice;
}

void Character::openTreasure(bool canBeTrick) {
	console.SetCoord(51, 18);
	cout << name << "�򿪱���";
	
	Treasure* temp = new Treasure();

	if (canBeTrick = false && temp->isTrick()) {
		console.SetCoord(51, 20);
		cmusic.setMediaName("����\\��Ѫ.mp3");
		cmusic.Play();
		cout << "������Ķ���������ҧ����һ��";
		console.SetCoord(51, 22);
		cout << name << "��ʧ��5��������";
		Now_HP -= 5;
	} else if(temp->isCoin()) {
		console.SetCoord(51, 20);
		cmusic.setMediaName("����\\���.mp3");
		cmusic.Play();
		cout << "�����﷢�Ž�⣡";
		console.SetCoord(51, 22);
		cout << "������" << temp->getCoinNumber() << "���!";
		goldCoin += temp->getCoinNumber();
	} else {
		srand(time(NULL));
		int num = rand() % (temp->getItems().size());
		console.SetCoord(51, 20);
		cmusic.setMediaName("����\\��.wav");
		cmusic.Play();
		if (addItem(temp->getItems().at(num))) {
			cout << "������" << temp->getItems().at(num).getName();
		}
		
		

	}
	Sleep(600);
}

const int * Character::getPosition() {
	int arr[2] = { x, y };
	return arr;
}



// void Character::showItems() {
// 
// 	for (Item temp : items) {
// 		cout << temp;
// 	}
// }

Character::Character() :Full_HP(30), Now_HP(30), damage_buff_debuff(0), revert_buff_debuff(0) {
	x = 2;
	y = 23;

	goldCoin = 20;

	level = 1;
	name = "VICUER";

	Now_HP = 30;
	
	speed = 2;
	power = 1;

	sword.setItem("�ƾɵľ޽�");
	shield.setItem("�ƾɵĶ���");
	shoes.setItem("�ƾɵ�Ь��");
	
}

void Character::move(Operator p) {
	switch (p) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x -= 2;
		break;
	case RIGHT:
		x += 2;
		break;
	}	
}

void Character::useItem(int row, int col) {
	if (col + row * 3 >= items.size()) {
		console.SetCoord(52, 16);
		cout << "��ʹ�ÿ������ҿ�����������ã�";
	} else {
		
		// 1 ��ҩˮ
		// 2�� �޽�
		// 3�� ����
		// 4�� Ь��
		// 5:  �������
		// 6:  ����

		string str;
		int index = col + row * 3;
		
		int revert_hp = 0;

		switch (items[index].getNumber()) {
		case 1:		
			console.SetCoord(52, 16);
			cout << items[index].getName();
			console.SetCoord(52, 18);
			cout << items[index].getIntro();
			console.SetCoord(52, 20);
			if (items[index].getAttribute() + Now_HP > Full_HP) {
				revert_hp = Full_HP - Now_HP;
				Now_HP = Full_HP;
			} else {
				revert_hp = items[index].getAttribute();
				Now_HP += items[index].getAttribute();
			}
			cout << "��ʹ����ҩˮ���ָ���" << revert_hp << "��Ѫ��";
			console.SetCoord(52, 22);
			cout << "��ǰѪ��: " << Now_HP;
			break;
		case 2:
			cmusic.setMediaName("����\\װ��.mp3");
			cmusic.Play();
			console.SetCoord(52, 16);
			cout << items[index].getName() ;
			console.SetCoord(52, 18);
			cout << items[index].getIntro();
			console.SetCoord(52, 20);
			cout << "�ɹ�װ��!";
			console.SetCoord(52, 22);

			power -= sword.getAttribute();
			sword = items[index];
			power += sword.getAttribute();

			cout << "��ǰ������: " << power;
			break;
		case 3:
			cmusic.setMediaName("����\\װ��.mp3");
			cmusic.Play();
			console.SetCoord(52, 16);
			cout << items[index].getName();
			console.SetCoord(52, 18);
			cout << items[index].getIntro();
			console.SetCoord(52, 20);
			cout << "�ɹ�װ��!";
			console.SetCoord(52, 22);

			Full_HP -= shield.getAttribute();		

			shield = items[index];

			Full_HP += shield.getAttribute();


			cout << "���������������: " << Full_HP;
			break;
		case 4:
			cmusic.setMediaName("����\\װ��.mp3");
			cmusic.Play();
			console.SetCoord(52, 16);
			cout << items[index].getName();
			console.SetCoord(52, 18);
			cout << items[index].getIntro();
			console.SetCoord(52, 20);
			cout << "�ɹ�װ��!";
			console.SetCoord(52, 22);

			speed -= shoes.getAttribute();
			shoes = items[index];
			speed += shoes.getAttribute();

			cout << "��ǰ����������: " << speed;
			break;
		case 5:
			openTreasure(false);
			break;
		case 6:
			console.SetCoord(52, 16);
			cout << items[index].getName();
			console.SetCoord(52, 18);
			cout << items[index].getIntro();

	
			console.SetCoord(52, 22);
			cout << "������һ����Щ���õ�����" ;
			break;
		case 7:
			break;

		}
		
		items.erase(items.begin() + col + row * 3);
	}
		
	getch();
}


bool Character::addItem(Item item) {

	if (items.size() < 6) {
		items.push_back(item);
		return true;
	} else {
		console.SetCoord(50, 16);
		cout << "����̫���ˣ���װ�����κζ���������";
		return false;
	}
}

int Character::getSpeed() {
	return speed;
}

void Character::printInterface() {
	console.SetCoord(50, 0);
	cout << "--------------������--------------";
	console.SetCoord(51, 1);
	cout << "��ʿ��" << left << setw(16) << name << "  �ȼ��� " << level;
	console.SetCoord(51, 3);
	cout << "����: " << power << " ������: " << Now_HP << "/" << Full_HP << " ����: " << speed;
	console.SetCoord(50, 4);
	cout << "--------------װ����--------------";
	console.SetCoord(51, 5);
	cout << "        ������ " << sword.getName();
	console.SetCoord(51, 6);
	cout << "        ���ƣ� " << shield.getName();
	console.SetCoord(51, 7);
	cout << "        Ь�ӣ� " << shoes.getName();
	console.SetCoord(50, 8);
	cout << "--------------�Ի���--------------";
	console.SetCoord(50, 24);
	cout  << "----------------------------------";
	console.SetCoord(0, 26);
	cout << "------------------------------------��Ʒ��------------------------------------------";

	int i = 0;
	int j = 0;
	// iΪ�У� jΪ��

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			console.SetCoord(10 + j * 30, 30 + i * 2);
			if (j + i * 3 >= items.size()) {
				cout << "��";
			} else {
				cout << items[j + i * 3].getName();
			}

		}
	}


	console.SetCoord(35, 35);

	cout << "������: " << goldCoin;

	console.SetCoord(50 ,25);
	cout << "�������� �ƶ�";
	
	cout << "  E ��Ʒ��";

	cout << "  ESC �˳�";
}

string Character::setName() {
	string name = "VICU";

	console.SetCoord(34, 16);
	//���ǲ�����ȷ��ȡ����
	cin >> name;
	this->name = name;

	return name;
}

void Character::levelUp() {
	level++;
	power++;
	Now_HP = Full_HP;

	console.SetCoord(51, 10);
	cout << "��ϲ�������ˣ�";

	console.SetCoord(51, 12);

	cout << "�������ӣ�";
	console.SetCoord(51, 14);

	cout << "��ǰ�ȼ���" << level;

}






int Character::play(Monster npc) {
	int cur;
	while (1) {
		if (GetAsyncKeyState('Q') & 0x8000) {
			cur = 0;
			break;
		} else if (GetAsyncKeyState('W') & 0x8000) {
			cur = 1;
			break;
		} else if (GetAsyncKeyState('E') & 0x8000) {
			cur = 2;
			break;
		} else if (GetAsyncKeyState('R') & 0x8000) {
			cur = 3;
			break;
		} else if (GetAsyncKeyState('T') & 0x8000) {
			cur = 4;
			break;
		} else if (GetAsyncKeyState('Y') & 0x8000) {
			cur = 5;
			break;
		} else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {
			cur = -1;
			break;
		}
	}
	return cur;
}
void Character::be_damaged(int num) {
	Now_HP -= ((num + damage_buff_debuff) > 0 ? (num + damage_buff_debuff) : 0);
}
void Character::Revert_HP(int num) {
	Now_HP += ((num + revert_buff_debuff) > 0 ? (num + revert_buff_debuff) : 0);
	Now_HP = Now_HP < Full_HP ? Now_HP : Full_HP;
}
void Character::_draw_card(int num) {
	
	srand((unsigned)time(NULL));
	for (int i = 0; i < num; i++) {
		int index = rand() % cardhouse.size();
		auto p1 = cardhouse.begin() + index;
		if (handhold.size() < 6) {
			handhold.push_back(*p1);
		}
		cardhouse.erase(p1);
	}
}

//��俨��
void Character::initcard() {

	cardhouse.clear();
	srand((unsigned)time(NULL));
	int j = 1;
	while (j < 100) {
		int i = rand() % 1000 + 1;
		{

			if (i <= 50 || i >= 201 && i <= 210) {
				MAGICAL_CARD *card = new MAGICAL_CARD(1, "�������", damage, 2);
				cardhouse.push_back(card);
			}
			if (i >= 51 && i <= 150 || i >= 901 && i <= 915) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "������", damage, 3);
				cardhouse.push_back(card);
			}
			if (i >= 301 && i <= 525) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "������", damage, 6);
				cardhouse.push_back(card);
			}
			if (i >= 801 && i <= 890) {
				MAGICAL_CARD *card = new MAGICAL_CARD(8, "�ױ���", damage, 10);
				cardhouse.push_back(card);
			}
		}//�˺���
		{
			if (i >= 151 && i <= 180) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "Ӣ������ʫ", revert_hp, 4);
				cardhouse.push_back(card);
			}
			if (i >= 526 && i <= 650) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "����ҩˮ", revert_hp, 8);
				cardhouse.push_back(card);
			}
		}//������
		{
			if (i >= 181 && i <= 200) {
				MAGICAL_CARD *card = new MAGICAL_CARD(3, "�����޴�", draw_card, 2);
				cardhouse.push_back(card);
			}
			if (i >= 891 && i <= 900) {
				MAGICAL_CARD *card = new MAGICAL_CARD(5, "����", draw_card, 3);
				cardhouse.push_back(card);
			}
		}//�鿨��
		{
			if (i >= 211 && i <= 250) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "��ŭ", damage_buff, 3);
				cardhouse.push_back(card);
			}
			if (i >= 711 && i <= 750) {
				MAGICAL_CARD *card = new MAGICAL_CARD(6, "��", damage_buff, 5);
				cardhouse.push_back(card);
			}
		}//�˺�BUFF��
		{
			if (i >= 251 && i <= 270) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "��������", damage_debuff, -1);
				cardhouse.push_back(card);
			}
			if (i >= 651 && i <= 710) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "��������", damage_debuff, -3);
				cardhouse.push_back(card);
			}
			if (i >= 916 && i <= 930) {
				MAGICAL_CARD *card = new MAGICAL_CARD(6, "�򲻵���", damage_debuff, -5);
				cardhouse.push_back(card);
			}
		}//�˺�DEBUFF��
		{
			if (i >= 271 && i <= 300) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "ʥ��ӡ��", revert_buff, 2);
				cardhouse.push_back(card);
			}
			if (i >= 751 && i <= 775) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "ǿ������", revert_buff, 3);
				cardhouse.push_back(card);
			}
			if (i >= 931 && i <= 965) {
				MAGICAL_CARD *card = new MAGICAL_CARD(6, "����ף��", revert_buff, 5);
				cardhouse.push_back(card);
			}
		}//����BUFF��
		{
			if (i >= 776 && i <= 800) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "��Ĭ", revert_debuff, -3);
				cardhouse.push_back(card);
			}
			if (i >= 966 && i <= 990) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��ɢ", revert_debuff, -8);
				cardhouse.push_back(card);
			}
		}//����DEBUFF��
		{
			if (i == 991) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "�ǿ����", draw_card, 1);
				cardhouse.push_back(card);
			}
			if (i == 992) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��������", damage_buff, 10);
				cardhouse.push_back(card);
			}
			if (i == 993) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��ʥף��", revert_buff, 8);
				cardhouse.push_back(card);
			}
			if (i == 994) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��Ǹ", damage, 12);
				cardhouse.push_back(card);
			}
			if (i == 995) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "�����ĳ���", damage_debuff, -12);
				cardhouse.push_back(card);
			}
			if (i == 996) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "�㰲ȫ��", revert_hp, 20);
				cardhouse.push_back(card);
			}
			if (i == 997) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��������", damage_buff, 10);
				cardhouse.push_back(card);
			}
			if (i == 998) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��Ǹ", damage, 12);
				cardhouse.push_back(card);
			}
			if (i == 999) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��ʥף��", revert_buff, 8);
				cardhouse.push_back(card);
			}
			if (i == 1000) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "�ǿ����", draw_card, 1);
				cardhouse.push_back(card);
			}
		}//�ʵ���
		j++;
	}

}

//row: 37
//column: 100 -> 84

ofstream & operator<<(ofstream & out, Character & c) {
	out << c.shield << " ";
	out << c.sword << " ";
	out << c.shoes << " "
		<< c.name << " " << c.level  << " " << c.goldCoin << " "
		<< c.items.size() << " ";
	for (Item temp : c.items) {
		out << temp;
	}
	out << c.Full_HP << " " << c.power << " " << c.speed << " "
		<< c.x << " " << c.y << " " << c.Now_HP << " " << c.damage_buff_debuff << " "
		<< c.revert_buff_debuff << " ";
	out << c.afraid << " ";
	return out;
}



ifstream & operator >> (ifstream & in, Character & c) {
	in >> c.shield >> c.sword >> c.shoes
		>> c.name >> c.level >> c.goldCoin;
	int size = 0;
	in >> size;
	Item *temp;
	for (int i = 0; i < size; i++) {
		temp = new Item();
		in >> *temp;
		c.items.push_back(*temp);
	}
	in >> c.Full_HP >> c.power >> c.speed
		>> c.x >> c.y >> c.Now_HP >> c.damage_buff_debuff
		>> c.revert_buff_debuff;
	in >> c.afraid;
	return in;
}