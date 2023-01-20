#include "bot.h"
#include <iostream>
#include "Presenter.h"

bot::bot(int N) :Botx(0), Boty(0), bot_mask(N, N, 0, undef), bot_score(0), bot_find_ship(false) {}

void bot::bot_move(Area& Board)
{
		do {
			if (bot_score == 18) //бот виграв, закінчуємо цикл
			{
				break;
			}
			while (!find_new_coordinates()) {}//знаходимо нові координати
		} while (bot_attack(Board, Botx, Boty)); //якщо бот промахнувся, то хід бота переходить до гравця і хід бота завершено

}

bool bot::find_new_coordinates() //функція знаходження нових координат
{
	if (!bot_find_ship)//якщо перший режим
	{
		while (bot_mask.getCell(Botx, Boty).getStatus() != undef)//рандомно знаходимо нові координати
		{
			Botx = rand() % 10;
			Boty = rand() % 10;
		}
		return true;
	}
	else
	{
		directions cur_dir = q_dir.front();//зчитуємо поточний напрямок і перевіряємо чи наступна комірка підходить для вистрілу
		switch (cur_dir)
		{
		case UP:
			if (!bot_mask.isEdgeCase(Botx - 1, Boty) && bot_mask.getCell(Botx - 1, Boty).getStatus() == undef)
			{
				Botx--; //якщо підходить то змінюємо значення координат для вистрілу
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
		Botx = FindedX;//якщо поточний напрямок не підходить 
		q_dir.pop(); //видаляємо його
		if (q_dir.empty())//закінчився режим знищення корабля
		{
			bot_find_ship = false; 
		}
		return false;
	}
}

bool bot::bot_attack(Area& Board, int ShootX, int ShootY)
{
	if (Board.getCell(ShootX, ShootY).getStatus() == deck) //бот перевіряє чи потрапив він на клітинку з палубою
	{
		Board.setCell(kill, ShootX, ShootY); // бот помічає в основному полі клітинку, як вбиту
		bot_mask.setCell(kill, ShootX, ShootY); //бот помічає в масці клітинку, як вбиту 
		bot_score++; //збільшується рахунок бота
		std::cout << "X coordinate: " << std::endl;
		std::cout << ShootX << " " << std::endl;
		std::cout << "Y coordinate: " << std::endl;
		std::cout << ShootY << " " << std::endl;
		if (!bot_find_ship)// якщо бот потрапив на цей корабель вперше
		{
			FindedX = ShootX; // запам'ятовуємо клітинку в якій бот знайшов палубу корабля
			FindedY = ShootY;
			find_directions(FindedX, FindedY);//знайдемо можливі напрямки подальших ударів навколо цієї клітинки
			if (!q_dir.empty()) //перевіримо чи не знайшли ми одразу однопалубний корабель
			{
				bot_find_ship = true; //якщо знайдена палуба не належить однопалубному кораблю, то входимо в режим знищення корабля
			}
		}
		return true;

	}
	else //якщо бот не потрапив у клітинку з палубою
	{
		bot_mask.setCell(empty, ShootX, ShootY); // бот помічає в масці клітинку, як пусту
		if (bot_find_ship) //якщо бот знаходиться в режимі знищення корабля
		{
			q_dir.pop(); // прибираємо напрямок в якому рухався бот з черги
			Botx = FindedX;
			Boty = FindedY;//координати для вистрілу знову на першій знайденій палубі
			if (q_dir.empty())// і якщо це був останній напрямок для пошуку
			{
				bot_find_ship = false; //весь корабель був знищений, "режим знищення" вимкнено
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
	} //очищуємо чергу

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