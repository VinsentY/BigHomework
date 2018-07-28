#pragma once

#ifndef SELLER_H
#define  SELLER_H

#include <vector>
#include <string>
#include "Character.h"
#include <conio.h>
#include <conio.h>
using std::vector;

#define WORDS_TO_SAY "我这里有很多好东西呢！"
#define SELLERS_NAME "旅行商人" 

class Seller {
private:

	vector<Item> commodities;	//商人售卖物品

	string name;	//商人名字

	CConsole console;
public:

	Seller();
	~Seller();
	void setName(string setName);
	string getName();

	void initItem();	//初始化商品

	void sayDialogue();		//商人台词

	void sellItem(Character& buyer);	//出售物品

	void addGoods(const Item& newGoods);//增加出售的商品

	void printMenu(); //打印选择菜单

};

#endif

