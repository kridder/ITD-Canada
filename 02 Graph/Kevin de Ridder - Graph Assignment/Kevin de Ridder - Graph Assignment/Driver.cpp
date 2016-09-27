#include <iostream>
using std::cout;
using std::endl;
using std::cin;
using std::left;

#include <iomanip>
using std::setw;

#include "Graph.h"
#include "GraphNode.h"
#include "GraphArc.h"

void printSystems(Graph & starChart);
void printSystemJumpPoints(Graph & starChart);
void TravelGraph(Graph & starChart);

int main()
{
	bool run = true;
	int userInput;
	string stringInput;
	size_t indexInput;
	size_t indexInput2;
	bool boolInput;
	Graph starChart;

	starChart.addNode(*new GraphNode("00 Sun"));
	starChart.addNode(*new GraphNode("01 Proxima Centauri"));
	starChart.addNode(*new GraphNode("02 Alpha Centauri"));
	starChart.addNode(*new GraphNode("03 Barnard's Star"));
	starChart.addNode(*new GraphNode("04 Luhman 16A"));
	starChart.addNode(*new GraphNode("05 Luhman 16B"));
	starChart.addNode(*new GraphNode("06 WISE 0855-0714"));

	starChart.addArc(0, 1, 4, true); // add two-way arc of 4ly from Sun to Proxima Centauri
	starChart.addArc(0, 2, 4, true); // add two-way arc of 4ly from Sun to Alpha Centauri
	starChart.addArc(0, 3, 6, true); // add two-way arc of 6ly from Sun to Alpha Centauri
	starChart.addArc(1, 2, 0, true); // add two-way arc of 0ly from Proxima Centauri to Alpha Centauri
	starChart.addArc(1, 4, 2, true); // add two-way arc of 2ly from Proxima Centauri to Luhman 16A
	starChart.addArc(2, 4, 2, true); // add two-way arc of 2ly from Alpha Centauri to Luhman 16A
	starChart.addArc(3, 6, 2, true); // add two-way arc of 2ly from Barnard's Star to WISE 0855-0714
	starChart.addArc(4, 5, 0, true); // add two-way arc of 0ly from Luhman 16A to Luhman 16B
	starChart.addArc(4, 6, 4); // add one-way arc of 4ly from Luhman 16A to WISE 0855-0714

	printSystems(starChart);

	printSystemJumpPoints(starChart);

	cout << "Depth traverse 00 Sun:\n";
	starChart.depthTraverse(*starChart.getNodes()[0]);
	cout << endl;

	cout << "Level traverse 00 Sun:\n";
	starChart.levelTraverse(*starChart.getNodes()[0]);
	cout << endl;

	cout << "Enter 1 to modify Graph.\nEnter 0 to Quit.\n\n";
	cin >> userInput;
	cout << endl;

	run = userInput;

	while (run)
	{
		cout << "1: Add Node.\n"
			"2: Remove Node.\n"
			"3: Add Arc.\n"
			"4: Remove Arc.\n"
			"5: Print all Nodes.\n"
			"6: Print all Nodes + Arcs.\n"
			"7: Depth Traverse.\n"
			"8: Level Traverse.\n"
			"9: Travel the Stars.\n"
			"0: Quit.\n\n";
		cin >> userInput;
		cout << endl;

		switch (userInput)
		{
		case 0:
			run = false;
			break;
		case 1:
			cout << "Enter the name of the new node:\n";
			cin.ignore(1000, '\n');
			std::getline(cin, stringInput);
			cout << endl;

			starChart.addNode(*new GraphNode(stringInput));
			cout << "Node added.\n";
			cout << endl;
			break;
		case 2:
			cout << "Enter the index of the node you want to remove:\n";
			cin >> indexInput;
			cout << endl;

			starChart.removeNode(indexInput);
			cout << "Node removed.\n";
			cout << endl;
			break;
		case 3:
			cout << "Enter the index of the home node:\n";
			cin >> indexInput;
			cout << endl;

			cout << "Enter the index of the destination node:\n";
			cin >> indexInput2;
			cout << endl;

			cout << "Enter the weight of the arc:\n";
			cin >> userInput;
			cout << endl;

			cout << "Enter 0 for a one way or 1 for a two way arc:\n";
			cin >> boolInput;
			cout << endl;

			starChart.addArc(indexInput, indexInput2, userInput, boolInput);
			cout << "Arc added.\n";
			cout << endl;
			break;
		case 4:
			cout << "Enter the index of the home node:\n";
			cin >> indexInput;
			cout << endl;

			cout << "Enter the index of the destination node:\n";
			cin >> indexInput2;
			cout << endl;

			cout << "Enter 0 for a one way or 1 for a two way removal:\n";
			cin >> boolInput;
			cout << endl;

			starChart.removeArc(indexInput, indexInput2, boolInput);
			cout << "Arc removed.\n";
			cout << endl;
			break;
		case 5:
			printSystems(starChart);
			break;
		case 6:
			printSystemJumpPoints(starChart);
			break;
		case 7:
			cout << "Enter the index of the home node:\n";
			cin >> indexInput;
			cout << endl;

			if (indexInput < starChart.getCount())
			{
				starChart.depthTraverse(*starChart.getNodes()[indexInput]);
			}
			else
			{
				cout << "ERROR: Node not found.\n";
			}
			cout << endl;
			break;
		case 8:
			cout << "Enter the index of the home node:\n";
			cin >> indexInput;
			cout << endl;

			if (indexInput < starChart.getCount())
			{
				starChart.levelTraverse(*starChart.getNodes()[indexInput]);
			}
			else
			{
				cout << "ERROR: Node not found.\n";
			}
			cout << endl;
			break;
		case 9:
			TravelGraph(starChart);
			cout << endl;
			break;
		}
	} // end while

	return 0;
} // end main

