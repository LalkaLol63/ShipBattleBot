#include <iostream>
#include "Area.h"
#include "Presenter.h"
#include <ctime>
#include "bot.h"
#include <conio.h>
#include <windows.h>
const int rows = 10;
const int elements = 10;

int main()
{
	
	srand(time(NULL));
	Area botArea = Area(rows, elements, 10, empty);
	Area userArea = Area(rows, elements, 10, empty);

	ConsolePresenter presenter;
	botArea.SetShips();
	userArea.SetShips();
	std::cout << "My position: " << std::endl;
	presenter.DisplayArea(userArea);
	std::cout << std::endl;
	std::cout << "Bot position: " << std::endl;
	presenter.DisplayArea(botArea);
	bot GameBot(rows);

	while (GameBot.getBotScore() != 18)
	{
		GameBot.bot_move(userArea);
		std::cout << std::endl;
		presenter.DisplayArea(userArea);
		std::cout << std::endl;
		std::cout << "bot mask" << std::endl;
		presenter.DisplayArea(GameBot.get_bot_mask());
		_getch();
	}
	return 0;
}