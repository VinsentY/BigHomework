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
			cout << "请输入正确的选项(0序号结束购买)   ";
		}	
	} while (!inputRight);
	

	int price = commodities[choice - 1].getPrice();


	console.SetCoord(51, 20);
	if (goldCoin >= price && addItem(commodities[choice - 1])) {
		goldCoin -= price;
		cout << "购买成功";
	} else {
		cout << "购买失败";
	}
	console.SetCoord(51, 21);
	cout << "金币余额 :" << goldCoin << endl;

	console.SetCoord(35, 35);
	cout << "金币余额: " << goldCoin << "  ";
	getch();
	return choice;
}

void Character::openTreasure(bool canBeTrick) {
	console.SetCoord(51, 18);
	cout << name << "打开宝箱";
	
	Treasure* temp = new Treasure();

	if (canBeTrick = false && temp->isTrick()) {
		console.SetCoord(51, 20);
		cmusic.setMediaName("音乐\\扣血.mp3");
		cmusic.Play();
		cout << "宝箱里的毒蛇爬出来咬了你一口";
		console.SetCoord(51, 22);
		cout << name << "损失了5点生命力";
		Now_HP -= 5;
	} else if(temp->isCoin()) {
		console.SetCoord(51, 20);
		cmusic.setMediaName("音乐\\金币.mp3");
		cmusic.Play();
		cout << "宝箱里发着金光！";
		console.SetCoord(51, 22);
		cout << "你获得了" << temp->getCoinNumber() << "金币!";
		goldCoin += temp->getCoinNumber();
	} else {
		srand(time(NULL));
		int num = rand() % (temp->getItems().size());
		console.SetCoord(51, 20);
		cmusic.setMediaName("音乐\\叮.wav");
		cmusic.Play();
		if (addItem(temp->getItems().at(num))) {
			cout << "你获得了" << temp->getItems().at(num).getName();
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

	sword.setItem("破旧的巨剑");
	shield.setItem("破旧的盾牌");
	shoes.setItem("破旧的鞋子");
	
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
		cout << "你使用空气给我看看？光合作用？";
	} else {
		
		// 1 ：药水
		// 2： 巨剑
		// 3： 盾牌
		// 4： 鞋子
		// 5:  随机宝箱
		// 6:  垃圾

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
			cout << "你使用了药水，恢复了" << revert_hp << "点血量";
			console.SetCoord(52, 22);
			cout << "当前血量: " << Now_HP;
			break;
		case 2:
			cmusic.setMediaName("音乐\\装备.mp3");
			cmusic.Play();
			console.SetCoord(52, 16);
			cout << items[index].getName() ;
			console.SetCoord(52, 18);
			cout << items[index].getIntro();
			console.SetCoord(52, 20);
			cout << "成功装备!";
			console.SetCoord(52, 22);

			power -= sword.getAttribute();
			sword = items[index];
			power += sword.getAttribute();

			cout << "当前攻击力: " << power;
			break;
		case 3:
			cmusic.setMediaName("音乐\\装备.mp3");
			cmusic.Play();
			console.SetCoord(52, 16);
			cout << items[index].getName();
			console.SetCoord(52, 18);
			cout << items[index].getIntro();
			console.SetCoord(52, 20);
			cout << "成功装备!";
			console.SetCoord(52, 22);

			Full_HP -= shield.getAttribute();		

			shield = items[index];

			Full_HP += shield.getAttribute();


			cout << "最大生命力增加至: " << Full_HP;
			break;
		case 4:
			cmusic.setMediaName("音乐\\装备.mp3");
			cmusic.Play();
			console.SetCoord(52, 16);
			cout << items[index].getName();
			console.SetCoord(52, 18);
			cout << items[index].getIntro();
			console.SetCoord(52, 20);
			cout << "成功装备!";
			console.SetCoord(52, 22);

			speed -= shoes.getAttribute();
			shoes = items[index];
			speed += shoes.getAttribute();

			cout << "当前移速增加至: " << speed;
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
			cout << "这里面一定有些有用的线索" ;
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
		cout << "背包太满了，你装不下任何东西了现在";
		return false;
	}
}

int Character::getSpeed() {
	return speed;
}

void Character::printInterface() {
	console.SetCoord(50, 0);
	cout << "--------------属性栏--------------";
	console.SetCoord(51, 1);
	cout << "勇士：" << left << setw(16) << name << "  等级： " << level;
	console.SetCoord(51, 3);
	cout << "力量: " << power << " 生命力: " << Now_HP << "/" << Full_HP << " 移速: " << speed;
	console.SetCoord(50, 4);
	cout << "--------------装备栏--------------";
	console.SetCoord(51, 5);
	cout << "        武器： " << sword.getName();
	console.SetCoord(51, 6);
	cout << "        盾牌： " << shield.getName();
	console.SetCoord(51, 7);
	cout << "        鞋子： " << shoes.getName();
	console.SetCoord(50, 8);
	cout << "--------------对话栏--------------";
	console.SetCoord(50, 24);
	cout  << "----------------------------------";
	console.SetCoord(0, 26);
	cout << "------------------------------------物品栏------------------------------------------";

	int i = 0;
	int j = 0;
	// i为行， j为列

	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++) {
			console.SetCoord(10 + j * 30, 30 + i * 2);
			if (j + i * 3 >= items.size()) {
				cout << "空";
			} else {
				cout << items[j + i * 3].getName();
			}

		}
	}


	console.SetCoord(35, 35);

	cout << "金币余额: " << goldCoin;

	console.SetCoord(50 ,25);
	cout << "↑↓←→ 移动";
	
	cout << "  E 物品栏";

	cout << "  ESC 退出";
}

