#include "Stone.h"

int Stone::stoneCount = 0;

Stone::Stone(size_t loc)
{
	location = loc;
	++stoneCount;
} // end Stone constructor

Stone::~Stone()
{
	--stoneCount;
} // end Stone destructor

bool Stone::alone() // only returns true if there are no stones adjecent
{
	return !(adjecent[0] || adjecent[1] || adjecent[2] || adjecent[3]);
} // end function alone