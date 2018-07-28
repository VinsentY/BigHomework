#pragma once
#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "CConsole.h"

using std::string;
using std::ostream;
using std::cout;
using std::ofstream;
using std::ifstream;

class Item {
protected:
	CConsole console;

	int number;
	string name;

	int price;

	int attribute;

	string introduction;
public:
	Item();

	Item(string name, int number, int price, int attribute, string intro);

	string getName() { return name; }

	void setItem(string name, int number = 520, int price = 1314, int attribute = 0, string intro = "NULL");

	int getPrice() { return price; }

	friend ostream& operator<< (ostream& o, Item& i);

	int getAttribute() { return attribute;}
	
	int getNumber() { return number; }

	void setAttribute(int num) { attribute = num; }

	string getIntro() { return introduction; }

	friend ofstream& operator<< (ofstream & o, Item &i);

	friend ifstream& operator >> (ifstream & o, Item &i);
};



#endif


