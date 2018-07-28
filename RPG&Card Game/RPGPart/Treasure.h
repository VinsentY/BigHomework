#pragma once
#ifndef TREASURE_H
#define TREASURE_H

#include <vector>
#include "Item.h"

using std::vector;

class Treasure {
private:
	int coinNumber;	//宝箱金币数

	vector<Item> items;	//宝箱内物品

public:
	Treasure();

	bool isTrick();	//是否为陷阱箱

	bool isCoin();	//是否为金币箱

	int getCoinNumber() { return coinNumber; }

	vector<Item> getItems() { return items; }
};

#endif

