#include "Monster.h"
#include "Character.h"

using namespace std;

Monster::Monster(int Now_HP, int power, vector<CARD> cardGrounp, string introduction) :Full_HP(FULL_HP), Now_HP(FULL_HP), damage_buff_debuff(0), revert_buff_debuff(0) {
	this->Now_HP = Now_HP;
	this->power = power;
	
}

void Monster::be_damaged(int num) {
	Now_HP -= ((num + damage_buff_debuff) > 0 ? (num + damage_buff_debuff) : 0);
}
void Monster::Revert_HP(int num) {
	Now_HP += ((num + revert_buff_debuff) > 0 ? (num + revert_buff_debuff) : 0);
	Now_HP = Now_HP < Full_HP ? Now_HP : Full_HP;
}
void Monster::_draw_card(int num) {
	srand((unsigned)time(NULL) + 1);
	for (int i = 0; i < num; i++) {
		int index = rand() % cardhouse.size();
		auto p1 = cardhouse.begin() + index;
		if (handhold.size() < 6) {
			handhold.push_back(*p1);
		}
		cardhouse.erase(p1);
	}
}

void Monster::initcard() {

	cardhouse.clear();
	srand((unsigned)time(NULL));
	int j = 1;
	while (j < 100) {
		int i = rand() % 1000 + 1;
		{

			if (i <= 50 || i >= 201 && i <= 210) {
				MAGICAL_CARD *card = new MAGICAL_CARD(1, "�������", damage, 2);
				cardhouse.push_back(card);
			}
			if (i >= 51 && i <= 150 || i >= 901 && i <= 915) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "������", damage, 3);
				cardhouse.push_back(card);
			}
			if (i >= 301 && i <= 525) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "������", damage, 6);
				cardhouse.push_back(card);
			}
			if (i >= 801 && i <= 890) {
				MAGICAL_CARD *card = new MAGICAL_CARD(8, "�ױ���", damage, 10);
				cardhouse.push_back(card);
			}
		}//�˺���
		{
			if (i >= 151 && i <= 180) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "Ӣ������ʫ", revert_hp, 4);
				cardhouse.push_back(card);
			}
			if (i >= 526 && i <= 650) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "����ҩˮ", revert_hp, 8);
				cardhouse.push_back(card);
			}
		}//������
		{
			if (i >= 181 && i <= 200) {
				MAGICAL_CARD *card = new MAGICAL_CARD(3, "�����޴�", draw_card, 2);
				cardhouse.push_back(card);
			}
			if (i >= 891 && i <= 900) {
				MAGICAL_CARD *card = new MAGICAL_CARD(5, "����", draw_card, 3);
				cardhouse.push_back(card);
			}
		}//�鿨��
		{
			if (i >= 211 && i <= 250) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "��ŭ", damage_buff, 3);
				cardhouse.push_back(card);
			}
			if (i >= 711 && i <= 750) {
				MAGICAL_CARD *card = new MAGICAL_CARD(6, "��", damage_buff, 5);
				cardhouse.push_back(card);
			}
		}//�˺�BUFF��
		{
			if (i >= 251 && i <= 270) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "��������", damage_debuff, -1);
				cardhouse.push_back(card);
			}
			if (i >= 651 && i <= 710) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "��������", damage_debuff, -3);
				cardhouse.push_back(card);
			}
			if (i >= 916 && i <= 930) {
				MAGICAL_CARD *card = new MAGICAL_CARD(6, "�򲻵���", damage_debuff, -5);
				cardhouse.push_back(card);
			}
		}//�˺�DEBUFF��
		{
			if (i >= 271 && i <= 300) {
				MAGICAL_CARD *card = new MAGICAL_CARD(2, "ʥ��ӡ��", revert_buff, 2);
				cardhouse.push_back(card);
			}
			if (i >= 751 && i <= 775) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "ǿ������", revert_buff, 3);
				cardhouse.push_back(card);
			}
			if (i >= 931 && i <= 965) {
				MAGICAL_CARD *card = new MAGICAL_CARD(6, "����ף��", revert_buff, 5);
				cardhouse.push_back(card);
			}
		}//����BUFF��
		{
			if (i >= 776 && i <= 800) {
				MAGICAL_CARD *card = new MAGICAL_CARD(4, "��Ĭ", revert_debuff, -3);
				cardhouse.push_back(card);
			}
			if (i >= 966 && i <= 990) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��ɢ", revert_debuff, -8);
				cardhouse.push_back(card);
			}
		}//����DEBUFF��
		{
			if (i == 991) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "�ǿ����", draw_card, 1);
				cardhouse.push_back(card);
			}
			if (i == 992) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��������", damage_buff, 10);
				cardhouse.push_back(card);
			}
			if (i == 993) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��ʥף��", revert_buff, 8);
				cardhouse.push_back(card);
			}
			if (i == 994) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��Ǹ", damage, 12);
				cardhouse.push_back(card);
			}
			if (i == 995) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "�����ĳ���", damage_debuff, -12);
				cardhouse.push_back(card);
			}
			if (i == 996) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "�㰲ȫ��", revert_hp, 20);
				cardhouse.push_back(card);
			}
			if (i == 997) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��������", damage_buff, 10);
				cardhouse.push_back(card);
			}
			if (i == 998) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��Ǹ", damage, 12);
				cardhouse.push_back(card);
			}
			if (i == 999) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "��ʥף��", revert_buff, 8);
				cardhouse.push_back(card);
			}
			if (i == 1000) {
				MAGICAL_CARD *card = new MAGICAL_CARD(10, "�ǿ����", draw_card, 1);
				cardhouse.push_back(card);
			}
		}//�ʵ���
		j++;
	}

}

ofstream & operator<<(ofstream & out, Monster & m) {
	out << m.power << m.introduction << m.name
		<< m.Full_HP << m.Now_HP << m.damage_buff_debuff
		<< m.revert_buff_debuff
		<< m.handhold.size();
	for (CARD *temp : m.handhold) {
		out << *(dynamic_cast<MAGICAL_CARD*>(temp));
	}
	out << m.cardhouse.size();
	for (CARD *temp : m.handhold) {
		out << *(dynamic_cast<MAGICAL_CARD*>(temp));
	}
	return out;
}

ifstream & operator >> (ifstream & in, Monster & m) {
	int size = 0;
	in >> m.power >> m.introduction >> m.name
		>> m.Full_HP >> m.Now_HP >> m.damage_buff_debuff
		>> m.revert_buff_debuff;
	in >> size;
	MAGICAL_CARD *temp;
	for (int i = 0; i < size; i++) {
		temp = new MAGICAL_CARD();
		in >> *temp;
		m.handhold.push_back(temp);
	}
	in >> size;
	for (int i = 0; i < size; i++) {
		temp = new MAGICAL_CARD();
		in >> *temp;
		m.handhold.push_back(temp);
	}
	return in;
}
