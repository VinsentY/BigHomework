#pragma once
#include"MAIN.h"
#include"Character.h"
#include "Monster.h"
#include "CConsole.h"

#define Player 1
#define Npc 2
class GAME {
	int turn;	//回合切换

	Character& player;	
	Monster npc;

	CConsole console;
	//人物、NPC的法力值
	int player_expense;		
	int player_now_expense;
	int npc_now_expense;
	int npc_expense;
	const int full_expense;

	char *EYE = "●";	//NPC的眼睛
public:
	GAME(Character* c);
	void start();	//开始游戏
	bool play();
	void draw();
	void AI();	//怪物的AI
	void end();
	void set_pos(int x, int y);
	//怪物动画
	void OpenEyes(int x, int y);
	void CloseEyes(int x, int y);

};
