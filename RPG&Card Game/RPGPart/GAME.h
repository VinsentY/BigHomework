#pragma once
#include"MAIN.h"
#include"Character.h"
#include "Monster.h"
#include "CConsole.h"

#define Player 1
#define Npc 2
class GAME {
	int turn;	//�غ��л�

	Character& player;	
	Monster npc;

	CConsole console;
	//���NPC�ķ���ֵ
	int player_expense;		
	int player_now_expense;
	int npc_now_expense;
	int npc_expense;
	const int full_expense;

	char *EYE = "��";	//NPC���۾�
public:
	GAME(Character* c);
	void start();	//��ʼ��Ϸ
	bool play();
	void draw();
	void AI();	//�����AI
	void end();
	void set_pos(int x, int y);
	//���ﶯ��
	void OpenEyes(int x, int y);
	void CloseEyes(int x, int y);

};
