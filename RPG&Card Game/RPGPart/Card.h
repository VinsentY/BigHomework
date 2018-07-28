#pragma once
#ifndef _CARD_H_
#define _CARD_H_
#include"MAIN.h"

using std::ofstream;
using std::istream;

//卡牌效果
//伤害牌、回复牌、抽卡牌、伤害增减益牌、回复增减益牌
enum EFFECT_type { damage, revert_hp, draw_card, damage_debuff, damage_buff, revert_buff, revert_debuff, nullcard };


class MAGICAL_CARD;

class CARD {
protected:

	int expense;	//卡牌法力花费
	string name;    // 卡牌名字

public:
	CARD() {}
	CARD(int expense, string name) : expense(expense), name(name) {}
	~CARD() {}

	int get_expense() {
		return expense;
	}

	string get_name() {
		return name;
	}

	virtual void play(class Character &player) {}
	virtual void play(class Monster &npc) {}
	virtual void draw(int x, int y) {}
	virtual void draw(){}
	virtual void _draw(){}
	virtual EFFECT_type get_type() { return nullcard; }
	virtual int get_effect() { return 0; }
	void set_pos(int x, int y);

	friend ofstream& operator<< (ofstream & o, MAGICAL_CARD &c);

	friend ifstream& operator >> (ifstream & o, MAGICAL_CARD &c);
};

class MAGICAL_CARD : public CARD {
public:

	EFFECT_type effect_t;
	int effect;

public:
	MAGICAL_CARD() {}

	MAGICAL_CARD(int expense, string name, EFFECT_type effect_type, int effect) :CARD(expense, name), effect_t(effect_type), effect(effect) {}

	void play(class Monster &npc);	//对玩家产生的效果

	void play(class Character &player);	//对NPC怪物产生的效果

	void draw(int x, int y);	//在对应坐标画出卡牌

	//显示卡牌战斗过程的信息面板
	void draw();
	void _draw();

	EFFECT_type get_type() { return this->effect_t; }

	int get_effect() { return effect; }


};
#endif // !_CARD_H_