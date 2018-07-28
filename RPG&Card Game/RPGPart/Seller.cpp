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

	// 1 ：药水
	// 2： 巨剑
	// 3： 盾牌
	// 4： 鞋子
	// 5:  神秘宝箱
	// 6： zhi
	commodities.clear();
	commodities.push_back(*(new Item("HP药水", 1, 5, 4, "这药剂就和兑了水一样")));
	commodities.push_back(*(new Item("精良巨剑", 2, 15, 2, "一把银光闪闪的巨剑")));
	commodities.push_back(*(new Item("暴风巨剑", 2, 25, 4, "似乎拥有暴风的力量")));
	commodities.push_back(*(new Item("神秘之剑", 2, 35, 8, "这应该是世界上最强的武器了")));
	commodities.push_back(*(new Item("精良盾牌", 3, 10, 2, "盾牌精良得能清楚地看见上面的条纹")));
	commodities.push_back(*(new Item("日内瓦盾牌", 3, 20, 7, "日内瓦勇士的智慧结晶")));
	commodities.push_back(*(new Item("神秘宝箱", 5, 6, 0, "Duang~")));
	commodities.push_back(*(new Item("轻灵之靴", 4, 15, 5, "你感觉健步如飞")));
}


void Seller::sayDialogue() {
	console.SetCoord(52, 9);
	cout << "你遇见了" << name;
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
		cout << "输入物品的序号(0序号结束购买)>>";

		choice = buyer.buyItemFromSeller(commodities);

		console.SetCoord(51, 22);

		console.SetCoord(51, 23);
	} while (choice != 0);

	console.SetCoord(51, 24);
	cout << "商人和你闲聊几句后走了" << endl;	
	Sleep(600);

// 	Item& itemToBuy = commodities[choice - 1];
// 
// 	if (buyer.getGoldCoin() >= itemToBuy.getPrice() && buyer.set) {
// 		buyer.setGoldCoin(buyer.getGoldCoin() - itemToBuy.getPrice());//减少人物金钱
// 		buyer.addItem(itemToBuy);//添加该物品到人物物品栏
// 		commodities.erase(commodities.begin() + choice - 1);//删除商人出售菜单中的该物品
// 	}
//	cout << "购买成功！" << endl;
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
