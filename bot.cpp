#include "bot.h"
#include <iostream>
#include "Presenter.h"

bot::bot(int N) :Botx(0), Boty(0), bot_mask(N, N, 0, undef), bot_score(0), bot_find_ship(false) {}

void bot::bot_move(Area& Board)
{
		do {
			if (bot_score == 18) //��� ������, �������� ����
			{
				break;
			}
			while (!find_new_coordinates()) {}//��������� ��� ����������
		} while (bot_attack(Board, Botx, Boty)); //���� ��� �����������, �� ��� ���� ���������� �� ������ � ��� ���� ���������

}

bool bot::find_new_coordinates() //������� ����������� ����� ���������
{
	if (!bot_find_ship)//���� ������ �����
	{
		while (bot_mask.getCell(Botx, Boty).getStatus() != undef)//�������� ��������� ��� ����������
		{
			Botx = rand() % 10;
			Boty = rand() % 10;
		}
		return true;
	}
	else
	{
		directions cur_dir = q_dir.front();//������� �������� �������� � ���������� �� �������� ������ �������� ��� �������
		switch (cur_dir)
		{
		case UP:
			if (!bot_mask.isEdgeCase(Botx - 1, Boty) && bot_mask.getCell(Botx - 1, Boty).getStatus() == undef)
			{
				Botx--; //���� �������� �� ������� �������� ��������� ��� �������
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
		Botx = FindedX;//���� �������� �������� �� �������� 
		q_dir.pop(); //��������� ����
		if (q_dir.empty())//��������� ����� �������� �������
		{
			bot_find_ship = false; 
		}
		return false;
	}
}

bool bot::bot_attack(Area& Board, int ShootX, int ShootY)
{
	if (Board.getCell(ShootX, ShootY).getStatus() == deck) //��� �������� �� �������� �� �� ������� � �������
	{
		Board.setCell(kill, ShootX, ShootY); // ��� ����� � ��������� ��� �������, �� �����
		bot_mask.setCell(kill, ShootX, ShootY); //��� ����� � ����� �������, �� ����� 
		bot_score++; //���������� ������� ����
		std::cout << "X coordinate: " << std::endl;
		std::cout << ShootX << " " << std::endl;
		std::cout << "Y coordinate: " << std::endl;
		std::cout << ShootY << " " << std::endl;
		if (!bot_find_ship)// ���� ��� �������� �� ��� �������� ������
		{
			FindedX = ShootX; // �����'������� ������� � ��� ��� ������� ������ �������
			FindedY = ShootY;
			find_directions(FindedX, FindedY);//�������� ������ �������� ��������� ����� ������� ���� �������
			if (!q_dir.empty()) //��������� �� �� ������� �� ������ ������������ ��������
			{
				bot_find_ship = true; //���� �������� ������ �� �������� ������������� �������, �� ������� � ����� �������� �������
			}
		}
		return true;

	}
	else //���� ��� �� �������� � ������� � �������
	{
		bot_mask.setCell(empty, ShootX, ShootY); // ��� ����� � ����� �������, �� �����
		if (bot_find_ship) //���� ��� ����������� � ����� �������� �������
		{
			q_dir.pop(); // ��������� �������� � ����� ������� ��� � �����
			Botx = FindedX;
			Boty = FindedY;//���������� ��� ������� ����� �� ������ �������� �����
			if (q_dir.empty())// � ���� �� ��� ������� �������� ��� ������
			{
				bot_find_ship = false; //���� �������� ��� ��������, "����� ��������" ��������
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
	} //������� �����

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