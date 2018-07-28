#include"CARD.h"
#include "Monster.h"
#include "Character.h"


void MAGICAL_CARD::play(Monster &npc)
{

	if (this->effect_t == damage)
	{
		cmusic.setMediaName("����\\��Ѫ.mp3");
		cmusic.setMediaName("����\\��Ѫ.mp3");
		cmusic.Play();
		npc.be_damaged(effect);
	}
	else if (this->effect_t == revert_hp)
	{
		cmusic.setMediaName("����\\����.mp3");
		cmusic.setMediaName("����\\����.mp3");
		cmusic.Play();
		npc.Revert_HP(effect);
	}
	else if (this->effect_t == draw_card)
	{
		cmusic.setMediaName("����\\����.mp3");
		cmusic.Play();
		npc._draw_card(effect);
	}
	else if (this->effect_t == damage_buff || this->effect_t == damage_debuff)
	{
		cmusic.setMediaName("����\\����.mp3");
		cmusic.Play();
		npc._damage(effect);
	}
	else if (this->effect_t == revert_buff || this->effect_t == revert_debuff)
	{
		cmusic.setMediaName("����\\����.mp3");
		cmusic.Play();
		npc._revert(effect);
	}
}


void MAGICAL_CARD::play(Character &player)
{
	if (this->effect_t == damage)
	{
		cmusic.setMediaName("����\\��Ѫ.mp3");
		cmusic.Play();
		player.be_damaged(effect);
	}
	else if (this->effect_t == revert_hp)
	{
		cmusic.setMediaName("����\\����.mp3");
		cmusic.Play();
		player.Revert_HP(effect);
	}
	else if (this->effect_t == draw_card)
	{
		cmusic.setMediaName("����\\����.mp3");
		cmusic.Play();
		player._draw_card(effect);
	}
	else if (this->effect_t == damage_buff || this->effect_t == damage_debuff)
	{
		cmusic.setMediaName("����\\����.mp3");
		cmusic.Play();
		player._damage(effect);
	}
	else if (this->effect_t == revert_buff || this->effect_t == revert_debuff)
	{
		cmusic.setMediaName("����\\����.mp3");
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
		cout << "��ʹ�����˺���:";
		cout << get_name() << "  ";
	}
	else if (this->effect_t == revert_hp)
	{
		cout << "��ʹ����������:";
		cout << get_name() << "  ";
	}
	else if (this->effect_t == draw_card)
	{
		cout << "��ʹ���˳鿨��:";
		cout << get_name() << "  ";
		cout << "��" << effect << "����";
	}
	else if (this->effect_t == damage_buff)
	{
		cout << "��ʹ���˺���:";
		cout << get_name();
	}
	else if (this->effect_t == damage_debuff)
	{
		cout << "��Ե���ʹ���˼���ħ����:";
		cout << get_name() << "  ";
	}
	else if (this->effect_t == revert_buff)
	{
		cout << "����Լ�ʹ��������ָ���:";
		cout << get_name() << " ";
	}
	else if (this->effect_t == revert_debuff)
	{
		cout << "��Ե���ʹ���˼���ָ���:";
		cout << get_name() << "  ";
	}
}
void MAGICAL_CARD::draw()
{
	set_pos(5, 15);
	cout << "                                               ";
	set_pos(5, 15);
	if (this->effect_t == damage) {
		cout << "�Է�ʹ�����˺���:";
		cout << get_name() << "  ";
	} else if (this->effect_t == revert_hp) {
		cout << "�Է�ʹ����������:";
		cout << get_name() << "  ";
	} else if (this->effect_t == draw_card) {
		cout << "�Է�ʹ���˳鿨��:";
		cout << get_name() << "  ";
		cout << "��" << effect << "����";
	} else if (this->effect_t == damage_buff) {
		cout << "�Է�ʹ���˺���:";
		cout << get_name();
	} else if (this->effect_t == damage_debuff) {
		cout << "�Է��Ե���ʹ���˼���ħ����:";
		cout << get_name() << "  ";
	} else if (this->effect_t == revert_buff) {
		cout << "�Է����Լ�ʹ��������ָ���:";
		cout << get_name() << " ";
	} else if (this->effect_t == revert_debuff) {
		cout << "�Է�����ʹ���˼���ָ���:";
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
		cout << "�������� " << get_expense();
		set_pos(x, y + 4);
		cout << "���" << effect << "�˺�";
	}
	else if (this->effect_t == revert_hp)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "�������� " << get_expense();
		set_pos(x, y + 4);
		cout << "�ظ�" << effect << "Ѫ��";
	}
	else if (this->effect_t == draw_card)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "�������� " << get_expense();
		set_pos(x, y + 4);
		cout << "��" << effect << "����";
	}
	else if (this->effect_t == damage_buff)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "�������� " << get_expense();
		set_pos(x, y + 4);
		cout << "�ҷ��˺�+" << effect;
	}
	else if (this->effect_t == damage_debuff)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "�������� " << get_expense();
		set_pos(x, y + 4);
		cout << "�з��˺�" << effect;
	}
	else if (this->effect_t == revert_buff)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "�������� " << get_expense();
		set_pos(x, y + 4);
		cout << "�ظ��ӳ�+" << effect;
	}
	else if (this->effect_t == revert_debuff)
	{
		set_pos(x, y);
		cout << get_name();
		set_pos(x, y + 2);
		cout << "�������� " << get_expense();
		set_pos(x, y + 4);
		cout << "�з��ظ�" << effect;
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
