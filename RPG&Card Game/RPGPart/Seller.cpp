#include "Seller.h"
using namespace std;


Seller::Seller() {

	setName(SELLERS_NAME);

	

	initItem();

}

Seller::~Seller() {
}

void Seller::setName(string setName) {
	name = setName;
}

string Seller::getName() { return name; }

void Seller::initItem() {

	// 1 ��ҩˮ
	// 2�� �޽�
	// 3�� ����
	// 4�� Ь��
	// 5:  ���ر���
	// 6�� zhi
	commodities.clear();
	commodities.push_back(*(new Item("HPҩˮ", 1, 5, 4, "��ҩ���ͺͶ���ˮһ��")));
	commodities.push_back(*(new Item("�����޽�", 2, 15, 2, "һ�����������ľ޽�")));
	commodities.push_back(*(new Item("����޽�", 2, 25, 4, "�ƺ�ӵ�б��������")));
	commodities.push_back(*(new Item("����֮��", 2, 35, 8, "��Ӧ������������ǿ��������")));
	commodities.push_back(*(new Item("��������", 3, 10, 2, "���ƾ�����������ؿ������������")));
	commodities.push_back(*(new Item("�����߶���", 3, 20, 7, "��������ʿ���ǻ۽ᾧ")));
	commodities.push_back(*(new Item("���ر���", 5, 6, 0, "Duang~")));
	commodities.push_back(*(new Item("����֮ѥ", 4, 15, 5, "��о��������")));
}


void Seller::sayDialogue() {
	console.SetCoord(52, 9);
	cout << "��������" << name;
}


void Seller::sellItem(Character& buyer) {
	
	unsigned int n = 0;
	
	int choice = 0;


	//?

	sayDialogue();
	
	do {

		for (int i = 19; i <= 25; i++) {
			console.SetCoord(50, i);
			for (int j = 1; j <= 35; j++) {
				cout << " ";
			}
		}

		printMenu();
		
		console.SetCoord(51, 19);
		cout << "������Ʒ�����(0��Ž�������)>>";

		choice = buyer.buyItemFromSeller(commodities);

		console.SetCoord(51, 22);

		console.SetCoord(51, 23);
	} while (choice != 0);

	console.SetCoord(51, 24);
	cout << "���˺������ļ��������" << endl;	
	Sleep(600);

// 	Item& itemToBuy = commodities[choice - 1];
// 
// 	if (buyer.getGoldCoin() >= itemToBuy.getPrice() && buyer.set) {
// 		buyer.setGoldCoin(buyer.getGoldCoin() - itemToBuy.getPrice());//���������Ǯ
// 		buyer.addItem(itemToBuy);//��Ӹ���Ʒ��������Ʒ��
// 		commodities.erase(commodities.begin() + choice - 1);//ɾ�����˳��۲˵��еĸ���Ʒ
// 	}
//	cout << "����ɹ���" << endl;
}

void Seller::addGoods(const Item& newGoods) {
	commodities.push_back(newGoods);
}

void Seller::printMenu() {
	
	
	int n = 0;
	for (Item temp : commodities) {
		n += 1;
		console.SetCoord(51, n + 10);
		cout << n << '.';
		cout << temp;
	}

}
