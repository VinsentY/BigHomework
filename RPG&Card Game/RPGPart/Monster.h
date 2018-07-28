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

//��ͨ����
class Monster {
private:
	int power;	//����
	
	string introduction;	//�������

	string name;	//��������

	int Full_HP;	//��״̬Ѫ��
	int Now_HP;		//��ǰѪ��
	int damage_buff_debuff;		//�Է��˺��ӳɣ�������ӳ�)
	int revert_buff_debuff;		//����ظ��ӳ�
	vector < CARD* > handhold;	//��ǰ����
	vector < CARD* > cardhouse;	//����
public:

	Monster(int damage_buff_debuff) :Full_HP(FULL_HP), Now_HP(FULL_HP), damage_buff_debuff(0), revert_buff_debuff(0) {
		this->damage_buff_debuff = damage_buff_debuff; 
	}
	Monster(int Now_HP, int power, vector<CARD> cardGrounp, string introduction);	//�������

	int getPower() { return power; }

	void setPower(int power) { this->power = power; }

	void addPower(int addNum) { power += addNum; }
	
	friend ofstream& operator<< (ofstream & o, Monster &m);

	friend ifstream& operator >> (ifstream & o, Monster &m);

	friend class GAME;
	//�ж��Ƿ�����
	bool is_alive() { return Now_HP > 0 ? true : false; }
	//ץ��
	void _draw_card(int num);
	//�ܵ��˺�
	void be_damaged(int num);
	//�ظ�����
	void Revert_HP(int num);
	//��ʼ������
	void initcard();
	//�˺�����
	void _damage(int buff_debuff) { damage_buff_debuff += buff_debuff; }
	//�ظ�����
	void _revert(int buff_debuff) { revert_buff_debuff += buff_debuff; }
};

#endif




