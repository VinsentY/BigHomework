#include "Treasure.h"

Treasure::Treasure() {

	items.push_back(*(new Item("HP", 1, 0, 5, "看起来很难喝的生命药水")));
	items.push_back(*(new Item("玩具塑料剑", 2, 0, -5, "很适合儿童玩耍")));
	items.push_back(*(new Item("神秘纸条", 6, 0, 0, "几个模糊的数字: Ⅵ Ⅲ Ⅷ Ⅴ Ⅳ Ⅶ")));
	items.push_back(*(new Item("诸神之剑", 2, 0, 8, "这绝对是最强的武器了")));

	// 1 ：药水
	// 2： 巨剑
	// 3： 盾牌
	// 4： 鞋子
	// 5:  神秘宝箱
	// 6： 垃圾

	coinNumber = rand() % 5 + 1;
}

bool Treasure::isTrick() {
	srand(time(NULL));

	switch (rand() % 6 + 1) {
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
		return false;
	case 6:
		return true;
	}
}

bool Treasure::isCoin() {

	srand(time(NULL));

	int temp = rand() % 10 + 1;

	if (temp == 10) {
		return false;
	}
	return true;
}

