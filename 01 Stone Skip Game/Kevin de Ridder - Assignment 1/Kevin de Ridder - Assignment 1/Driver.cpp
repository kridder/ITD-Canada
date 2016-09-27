#include "Grid.h"

int main()
{
	int choice;

	while (true)
	{

		cout << "1: Play default game\n2: Play large game\n0: Quit\n\n";
		cin >> choice;

		if (choice == 0)
		{
			break;
		}
		else if (choice == 1)
		{
			Grid grid;

			cout << endl;
			grid.playGame();
		}
		else if (choice == 2)
		{
			Grid grid(100,16); // grid (number of stones, width and height of the grid)

			cout << endl;
			grid.playGame();
		}

		cout << endl;
	} // end while
	return 0;
} // end main