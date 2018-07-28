#include "Treasure.h"

Treasure::Treasure() {

	items.push_back(*(new Item("HP", 1, 0, 5, "���������Ѻȵ�����ҩˮ")));
	items.push_back(*(new Item("������Ͻ�", 2, 0, -5, "���ʺ϶�ͯ��ˣ")));
	items.push_back(*(new Item("����ֽ��", 6, 0, 0, "����ģ��������: �� �� �� �� �� ��")));
	items.push_back(*(new Item("����֮��", 2, 0, 8, "���������ǿ��������")));

	// 1 ��ҩˮ
	// 2�� �޽�
	// 3�� ����
	// 4�� Ь��
	// 5:  ���ر���
	// 6�� ����

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

