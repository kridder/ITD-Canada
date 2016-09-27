#pragma once

#include "Cell.h"

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

#include <iomanip>

#include <ctime>

class Grid {
public:
	Grid(int numStones = 30, int dimension = 8);
	~Grid();
	void drawGrid();
	int getStones();
	void checkAdjecent();
	size_t getPosition();
	void moveStone();
	int moveableStones();
	void playGame();
private:
	Cell *const grid;
	size_t width;
	size_t size;
};