#pragma once

#ifndef SELLER_H
#define  SELLER_H

#include <vector>
#include <string>
#include "Character.h"
#include <conio.h>
#include <conio.h>
using std::vector;

#define WORDS_TO_SAY "�������кܶ�ö����أ�"
#define SELLERS_NAME "��������" 

class Seller {
private:

	vector<Item> commodities;	//����������Ʒ

	string name;	//��������

	CConsole console;
public:

	Seller();
	~Seller();
	void setName(string setName);
	string getName();

	void initItem();	//��ʼ����Ʒ

	void sayDialogue();		//����̨��

	void sellItem(Character& buyer);	//������Ʒ

	void addGoods(const Item& newGoods);//���ӳ��۵���Ʒ

	void printMenu(); //��ӡѡ��˵�

};

#endif

