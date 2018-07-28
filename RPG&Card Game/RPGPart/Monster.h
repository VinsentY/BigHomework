#pragma once

#ifndef MONSTER_H
#define  MONSTER_H

#include "Card.h"
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::ofstream;
using std::ifstream;

#define FULL_HP 30

class Character;

//普通怪物
class Monster {
private:
	int power;	//力量
	
	string introduction;	//怪物介绍

	string name;	//怪物名字

	int Full_HP;	//满状态血量
	int Now_HP;		//当前血量
	int damage_buff_debuff;		//对方伤害加成（非自身加成)
	int revert_buff_debuff;		//自身回复加成
	vector < CARD* > handhold;	//当前手牌
	vector < CARD* > cardhouse;	//卡池
public:

	Monster(int damage_buff_debuff) :Full_HP(FULL_HP), Now_HP(FULL_HP), damage_buff_debuff(0), revert_buff_debuff(0) {
		this->damage_buff_debuff = damage_buff_debuff; 
	}
	Monster(int Now_HP, int power, vector<CARD> cardGrounp, string introduction);	//构造怪物

	int getPower() { return power; }

	void setPower(int power) { this->power = power; }

	void addPower(int addNum) { power += addNum; }
	
	friend ofstream& operator<< (ofstream & o, Monster &m);

	friend ifstream& operator >> (ifstream & o, Monster &m);

	friend class GAME;
	//判断是否死亡
	bool is_alive() { return Now_HP > 0 ? true : false; }
	//抓牌
	void _draw_card(int num);
	//受到伤害
	void be_damaged(int num);
	//回复生命
	void Revert_HP(int num);
	//初始化卡组
	void initcard();
	//伤害增益
	void _damage(int buff_debuff) { damage_buff_debuff += buff_debuff; }
	//回复增益
	void _revert(int buff_debuff) { revert_buff_debuff += buff_debuff; }
};

#endif




