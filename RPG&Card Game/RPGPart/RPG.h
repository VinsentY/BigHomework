#pragma once

#ifndef RPG_H
#define RPG_H

#include "Character.h"
#include "Monster.h"
#include "Seller.h"
#include "Treasure.h"
#include <conio.h>
#include <cstdio>
#include "CConsole.h"
#include <iostream>
#include <Windows.h>
#include "MAIN.h"
#include "GAME.h"

#define  symbol symbolWall

#define CHARACTER 6

#define EMPTY 0
#define WALL 1

#define MONSETER 2
#define SELLER 3
#define TREASURE 4
#define ENTRANCE 7

//RPG的元素
class RPG {
public:

	Character character;	//人物元素
	
	Seller seller;	//商人元素

	Treasure treasures;		//宝箱元素

	static const int row = 25;
	static const int column = 25;

	int map[row][column];	//地图

	int pixel[4][4] = { 0 };
		
	int rounds = 1;		//回合数

	bool game_over = false;	//游戏是否结束

	//人物位置

	int character_x;
	int character_y;

	int killNum = 0;	//击杀怪物数

	CConsole console;


	//元素符号
	char* symbolCharacter = "●";
	char* symbolCharacterMove = "○";
	char* symbolWall = "■";
	char* symbolSeller = "﹩";
	char* symbolChoice = "△";
	char* symbolMonster = "Ω";
	char* symbolTreasure = "☆";
	char* symbolTEntrance = "╳ ";
	char* symbolFog = "≈";

public:
	RPG();		//正确初始化游戏

	void gameStart();		//开始游戏！
	
	void beforeRound();	//回合前需要做的事

	void startRound();	//回合时的操作

	void afterRound();	//回合后的相应处理

	void startAnimation();	//开场动画

	bool login();	//登陆界面
	
	void drama(int sleepTime);	//游戏剧情

	void cutscenes();	//过渡动画

	void drawVICU(int x, int y, char * symbol,int sleepTime);	//VICU动画

	void choiceItem();	//使用物品

	Operator selectToMove();	//选择移动位置

	void analyseState();	//分析人物位置状态

	void refreshData();		//更新数据

	void refreshMap();	//刷新地图

	void drawMove(int x, int y, Operator p);	//画出移动轨迹

	//指定位置延时可跳过字符串输出函数
	inline void printWords_p(int x, int y, const char* words, int& sleepTime) {
		console.SetCoord(x, y);
		for (int i = 0; words[i] != '\0'; i++) {
			cout << words[i];
			Sleep(sleepTime);
			if (sleepTime !=0 && kbhit()) {
				getch();
				sleepTime = 0;
			}
		}
	}


	inline void printWords(int x, int y, const char* words,int sleepTime = 75) {
		console.SetCoord(x, y);
		for (int i = 0; words[i] != '\0'; i++) {
			cout << words[i];
			Sleep(sleepTime);
		}
	}

	void gameOver(int sleepTime);	//游戏结束动画

	void goodEnd(int sleepTime);	//结局

	void readFromFile();	//读取文件
		
	void writeToFile();		//写入文件

	void aboutUs();		//关于我们

};

#endif