void printSystems(Graph & starChart)
{
	cout << "Systems:" << endl;
	for each(GraphNode * node in starChart.getNodes())
	{
		cout << node->getData() << endl;
	} // end for each
	cout << endl;
}

void printSystemJumpPoints(Graph & starChart)
{
	for each(GraphNode * node in starChart.getNodes())
	{
		cout << "Current System:\n";
		cout << node->getData() << endl;
		cout << "Jump points:\n";
		if (!node->getArcs().empty())
		{
			for each(GraphArc * arc in node->getArcs())
			{
				cout << left << setw(20) << arc->getNode()->getData() + ":" << "\t" << arc->getArcWeight() << "ly." << endl;
			} // end for each
		}
		else
		{
			cout << "none\n";
		}
		cout << endl;
	} // end for each
	cout << endl;
}

void TravelGraph(Graph & starChart)
{
	int userInput;
	size_t indexInput;

	GraphNode * currentSystem = starChart.getNodes()[0];
	int fuel = 20;

	while (true)
	{
		cout << "Current System: " << currentSystem->getData() << endl;
		cout << "Fuel reserve: " << fuel << "ly.\n";
		cout << endl;

		cout << "1: Get systems overview.\n"
			"2: Get jump point overview for current system.\n"
			"3: Depth scan possible routes.\n"
			"4: Level scan possible routes.\n"
			"5: Attempt Jump\n"
			<< (currentSystem == starChart.getNodes()[0] ? "6: Fuel up.\n" : "") <<
			"0: Quit\n\n";

		cin >> userInput;
		cout << endl;

		if (userInput == 0)
		{
			return;
		}
		else if (userInput == 1)
		{
			printSystems(starChart);
		}
		else if (userInput == 2)
		{
			cout << "Current System:\n";
			cout << currentSystem->getData() << endl;
			cout << "Jump points:\n";
			if (!currentSystem->getArcs().empty())
			{
				for each(GraphArc * arc in currentSystem->getArcs())
				{
					cout << left << setw(20) << arc->getNode()->getData() + ":" << "\t" << arc->getArcWeight() << "ly." << endl;
				} // end for each
			}
			else
			{
				cout << "none\n";
			}
			cout << endl;
		}
		else if (userInput == 3)
		{
			starChart.depthTraverse(*currentSystem);
			cout << endl;
		}
		else if (userInput == 4)
		{
			starChart.levelTraverse(*currentSystem);
			cout << endl;
		}
		else if (userInput == 5)
		{
			cout << "Enter coordinates of the system you want to jump to.\n";
			cin >> indexInput;
			cout << endl;

			// check if index is in range
			if (indexInput >= 0 && indexInput < starChart.getCount())
			{
				GraphNode * destination = currentSystem->getNode(starChart.getNodes()[indexInput]);

				if (destination != 0)
				{
					int distance = currentSystem->getArc(starChart.getNodes()[indexInput])->getArcWeight();

					if (distance != 0)
					{
						if (fuel > 0)
						{
							cout << "Engaging hyperdrive.\n\n";

							if (fuel >= distance)
							{
								currentSystem = destination;
								fuel -= distance;

								cout << "Jump succesful.\n";
							}
							else
							{
								currentSystem = 0;
								fuel = 0;

								cout << "Hyperdrive failure: no fuel left.\n";
								cout << "Deploying solar sail.\n\n";

								cout << "ETA: in 357 years.\n\n";

								cout << "Current System: " << "Interstellar space\n";
								cout << "Fuel reserve: " << fuel << "ly.\n";
								cout << endl;

								return;
							}
						}
						else
						{
							cout << "Jump attempt failed: no fuel left.\n";
						}
					}
					else
					{
						cout << "Deploying solar sail.\n\n";

						currentSystem = destination;

						cout << "Destination reached.\n";
					}
				}
				else
				{
					cout << "Jump attempt failed: no suitable jump point found in current system.\n";
				}
			}
			else
			{
				cout << "Error: Invalid Coordinates entered.\n";
			}
			cout << endl;
		}
		else if (userInput == 6 && currentSystem == starChart.getNodes()[0])
		{
			fuel = 20;

			cout << "Fuel level back up to " << fuel << "ly.\n";
			cout << endl;
		}

		cout << endl;

	} // end while

} // end function TravelGraph