#pragma once
#include "Area.h" 
class Presenter
{
public:
	virtual void DisplayArea(Area area) = 0;
};

class ConsolePresenter : Presenter
{
public:
	void DisplayArea(Area area) override
	{
		for (int i = 0; i < area.getRows(); i++)
		{
			for (int j = 0; j < area.getElements(); j++)
			{
				std::cout << area.getCell(i, j).getStatus() << " ";
			}
			std::cout << std::endl;
		}
	}
};
