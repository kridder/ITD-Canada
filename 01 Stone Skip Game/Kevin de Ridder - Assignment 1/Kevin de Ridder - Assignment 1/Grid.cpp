#include "Grid.h"

Grid::Grid(int numStones, int dimension) : // default numStones = 30, dimension = 8
	grid(new Cell[dimension * dimension])
{
	width = dimension;
	size = dimension * dimension;

	// randomly distribute stones
	srand(time(NULL));
	int stonesLeft = numStones; // set the amount of stones to be placed on the grid

	while (Stone::stoneCount < (numStones * 0.8))
	{
		int deletedStones = 0;

		for (int i = 0; i < stonesLeft; ++i) // for the amount of stones left to be placed
		{
			int random = rand() % size; // get a random index for the grid
			if (!grid[random].isFilled()) // if that random position in the grid is empty
			{
				grid[random].filled = new Stone(random); // fill it with a new Stone
			}
			else
			{
				--i; // set back i by one step to find another place for this stone
			}
		} // end for

		checkAdjecent(); // check for each stone if it has any stones adjecent to it

		for (size_t i = 0; i < size; ++i) // check every cell in the grid
		{
			if (grid[i].filled != 0) // if the cell is not empty (and thus holds a stone object)
			{
				if (grid[i].filled->alone()) // if this stone is alone (has no other stone adjecent)
				{
					delete grid[i].filled; // delete this stone
					grid[i].filled = 0; // set the pointer in Cell to 0
					++deletedStones; // count how many stones are deleted in this manner
				}
			}
		} // end for

		checkAdjecent(); // check for each stone if it has any stones adjecent to it

		stonesLeft = deletedStones; // set the number of stones to be placed to the number of stones that were just removed
	} // end while

	for (int i = 0; i < stonesLeft; ++i)
	{
		int random = rand() % size; // get a random index for the grid
		if (!grid[random].isFilled()) // if that random position in the grid is empty
		{
			if (random >= width ? grid[random - width].filled != 0 : false || (random + 1) % width != 0 ? grid[random + 1].filled != 0 : false || (random + width) < size ? grid[random + width].filled != 0 : false || random % width != 0 ? grid[random - 1].filled != 0 : false)
			{
				grid[random].filled = new Stone(random); // fill it with a new Stone
			}
			else
			{
				--i; // set back i by one step to find another place for this stone
			}
		}
		else
		{
			--i; // set back i by one step to find another place for this stone
		}
	} // end for
} // end Grid contructor

Grid::~Grid() // grid destructor will delete all stones and the grid array to prevent memory leaks and errors
{
	for (size_t i = 0; i < size; ++i)
	{
		if (grid[i].filled != 0) // delete all leftover stones in the grid
		{
			delete grid[i].filled;
			grid[i].filled = 0;
		}
	} // end for

	delete grid; // deletes the new array of Cells created in the constructor
} // end Grid destrcutor

void Grid::drawGrid()
{
	// draw horizontal coordinate index
	char letter = 'A';
	cout << std::setw(5) << letter;
	for (size_t i = 1; i < width; ++i)
	{
		cout << " " << ++letter;
	} // end for

	// draw grid
	for (size_t i = 0; i < size; ++i)
	{
		if (i % width == 0) // draw vertical coordinate index
		{
			cout << endl << std::setw(3) << i / width + 1;
		}
		if (grid[i].isFilled())
		{
			cout << " o";
		}
		else
		{
			cout << " +";
		}
	} // end for
	cout << endl;
} // end function drawGrid

int Grid::getStones()
{
	return Stone::stoneCount;
} // end function getStones

void Grid::checkAdjecent()
{
	for (size_t i = 0; i < size; ++i)
	{
		if (grid[i].filled != 0)
		{
			// check top
			if (i >= width) // if i is not in the top row
			{
				if (grid[i - width].filled != 0) // if cell above this one is not empty
				{
					grid[i].filled->adjecent[0] = true;
				}
				else
				{
					grid[i].filled->adjecent[0] = false;
				}
			}
			else
			{
				grid[i].filled->adjecent[0] = false;
			}

			// check right
			if ((i + 1) % width != 0) // if i is not in the right most column
			{
				if (grid[i + 1].filled != 0) // if cell to the right of this one is not empty
				{
					grid[i].filled->adjecent[1] = true;
				}
				else
				{
					grid[i].filled->adjecent[1] = false;
				}
			}
			else
			{
				grid[i].filled->adjecent[1] = false;
			}

			// check bottom
			if ((i + width) < size) // if i is not in the bottom row
			{
				if (grid[i + width].filled != 0) // if cell below this one is not empty
				{
					grid[i].filled->adjecent[2] = true;
				}
				else
				{
					grid[i].filled->adjecent[2] = false;
				}
			}
			else
			{
				grid[i].filled->adjecent[2] = false;
			}

			// check left
			if (i % width != 0) // if i is not in the left most column
			{
				if (grid[i - 1].filled != 0) // if cell to the left of this one is not empty
				{
					grid[i].filled->adjecent[3] = true;
					}
					else
					{
						grid[i].filled->adjecent[3] = false;
					}
				}
			else
			{
				grid[i].filled->adjecent[3] = false;
			}
		}
	} // end for
} // end function checkAdjecent

