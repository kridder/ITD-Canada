#pragma once

class Stone
{
	friend class Grid;
public:
	Stone(size_t loc);
	~Stone();
	bool alone();
private:
	size_t location;
	bool adjecent[4] = { false, false, false, false }; // top, right, bottom, left
	static int stoneCount;
};