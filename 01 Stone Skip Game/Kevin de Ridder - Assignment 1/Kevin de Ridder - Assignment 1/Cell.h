#pragma once

#include "Stone.h"

class Cell {
	friend class Grid;
public:
	Cell();
	bool isFilled() const;
private:
	Stone * filled;
};