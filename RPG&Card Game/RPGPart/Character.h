#pragma once

#ifndef CHARACTER_H
#define CHARACTER_H

#include <vector>
#include "Card.h"
#include "Item.h"
#include <vector>
#include "CConsole.h"
#include <conio.h>
#include "Treasure.h"

#include <iostream>

class Monster;

using std::vector;
using std::string;
using std::string;


//移动方向
enum Operator {
	UP, DOWN, LEFT, RIGHT, NOMOVE, OPENITEM
};

class Character {
private:

	CConsole console;

	//人物三大装备
	Item shield;
	Item sword;
	Item shoes;

	//名字
	string name;

	//等级
	int level;

	//金币数
	int goldCoin;

	//物品栏
	static const int MAX_ITEM = 6;
	vector<Item> items;

	//人物属性
	int Full_HP;
	int power;
	int speed;

	//人物位置
	int x;
	int y;
	
	
	int Now_HP;

	int damage_buff_debuff;

	int revert_buff_debuff;

	//人物卡组
	vector < CARD* > handhold;
	vector < CARD* > cardhouse;

	//恐惧值，影响怪物伤害加成
	int afraid = 0;


public:

	Character();

	void move(Operator p);	//人物移动

	void useItem(int row, int col);	//使用物品

	bool fightToMonster();	//进入战斗

	int buyItemFromSeller(vector<Item> commodities);	//从商人处购买物品

	void openTreasure(bool canBeTrick = true);	//打开宝箱

	const int* getPosition();

	int getGoldCoin() { return goldCoin; }

	void setGoldCoin(int goldCoin) { this->goldCoin = goldCoin; }

	bool addItem(Item item);

	int getItemNumber() { return items.size(); }

	int getSpeed();

	void printInterface();	//绘制人物属性界面

	string setName();

	void levelUp();		//人物升级

	friend ofstream& operator<< (ofstream & o, Character &c);

	friend ifstream& operator>> (ifstream & o, Character &c);

	friend class GAME;
	
	bool is_alive() { return Now_HP > 0 ? true : false; }

	int play(Monster npc);

	void _draw_card(int num);

	void be_damaged(int num);

	void Revert_HP(int num);

	void initcard();

	void _damage(int buff_debuff) { damage_buff_debuff += buff_debuff; }

	void _revert(int buff_debuff) { revert_buff_debuff += buff_debuff; }

	void addAfraid() { ++afraid; }

};

#endif CHARACTER_H

