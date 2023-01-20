#include "bot.h"
#include <iostream>
#include "Presenter.h"

bot::bot(int N) :Botx(0), Boty(0), bot_mask(N, N, 0, undef), bot_score(0), bot_find_ship(false) {}

void bot::bot_move(Area& Board)
{
		do {
			if (bot_score == 18) //іиіоаидимс
			{
				break;
			}
			while (!find_new_coordinates()) {}//çíàõîäèìî íîâ³ êîîğäèíàòè
		} while (bot_attack(Board, Botx, Boty)); //ÿêùî áîò ïğîìàõíóâñÿ, òî õ³ä áîòà ïåğåõîäèòü äî ãğàâöÿ ³ õ³ä áîòà çàâåğøåíî

}

bool bot::find_new_coordinates() //ôóíêö³ÿ çíàõîäæåííÿ íîâèõ êîîğäèíàò
{
	if (!bot_find_ship)//ÿêùî ïåğøèé ğåæèì
	{
		while (bot_mask.getCell(Botx, Boty).getStatus() != undef)//ğàíäîìíî çíàõîäèìî íîâ³ êîîğäèíàòè
		{
			Botx = rand() % 10;
			Boty = rand() % 10;
		}
		return true;
	}
	else
	{
		directions cur_dir = q_dir.front();//ç÷èòóºìî ïîòî÷íèé íàïğÿìîê ³ ïåğåâ³ğÿºìî ÷è íàñòóïíà êîì³ğêà ï³äõîäèòü äëÿ âèñòğ³ëó
		switch (cur_dir)
		{
		case UP:
			if (!bot_mask.isEdgeCase(Botx - 1, Boty) && bot_mask.getCell(Botx - 1, Boty).getStatus() == undef)
			{
				Botx--; //ÿêùî ï³äõîäèòü òî çì³íşºìî çíà÷åííÿ êîîğäèíàò äëÿ âèñòğ³ëó
				return true;
			}
			break;
		case LEFT:
			if (!bot_mask.isEdgeCase(Botx, Boty - 1) && bot_mask.getCell(Botx, Boty - 1).getStatus() == undef)
			{
				Boty--;
				return true;
			}
			break;
		case DOWN:
			if (!bot_mask.isEdgeCase(Botx + 1, Boty) && bot_mask.getCell(Botx + 1, Boty).getStatus() == undef)
			{
				Botx++;
				return true;
			}
			break;
		case RIGHT:
			if (!bot_mask.isEdgeCase(Botx, Boty + 1) && bot_mask.getCell(Botx, Boty + 1).getStatus() == undef)
			{
				Boty++;
				return true;
			}
			break;
		}
		Boty = FindedY;
		Botx = FindedX;//ÿêùî ïîòî÷íèé íàïğÿìîê íå ï³äõîäèòü 
		q_dir.pop(); //âèäàëÿºìî éîãî
		if (q_dir.empty())//çàê³í÷èâñÿ ğåæèì çíèùåííÿ êîğàáëÿ
		{
			bot_find_ship = false; 
		}
		return false;
	}
}

bool bot::bot_attack(Area& Board, int ShootX, int ShootY)
{
	if (Board.getCell(ShootX, ShootY).getStatus() == deck) //áîò ïåğåâ³ğÿº ÷è ïîòğàïèâ â³í íà êë³òèíêó ç ïàëóáîş
	{
		Board.setCell(kill, ShootX, ShootY); // áîò ïîì³÷àº â îñíîâíîìó ïîë³ êë³òèíêó, ÿê âáèòó
		bot_mask.setCell(kill, ShootX, ShootY); //áîò ïîì³÷àº â ìàñö³ êë³òèíêó, ÿê âáèòó 
		bot_score++; //çá³ëüøóºòüñÿ ğàõóíîê áîòà
		std::cout << "X coordinate: " << std::endl;
		std::cout << ShootX << " " << std::endl;
		std::cout << "Y coordinate: " << std::endl;
		std::cout << ShootY << " " << std::endl;
		if (!bot_find_ship)// ÿêùî áîò ïîòğàïèâ íà öåé êîğàáåëü âïåğøå
		{
			FindedX = ShootX; // çàïàì'ÿòîâóºìî êë³òèíêó â ÿê³é áîò çíàéøîâ ïàëóáó êîğàáëÿ
			FindedY = ShootY;
			find_directions(FindedX, FindedY);//çíàéäåìî ìîæëèâ³ íàïğÿìêè ïîäàëüøèõ óäàğ³â íàâêîëî ö³º¿ êë³òèíêè
			if (!q_dir.empty()) //ïåğåâ³ğèìî ÷è íå çíàéøëè ìè îäğàçó îäíîïàëóáíèé êîğàáåëü
			{
				bot_find_ship = true; //ÿêùî çíàéäåíà ïàëóáà íå íàëåæèòü îäíîïàëóáíîìó êîğàáëş, òî âõîäèìî â ğåæèì çíèùåííÿ êîğàáëÿ
			}
		}
		return true;

	}
	else //ÿêùî áîò íå ïîòğàïèâ ó êë³òèíêó ç ïàëóáîş
	{
		bot_mask.setCell(empty, ShootX, ShootY); // áîò ïîì³÷àº â ìàñö³ êë³òèíêó, ÿê ïóñòó
		if (bot_find_ship) //ÿêùî áîò çíàõîäèòüñÿ â ğåæèì³ çíèùåííÿ êîğàáëÿ
		{
			q_dir.pop(); // ïğèáèğàºìî íàïğÿìîê â ÿêîìó ğóõàâñÿ áîò ç ÷åğãè
			Botx = FindedX;
			Boty = FindedY;//êîîğäèíàòè äëÿ âèñòğ³ëó çíîâó íà ïåğø³é çíàéäåí³é ïàëóá³
			if (q_dir.empty())// ³ ÿêùî öå áóâ îñòàíí³é íàïğÿìîê äëÿ ïîøóêó
			{
				bot_find_ship = false; //âåñü êîğàáåëü áóâ çíèùåíèé, "ğåæèì çíèùåííÿ" âèìêíåíî
			}
		}
		return false;
	}
}

void bot::find_directions(int XtoDir, int YtoDir)
{
	while (!q_dir.empty())
	{
		q_dir.pop();
	} //î÷èùóºìî ÷åğãó

	if (!bot_mask.isEdgeCase(XtoDir - 1, YtoDir) && bot_mask.getCell(XtoDir - 1, YtoDir).getStatus() == undef)
	{
		q_dir.push(UP);

	}
	if (!bot_mask.isEdgeCase(XtoDir + 1, YtoDir) && bot_mask.getCell(XtoDir + 1, YtoDir).getStatus() == undef)
	{
		q_dir.push(DOWN);

	}
	if (!bot_mask.isEdgeCase(XtoDir, YtoDir - 1) && bot_mask.getCell(XtoDir, YtoDir - 1).getStatus() == undef)
	{
		q_dir.push(LEFT);

	}
	if (!bot_mask.isEdgeCase(XtoDir, YtoDir + 1) && bot_mask.getCell(XtoDir, YtoDir + 1).getStatus() == undef)
	{
		q_dir.push(RIGHT);

	}

}

int bot::getBotScore()
{
	return bot_score;
}

Area bot::get_bot_mask()
{
	return bot_mask;
}
