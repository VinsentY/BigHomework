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


//�ƶ�����
enum Operator {
	UP, DOWN, LEFT, RIGHT, NOMOVE, OPENITEM
};

class Character {
private:

	CConsole console;

	//��������װ��
	Item shield;
	Item sword;
	Item shoes;

	//����
	string name;

	//�ȼ�
	int level;

	//�����
	int goldCoin;

	//��Ʒ��
	static const int MAX_ITEM = 6;
	vector<Item> items;

	//��������
	int Full_HP;
	int power;
	int speed;

	//����λ��
	int x;
	int y;
	
	
	int Now_HP;

	int damage_buff_debuff;

	int revert_buff_debuff;

	//���￨��
	vector < CARD* > handhold;
	vector < CARD* > cardhouse;

	//�־�ֵ��Ӱ������˺��ӳ�
	int afraid = 0;


public:

	Character();

	void move(Operator p);	//�����ƶ�

	void useItem(int row, int col);	//ʹ����Ʒ

	bool fightToMonster();	//����ս��

	int buyItemFromSeller(vector<Item> commodities);	//�����˴�������Ʒ

	void openTreasure(bool canBeTrick = true);	//�򿪱���

	const int* getPosition();

	int getGoldCoin() { return goldCoin; }

	void setGoldCoin(int goldCoin) { this->goldCoin = goldCoin; }

	bool addItem(Item item);

	int getItemNumber() { return items.size(); }

	int getSpeed();

	void printInterface();	//�����������Խ���

	string setName();

	void levelUp();		//��������

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

