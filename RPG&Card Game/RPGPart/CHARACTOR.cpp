#include"CHARACTOR.h"
int Character::play(Monster npc)
{
	int cur;
	while (1)
	{
		if (GetAsyncKeyState('Q') & 0x8000)
		{
			cur = 0;
			break;
		}
		else if (GetAsyncKeyState('W') & 0x8000)
		{
			cur = 1;
			break;
		}
		else if (GetAsyncKeyState('E') & 0x8000)
		{
			cur = 2;
			break;
		}
		else if (GetAsyncKeyState('R') & 0x8000)
		{
			cur = 3;
			break;
		}
		else if (GetAsyncKeyState('T') & 0x8000)
		{
			cur = 4;
			break;
		}
		else if (GetAsyncKeyState('Y') & 0x8000)
		{
			cur = 5;
			break;
		}
		else if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
		{
			cur = -1;
			break;
		}
	}
	return cur;
}
void Character::be_damaged(int num)
{
	Now_HP -= ((num + damage_buff_debuff) > 0 ? (num + damage_buff_debuff) : 0);
}
void Character::Revert_HP(int num)
{
	Now_HP += ((num + revert_buff_debuff) > 0 ? (num + revert_buff_debuff) : 0);
	Now_HP = Now_HP < Full_HP ? Now_HP : Full_HP;
}
void Character::_draw_card(int num)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < num; i++)
	{
		int index = rand() % cardhouse.size();
		auto p1 = cardhouse.begin() + index;
		if (handhold.size() < 6)
		{
			handhold.push_back(*p1);
		}
		cardhouse.erase(p1);
	}
}
void Character::initcard()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int index = rand() % 5 + 1;
		MAGICAL_CARD *card = new MAGICAL_CARD(index - 1, "damage", damage, index);
		cardhouse.push_back(card);
	}
	for (int i = 0; i < 5; i++)
	{
		int index = rand() % 3 + 1;
		MAGICAL_CARD *card = new MAGICAL_CARD(index - 1, "revert", revert_hp, index);
		cardhouse.push_back(card);
	}
	for (int i = 0; i < 3; i++)
	{
		int index = rand() % 2 + 1;
		MAGICAL_CARD *card1 = new MAGICAL_CARD(index + 1, "draw", draw_card, index);
		index = rand() % 2 + 1;
		MAGICAL_CARD *card2 = new MAGICAL_CARD(index + 1, "damage_buff", damage_buff, index);
		MAGICAL_CARD *card3 = new MAGICAL_CARD(index + 1, "damage_debuff", damage_debuff, -index);
		MAGICAL_CARD *card4 = new MAGICAL_CARD(index + 1, "revert_buff", revert_buff, index);
		MAGICAL_CARD *card5 = new MAGICAL_CARD(index + 1, "revert_debuff", damage_debuff, -index);
		cardhouse.push_back(card1);
		cardhouse.push_back(card2);
		cardhouse.push_back(card3);
		cardhouse.push_back(card4);
		cardhouse.push_back(card5);
	}
}


int Monster::play(Character player)
{
	return 0;
}
void Monster::be_damaged(int num)
{
	Now_HP -= ((num + damage_buff_debuff) > 0 ? (num + damage_buff_debuff) : 0);
}
void Monster::Revert_HP(int num)
{
	Now_HP += ((num + revert_buff_debuff) > 0 ? (num + revert_buff_debuff) : 0);
	Now_HP = Now_HP < Full_HP ? Now_HP : Full_HP;
}
void Monster::_draw_card(int num)
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < num; i++)
	{
		int index = rand() % cardhouse.size();
		auto p1 = cardhouse.begin() + index;
		if (handhold.size() < 6)
		{
			handhold.push_back(*p1);
		}
		cardhouse.erase(p1);
	}
}
void Monster::initcard()
{
	srand((unsigned)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int index = rand() % 5 + 1;
		MAGICAL_CARD *card = new MAGICAL_CARD(index - 1, "damage", damage, index);
		cardhouse.push_back(card);
	}
	for (int i = 0; i < 5; i++)
	{
		int index = rand() % 3 + 1;
		MAGICAL_CARD *card = new MAGICAL_CARD(index - 1, "revert", revert_hp, index);
		cardhouse.push_back(card);
	}
	for (int i = 0; i < 3; i++)
	{
		int index = rand() % 2 + 1;
		MAGICAL_CARD *card1 = new MAGICAL_CARD(index + 1, "draw", draw_card, index);
		index = rand() % 2 + 1;
		MAGICAL_CARD *card2 = new MAGICAL_CARD(index + 1, "damage_buff", damage_buff, index);
		MAGICAL_CARD *card3 = new MAGICAL_CARD(index + 1, "damage_debuff", damage_debuff, index);
		MAGICAL_CARD *card4 = new MAGICAL_CARD(index + 1, "revert_buff", revert_buff, index);
		MAGICAL_CARD *card5 = new MAGICAL_CARD(index + 1, "revert_debuff", revert_debuff, index);
		cardhouse.push_back(card1);
		cardhouse.push_back(card2);
		cardhouse.push_back(card3);
		cardhouse.push_back(card4);
		cardhouse.push_back(card5);
	}
}