string Character::setName() {
	string name = "VICU";

	console.SetCoord(34, 16);
	//就是不能正确读取汉字
	cin >> name;
	this->name = name;

	return name;
}

void Character::levelUp() {
	level++;
	power++;
	Now_HP = Full_HP;

	console.SetCoord(51, 10);
	cout << "恭喜你升级了！";

	console.SetCoord(51, 12);

	cout << "力量增加！";
	console.SetCoord(51, 14);

	cout << "当前等级：" << level;

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

//填充卡组
void Character::initcard() {

	cardhouse.clear();
	srand((unsigned)time(NULL));
	int j = 1;
	while (j < 100) {
		int i = rand() % 1000 + 1;
		{

			if (i <= 50 || i >= 201 && i <= 210) {
				MAGICAL_CARD *card = new MAGICAL_CARD(1, "奥术射击", damage, 2);
				cardhouse.push_back(card);
			}
			if (i >= 51 && i <= 150 || i >= 901 && i <= 915) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "寒冰箭", damage, 3);
				cardhouse.push_back(card);
			}
			if (i >= 301 && i <= 525) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "火球术", damage, 6);
				cardhouse.push_back(card);
			}
			if (i >= 801 && i <= 890) {
				MAGICAL_CARD *card = new MAGICAL_CARD(8, "炎爆术", damage, 10);
				cardhouse.push_back(card);
			}
		}//伤害牌
		{
			if (i >= 151 && i <= 180) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "英勇赞美诗", revert_hp, 4);
				cardhouse.push_back(card);
			}
			if (i >= 526 && i <= 650) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "治疗药水", revert_hp, 8);
				cardhouse.push_back(card);
			}
		}//治疗牌
		{
			if (i >= 181 && i <= 200) {
				MAGICAL_CARD *card = new MAGICAL_CARD(3, "奥术愚蠢", draw_card, 2);
				cardhouse.push_back(card);
			}
			if (i >= 891 && i <= 900) {
				MAGICAL_CARD *card = new MAGICAL_CARD(5, "疾跑", draw_card, 3);
				cardhouse.push_back(card);
			}
		}//抽卡牌
		{
			if (i >= 211 && i <= 250) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "激怒", damage_buff, 3);
				cardhouse.push_back(card);
			}
			if (i >= 711 && i <= 750) {
				MAGICAL_CARD *card = new MAGICAL_CARD(6, "狂暴", damage_buff, 5);
				cardhouse.push_back(card);
			}
		}//伤害BUFF牌
		{
			if (i >= 251 && i <= 270) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "虚弱诅咒", damage_debuff, -1);
				cardhouse.push_back(card);
			}
			if (i >= 651 && i <= 710) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "死亡嚎叫", damage_debuff, -3);
				cardhouse.push_back(card);
			}
			if (i >= 916 && i <= 930) {
				MAGICAL_CARD *card = new MAGICAL_CARD(6, "打不到我", damage_debuff, -5);
				cardhouse.push_back(card);
			}
		}//伤害DEBUFF牌
		{
			if (i >= 271 && i <= 300) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "圣光印记", revert_buff, 2);
				cardhouse.push_back(card);
			}
			if (i >= 751 && i <= 775) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "强化治疗", revert_buff, 3);
				cardhouse.push_back(card);
			}
			if (i >= 931 && i <= 965) {
				MAGICAL_CARD *card = new MAGICAL_CARD(6, "治疗祝福", revert_buff, 5);
				cardhouse.push_back(card);
			}
		}//治疗BUFF牌
		{
			if (i >= 776 && i <= 800) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "沉默", revert_debuff, -3);
				cardhouse.push_back(card);
			}
			if (i >= 966 && i <= 990) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "驱散", revert_debuff, -8);
				cardhouse.push_back(card);
			}
		}//治疗DEBUFF牌
		{
			if (i == 991) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "那可真蠢", draw_card, 1);
				cardhouse.push_back(card);
			}
			if (i == 992) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "气定神闲", damage_buff, 10);
				cardhouse.push_back(card);
			}
			if (i == 993) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "神圣祝福", revert_buff, 8);
				cardhouse.push_back(card);
			}
			if (i == 994) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "抱歉", damage, 12);
				cardhouse.push_back(card);
			}
			if (i == 995) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "该死的虫子", damage_debuff, -12);
				cardhouse.push_back(card);
			}
			if (i == 996) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "你安全了", revert_hp, 20);
				cardhouse.push_back(card);
			}
			if (i == 997) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "气定神闲", damage_buff, 10);
				cardhouse.push_back(card);
			}
			if (i == 998) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "抱歉", damage, 12);
				cardhouse.push_back(card);
			}
			if (i == 999) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "神圣祝福", revert_buff, 8);
				cardhouse.push_back(card);
			}
			if (i == 1000) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "那可真蠢", draw_card, 1);
				cardhouse.push_back(card);
			}
		}//彩蛋牌
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