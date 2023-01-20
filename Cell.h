#include "Header.h"
#pragma once
class Cell
{
private:
	int status;
public:
	Cell();

	Cell(CellStatus newStatus);

	int getStatus() const;

	void setStatus(CellStatus newStatus);
};