size_t Grid::getPosition()
{
	char x;
	int y;

	size_t ix;
	size_t iy;

	bool invalid;

	do
	{
		cin >> x >> y;

		if (x > 64 && x < 91) // convert uppercase ASCII to int
		{
			ix = x - 65;
		}
		else if (x > 96 && x < 123) // convert lowercase ASCII to int
		{
			ix = x - 97;
		}
		else // if the user did not enter a upper or lowercase letter, ix will be set to 255 causing an error messeages on line 234 and allowing the user to enter again
		{
			ix = 255;
		}

		iy = y - 1;

		if (ix >= width || iy >= width) // if ix or iy are out of range (no need to check for smaller than 0 because they are unsingend integers (size_t))
		{
			cout << "Invalid cooridnates, please enter again:\n";
			invalid = true;
		}
		else
		{
			invalid = false;
		}
	} while (invalid);

	return ix + (iy * width);
} // end function getPosition

void Grid::moveStone()
{
	size_t from;
	size_t middle = size;
	size_t to;
	bool invalid;

	cout << "Enter the coordinates of the stone you want to move:\n";
	do
	{
		from = getPosition();

		if (!grid[from].isFilled()) // if the from cell in the grid is not filled with a stone
		{
			cout << "This position is empty, please enter the coordinates for another position:\n";
			invalid = true;
		}
		else
		{
			invalid = false;
		}
	} while (invalid);

	cout << "\nEnter the coordinates you want to move the stone to:\n";
	to = getPosition();

	if (grid[to].isFilled()) // if the destination cell in the grid already holds a stone
	{
		cout << "Invalid move: destination is not empty.\n";
		return;
	}

	if (to == from - (width * 2)) // if trying to move the stone up
	{
		if (grid[from - width].isFilled()) // if there is a stone in between from and to
		{
			middle = from - width;
		}
		else
		{
			cout << "Invalid move: no stone to jump over.\n";
			return;
		}
	}
	else if (to == from + 2 && to / width == from / width) // if trying to move the stone right AND to and from are still on the same row
	{
		if (grid[from + 1].isFilled()) // if there is a stone in between from and to
		{
			middle = from +1;
		}
		else
		{
			cout << "Invalid move: no stone to jump over.\n";
			return;
		}
	}
	else if (to == from + (width * 2)) // if trying to move the stone down
	{
		if (grid[from + width].isFilled()) // if there is a stone in between from and to
		{
			middle = from + width;
		}
		else
		{
			cout << "Invalid move: no stone to jump over.\n";
			return;
		}
	}
	else if (to == from - 2 && to / width == from / width) // if trying to move the stone left AND to and from are still on the same row
	{
		if (grid[from - 1].isFilled()) // if there is a stone in between from and to
		{
			middle = from - 1;
		}
		else
		{
			cout << "Invalid move: no stone to jump over.\n";
			return;
		}
	}
	else
	{
		cout << "Invalid move: move not in range.\n";
		return;
	}

	if (middle < size) // if a valid move was made
	{
		grid[to].filled = grid[from].filled;
		grid[from].filled = 0;

		delete grid[middle].filled;
		grid[middle].filled = 0;

		checkAdjecent();
	}
} // end function moveStone


int Grid::moveableStones()
{
	int count = 0; // counts the number of stones left with a valid move

	for (size_t i = 0; i < size; ++i) // check every cell in the grid
	{
		if (grid[i].filled != 0) // if the cell is not empty
		{
			if (!grid[i].filled->alone()) // and the stone in the cell has a stone adjecent to it (this is detmerined by function checkAdjecent after every move)
			{
				++count; // add one to the count
			}
		}
	} // end for

	return count;
} // end function moveableStones

void Grid::playGame()
{
	drawGrid();
	cout << "Stones left: " << getStones() << endl << endl;

	while (moveableStones()) // play the game as long as there is at least one stone left that is not alone
	{
		moveStone();
		cout << endl;

		drawGrid();
		cout << "Stones left: " << getStones() << endl << endl;
	}

	cout << "\nNo moves left.\nFinal score: " << getStones() << endl << endl;
} // end function playGame