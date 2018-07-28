#pragma once
#ifndef TREASURE_H
#define TREASURE_H

#include <vector>
#include "Item.h"

using std::vector;

class Treasure {
private:
	int coinNumber;	//��������

	vector<Item> items;	//��������Ʒ

public:
	Treasure();

	bool isTrick();	//�Ƿ�Ϊ������

	bool isCoin();	//�Ƿ�Ϊ�����

	int getCoinNumber() { return coinNumber; }

	vector<Item> getItems() { return items; }
};

#endif

