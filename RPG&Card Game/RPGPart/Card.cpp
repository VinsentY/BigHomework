#include"CARD.h"
#include "Monster.h"
#include "Character.h"


void MAGICAL_CARD::play(Monster &npc)
{

	if (this->effect_t == damage)
	{
		cmusic.setMediaName("音乐\\扣血.mp3");
		cmusic.setMediaName("音乐\\扣血.mp3");
		cmusic.Play();
		npc.be_damaged(effect);
	}
	else if (this->effect_t == revert_hp)
	{
		cmusic.setMediaName("音乐\\治疗.mp3");
		cmusic.setMediaName("音乐\\治疗.mp3");
		cmusic.Play();
		npc.Revert_HP(effect);
	}
	else if (this->effect_t == draw_card)
	{
		cmusic.setMediaName("音乐\\出牌.mp3");
		cmusic.Play();
		npc._draw_card(effect);
	}
	else if (this->effect_t == damage_buff || this->effect_t == damage_debuff)
	{
		cmusic.setMediaName("音乐\\出牌.mp3");
		cmusic.Play();
		npc._damage(effect);
	}
	else if (this->effect_t == revert_buff || this->effect_t == revert_debuff)
	{
		cmusic.setMediaName("音乐\\出牌.mp3");
		cmusic.Play();
		npc._revert(effect);
	}
}


void MAGICAL_CARD::play(Character &player)
{
	if (this->effect_t == damage)
	{
		cmusic.setMediaName("音乐\\扣血.mp3");
		cmusic.Play();
		player.be_damaged(effect);
	}
	else if (this->effect_t == revert_hp)
	{
		cmusic.setMediaName("音乐\\治疗.mp3");
		cmusic.Play();
		player.Revert_HP(effect);
	}
	else if (this->effect_t == draw_card)
	{
		cmusic.setMediaName("音乐\\出牌.mp3");
		cmusic.Play();
		player._draw_card(effect);
	}
	else if (this->effect_t == damage_buff || this->effect_t == damage_debuff)
	{
		cmusic.setMediaName("音乐\\出牌.mp3");
		cmusic.Play();
		player._damage(effect);
	}
	else if (this->effect_t == revert_buff || this->effect_t == revert_debuff)
	{
		cmusic.setMediaName("音乐\\出牌.mp3");
		cmusic.Play();
		player._revert(effect);
	}
}
void MAGICAL_CARD::_draw()
{
	set_pos(53, 15);
	cout << "                                               ";
	set_pos(53, 18);
	
	if (this->effect_t == damage)
	{
		cout << "你使用了伤害牌:";
		cout << get_name() << "  ";
	}
	else if (this->effect_t == revert_hp)
	{
		cout << "你使用了治疗牌:";
		cout << get_name() << "  ";
	}
	else if (this->effect_t == draw_card)
	{
		cout << "你使用了抽卡牌:";
		cout << get_name() << "  ";
		cout << "抽" << effect << "张牌";
	}
	else if (this->effect_t == damage_buff)
	{
		cout << "你使用伤害牌:";
		cout << get_name();
	}
	else if (this->effect_t == damage_debuff)
	{
		cout << "你对敌人使用了减益魔法牌:";
		cout << get_name() << "  ";
	}
	else if (this->effect_t == revert_buff)
	{
		cout << "你对自己使用了增益恢复牌:";
		cout << get_name() << " ";
	}
	else if (this->effect_t == revert_debuff)
	{
		cout << "你对敌人使用了减益恢复牌:";
		cout << get_name() << "  ";
	}
}
void MAGICAL_CARD::draw()
{
	set_pos(5, 15);
	cout << "                                               ";
	set_pos(5, 15);
	if (this->effect_t == damage) {
		cout << "对方使用了伤害牌:";
		cout << get_name() << "  ";
	} else if (this->effect_t == revert_hp) {
		cout << "对方使用了治疗牌:";
		cout << get_name() << "  ";
	} else if (this->effect_t == draw_card) {
		cout << "对方使用了抽卡牌:";
		cout << get_name() << "  ";
		cout << "抽" << effect << "张牌";
	} else if (this->effect_t == damage_buff) {
		cout << "对方使用伤害牌:";
		cout << get_name();
	} else if (this->effect_t == damage_debuff) {
		cout << "对方对敌人使用了减益魔法牌:";
		cout << get_name() << "  ";
	} else if (this->effect_t == revert_buff) {
		cout << "对方对自己使用了增益恢复牌:";
		cout << get_name() << " ";
	} else if (this->effect_t == revert_debuff) {
		cout << "对方对你使用了减益恢复牌:";
		cout << get_name() << "  ";
	}
	Sleep(2000);
}
void MAGICAL_CARD::draw(int x, int y)
{
	if (this->effect_t == damage)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "法力消耗 " << get_expense();
		set_pos(x, y + 4);
		cout << "造成" << effect << "伤害";
	}
	else if (this->effect_t == revert_hp)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "法力消耗 " << get_expense();
		set_pos(x, y + 4);
		cout << "回复" << effect << "血量";
	}
	else if (this->effect_t == draw_card)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "法力消耗 " << get_expense();
		set_pos(x, y + 4);
		cout << "抽" << effect << "张牌";
	}
	else if (this->effect_t == damage_buff)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "法力消耗 " << get_expense();
		set_pos(x, y + 4);
		cout << "我方伤害+" << effect;
	}
	else if (this->effect_t == damage_debuff)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "法力消耗 " << get_expense();
		set_pos(x, y + 4);
		cout << "敌方伤害" << effect;
	}
	else if (this->effect_t == revert_buff)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "法力消耗 " << get_expense();
		set_pos(x, y + 4);
		cout << "回复加成+" << effect;
	}
	else if (this->effect_t == revert_debuff)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "法力消耗 " << get_expense();
		set_pos(x, y + 4);
		cout << "敌方回复" << effect;
	}
}

ofstream & operator<<(ofstream & out, MAGICAL_CARD & c) {

	out << c.expense << c.name << c.effect_t << c.effect;
	return out;
}

ifstream & operator >> (ifstream & in, MAGICAL_CARD & c) {
	in >> c.expense >> c.name;
	int i = 0;
	in >> i;
	c.effect_t = EFFECT_type(i);
	in >> c.effect;
	return in;
}

void CARD::set_pos(int x, int y) {
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
