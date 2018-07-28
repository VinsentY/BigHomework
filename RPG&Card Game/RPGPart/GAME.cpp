#include"GAME.h"
GAME::GAME(Character * c) : player(*c), npc(player.power), 
	turn(Player), player_expense(3), npc_expense(3), 
	full_expense(10), npc_now_expense(3), player_now_expense(3) {

	c->damage_buff_debuff = c->afraid;

	c->revert_buff_debuff = 0;

	player.handhold.clear(); 
	player.cardhouse.clear();

}
void GAME::start()
{
	player.initcard();
	npc.initcard();
	player._draw_card(4);
	npc._draw_card(4);
}
bool GAME::play()
{
	while (player.is_alive() && npc.is_alive())
	{
		if (turn == Player)
		{
		
			if (player_expense < full_expense)
			{
				player_expense++;
			}
			player_now_expense = player_expense;
			player._draw_card(1);
			draw();
		begin:int cur = player.play(npc);
			if (cur != -1)
				if (player.handhold.size() > cur)
				{
					auto p = player.handhold.begin() + cur;
					if (player_now_expense >= (*p)->get_expense())
					{
						if ((*p)->get_type() == damage || (*p)->get_type() == damage_buff || (*p)->get_type() == revert_debuff)
						{
							(*p)->play(npc);
							if (!npc.is_alive())
							{
								goto end;
							}
						}
						else
						{
							(*p)->play(player);
							
						}
						(*p)->_draw();
						Sleep(1000);
						player_now_expense -= (*p)->get_expense();
						player.handhold.erase(p);
						system("cls");
						draw();
							
						goto begin;
					}
					else
					{
						set_pos(30, 15);
						cout << "你没有足够的法力值！";
						Sleep(200);
						goto begin;
					}
				}
			turn = Npc;
		}
		else
		{
			
			if (npc_expense < full_expense)
			{
				npc_expense++;
				
			}
			npc_now_expense = npc_expense;
			npc._draw_card(1);
			AI();
			system("cls");
			draw();
			Sleep(1000);
			turn = Player;
		}
	}
	end:
	if (player.is_alive()) {
		return true;
	} else {
		return false;
	}
}
void GAME::set_pos(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}
void GAME::OpenEyes(int x, int y) {
	
	int xx[5] = { x,x,x,x,x };
	console.HideCursor(true);
	set_pos(x, y);
	int a[5][27] = { 0 };

	int temp = y;

	a[0][5] = a[0][6] = a[0][7] = a[0][8] = a[0][18] = a[0][19] = a[0][20] = a[0][21] = 1;
	a[1][0] = a[1][3] = a[1][4] = a[1][9] = a[1][17] = a[1][22] = a[1][23] = a[1][26] = 1;
	a[2][1] = a[2][2] = a[2][10] = a[2][16] = a[2][24] = a[2][25] = 1;
	a[3][3] = a[3][4] = a[3][10] = a[3][11] = a[3][15] = a[3][16] = a[3][22] = a[3][23] = 1;
	a[4][5] = a[4][6] = a[4][7] = a[4][8] = a[4][9] = a[4][12] = a[4][14] = a[4][17] = a[4][18] = a[4][19] = a[4][20] = a[4][21] = 1;
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 27; j++) {
			if (a[i][j] == 1) {
				cout << EYE;
			} else {
				cout << "  ";
			}
		}
		y += 1;
		set_pos(x, y);
	
	}

}

void GAME::CloseEyes(int x, int y) {
	int xx[3] = { x,x,x };
	console.HideCursor(true);
	set_pos(x, y);
	int a[3][22] = { 0 };
	a[0][0] = a[0][21] = 1;
	a[1][1] = a[1][2] = a[1][3] = a[1][4] = a[1][5] = a[1][6] = a[1][7] = a[1][8] = a[1][13] = a[1][14] = a[1][15] = a[1][16] = a[1][17] = a[1][18] = a[1][19] = a[1][20] = 1;
	a[2][9] = a[2][12] = 1;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 22; j++) {
			if (a[i][j] == 1) {
				cout << EYE;
			} else {
				cout << "  ";
			}
		}
		y += 1;
		set_pos(x, y);
	}
}

