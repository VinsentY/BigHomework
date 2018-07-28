#pragma once
#ifndef _CARD_H_
#define _CARD_H_
#include"MAIN.h"

using std::ofstream;
using std::istream;

//����Ч��
//�˺��ơ��ظ��ơ��鿨�ơ��˺��������ơ��ظ���������
enum EFFECT_type { damage, revert_hp, draw_card, damage_debuff, damage_buff, revert_buff, revert_debuff, nullcard };


class MAGICAL_CARD;

class CARD {
protected:

	int expense;	//���Ʒ�������
	string name;    // ��������

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

	void play(class Monster &npc);	//����Ҳ�����Ч��

	void play(class Character &player);	//��NPC���������Ч��

	void draw(int x, int y);	//�ڶ�Ӧ���껭������

	//��ʾ����ս�����̵���Ϣ���
	void draw();
	void _draw();

	EFFECT_type get_type() { return this->effect_t; }

	int get_effect() { return effect; }


};
#endif // !_CARD_H_