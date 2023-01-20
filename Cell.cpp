#include "Cell.h"
Cell::Cell()
{
	this->status = empty;
}
Cell::Cell(CellStatus newStatus)
{
	this->status = newStatus;
}
int Cell::getStatus() const
{
	return this->status;
}

void Cell::setStatus(CellStatus newStatus) 
{
	this->status = newStatus;
}