void GAME::draw()
{
	system("cls");
	if (npc.Now_HP < 10 || player.Now_HP < 10) {
		console.SetColor("0c");
	} else {
		console.SetColor("07");
	}

	if (turn == Player) {
		CloseEyes(18, 5);
	} else {
		OpenEyes(12, 4);
	}

	set_pos(0, 12);
	cout << "______________________________________________________________________________________";
	set_pos(0, 13);
	cout << "★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★★";
	set_pos(0, 20);
	cout << "★★  Q  ★★★★  W  ★★★★★  E  ★★★★★  R  ★★★★  T  ★★★★★  Y★★★★";
	set_pos(0, 21);
	cout << "______________________________________________________________________________________";
	set_pos(0, 28);
	cout << "______________________________________________________________________________________";	

	set_pos(2, 31);
	cout << "生命值:  ";
	
	for (int i = 1; i <= player.Full_HP; i++) {
		if (i <= player.Now_HP) {
			cout << "■";
		} else {
			cout << "□";
		}
	}
	
	set_pos(14, 35);
	cout << "手牌数:" << player.handhold.size()
		<< '/' << 6 << "  " << "法力值:" << player_now_expense << '/' << player_expense << "  "
		<< "伤害加成:" << npc.damage_buff_debuff << "  " << "回复加成:" << player.revert_buff_debuff << "  " << "牌库:" << player.cardhouse.size();
	set_pos(1, 1);
	//cout << "BOSS血量:" << npc.Now_HP << '/' << npc.Full_HP;
	cout << "BOSS血量:  ";
	for (int i = 1; i <= npc.Full_HP; i++) {
		if (i <= npc.Now_HP) {
			cout << "■";
		} else {
			cout << "□";
		}
	}
	set_pos(14, 11);
	cout << "手牌数:" << npc.handhold.size()
		<< '/' << 6 << "  " << "法力值:" << npc_now_expense << '/' << npc_expense << "  "
		<< "伤害加成:" << player.damage_buff_debuff << "  " << "回复加成:" << npc.revert_buff_debuff << "  " << "牌库:" << npc.cardhouse.size();
	
	if (turn == Npc)
	{
		set_pos(36, 16);
		cout << "对方回合";
		set_pos(36, 17);
		cout << "        ";
	}
	else
	{
		set_pos(36, 16);
		cout << "        ";
		set_pos(32, 17);
		cout << "你的回合(ESC结束)";

	}
	set_pos(60, 0);
	auto p1 = player.handhold.begin();
	for (int j = 21; j < 28; j++) {
		set_pos(0, j);
		cout << '|';
	}
	for (int i = 0; p1 != player.handhold.end(); p1++, i += 14)
	{
		(*p1)->draw(i + 2, 23);
		for (int j = 22; j < 29; j++)
		{
			set_pos(i + 13, j);
			cout << '|';
		}
	}
}
void GAME::AI() {

	vector <CARD*> index;
begin:
	draw();
	for (int i = 0; i < npc.handhold.size(); i++) {

		auto p = npc.handhold.begin() + i;
		if ((*p)->get_expense() <= npc_now_expense) {
			index.push_back(*p);
		}
	}

	if (index.size() == 0) {
		return;
	}
	else if (index.size() == 1)
	{
		auto p = index.begin();
		if ((*p)->get_type() == revert_hp)
		{
			if ((npc.Now_HP + (*p)->get_effect() + npc.revert_buff_debuff) > FULL_HP)
			{
				Sleep(1000);
			}
			else 				
			{
				(*p)->play(npc);
				(*p)->draw();
				npc_now_expense -= (*p)->get_expense();
				for (auto q = npc.handhold.begin(); q != npc.handhold.end(); q++) {
					if ((*q) == (*p)) {
						npc.handhold.erase(q);
						break;
					}
				}
			}
		}
		else if ((*p)->get_type() == draw_card)
		{
			if ((5 - npc.handhold.size()) >= (*p)->get_effect())
			{
				(*p)->play(npc);
				(*p)->draw();
				npc_now_expense -= (*p)->get_expense();
				for (auto q = npc.handhold.begin(); q != npc.handhold.end(); q++)
				{
					if ((*q) == (*p))
					{
						npc.handhold.erase(q);
						break;
					}
				}
			}
			else
			{
				Sleep(1000);
			}
		}
		else if ((*p)->get_type() == damage || (*p)->get_type() == damage_buff || (*p)->get_type() == revert_debuff)
		{
			(*p)->play(player);
			(*p)->draw();
			npc_now_expense -= (*p)->get_expense();
			for (auto q = npc.handhold.begin(); q != npc.handhold.end(); q++)
			{
				if ((*q) == (*p))
				{
					npc.handhold.erase(q);
					break;
				}
			}
		}

		else
		{
			(*p)->play(npc);
			(*p)->draw();
			npc_now_expense -= (*p)->get_expense();
			for (auto q = npc.handhold.begin(); q != npc.handhold.end(); q++)
			{
				if ((*q) == (*p))
				{
					npc.handhold.erase(q);
					break;
				}
			}
		}
	}
	else
	{
		
		for (auto p = index.begin(); p != index.end(); p++)
		{
			if ((*p)->get_type() == damage && ((*p)->get_effect()+player.damage_buff_debuff) >= player.Now_HP)
			{
				(*p)->play(player);
				(*p)->draw();
				npc_now_expense -= (*p)->get_expense();
				for (auto q = npc.handhold.begin(); q != npc.handhold.end(); q++)
				{
					if ((*q) == (*p))
					{
						npc.handhold.erase(q);
						break;
					}
				}
				index.clear();
				goto begin;
			}
			else if ((*p)->get_type() == draw_card)
			{
				if ((5 - npc.handhold.size()) >= (*p)->get_effect())
				{
					(*p)->play(npc);
					(*p)->draw();
					npc_now_expense -= (*p)->get_expense();
					for (auto q = npc.handhold.begin(); q != npc.handhold.end(); q++)
					{
						if ((*q) == (*p))
						{
							npc.handhold.erase(q);
							index.clear();
							goto begin;
						}
					}
				}
				else
				{
					Sleep(1000);
				}
			}
			else if ((*p)->get_type() == damage)
			{
				for (auto q = index.begin(); q != index.end(); q++)
				{
					if ((*q)->get_type() == damage_buff && ((*q)->get_expense() + (*p)->get_expense() <= npc_now_expense))
					{
						(*q)->play(player);
						(*q)->draw();
						npc_now_expense -= (*q)->get_expense();
						for (auto k = npc.handhold.begin(); k != npc.handhold.end(); k++)
						{
							if ((*k) == (*q))
							{
								npc.handhold.erase(k);
								break;
							}
						}
						(*p)->play(player);
						(*p)->draw();
						npc_now_expense -= (*p)->get_expense();
						for (auto k = npc.handhold.begin(); k != npc.handhold.end(); k++)
						{
							if ((*k) == (*p))
							{
								npc.handhold.erase(k);
								break;
							}
						}
						index.clear();
						goto begin;
					}
					else if ((q + 1) == index.end())
					{
						
						(*p)->play(player);
						(*p)->draw();
						npc_now_expense -= (*p)->get_expense();
						for (auto k = npc.handhold.begin(); k != npc.handhold.end(); k++)
						{
							if ((*k) == (*p))
							{
								npc.handhold.erase(k);
								break;
							}
						}
						index.clear();
						goto begin;
					}
				}
			}
			else if ((*p)->get_type() == revert_hp)
			{
				for (auto q = index.begin(); q != index.end(); q++)
				{
					if ((*q)->get_type() == revert_buff && ((*q)->get_expense() + (*p)->get_expense() <= npc_now_expense))
					{
						(*q)->play(npc);
						(*q)->draw();
						npc_now_expense -= (*q)->get_expense();
						for (auto k = npc.handhold.begin(); k != npc.handhold.end(); k++)
						{
							if ((*k) == (*q))
							{
								npc.handhold.erase(k);
								break;
							}
						}
						(*p)->play(npc);
						(*p)->draw();
						npc_now_expense -= (*p)->get_expense();
						for (auto k = npc.handhold.begin(); k != npc.handhold.end(); k++)
						{
							if ((*k) == (*p))
							{
								npc.handhold.erase(k);
								break;
							}
						}
						index.clear();
						goto begin;
						
					}
					else if((q+1)==index.end())
					{
						if ((npc.Now_HP + (*p)->get_effect() + npc.revert_buff_debuff) <= FULL_HP)
						{
							(*p)->play(npc);
							(*p)->draw();
							npc_now_expense -= (*p)->get_expense();
							for (auto k = npc.handhold.begin(); k != npc.handhold.end(); k++)
							{
								if ((*k) == (*p))
								{
									npc.handhold.erase(k);
									break;
								}
							}
							index.clear();
							goto begin;
						}
					}
				}
			}
			else if ((*p)->get_type() == damage || (*p)->get_type() == damage_buff || (*p)->get_type() == revert_debuff)
			{
				(*p)->play(player);
				(*p)->draw();
				npc_now_expense -= (*p)->get_expense();
				for (auto k = npc.handhold.begin(); k != npc.handhold.end(); k++)
				{
					if ((*k) == (*p))
					{
						npc.handhold.erase(k);
						break;
					}
				}
				index.clear();
				goto begin;
			}
			else
			{
				(*p)->play(npc);
				(*p)->draw();
				npc_now_expense -= (*p)->get_expense();
				for (auto k = npc.handhold.begin(); k != npc.handhold.end(); k++)
				{
					if ((*k) == (*p))
					{
						npc.handhold.erase(k);
						break;
					}
				}
				index.clear();
				goto begin;
			}
		}
		
	}
}
void GAME::end() {

}