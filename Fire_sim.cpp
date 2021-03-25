#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <list>
#include <iterator>
#include "forest_header.h"

using namespace std;

int main(void)
{
	char val;
	Forest forest1;
	Grid view;
	int value = 0;
	list<string> updatedForest;

	while (value!=120)
	{
		system("CLS");
		updatedForest = forest1.getTrees();
		view.updateGrid(updatedForest);
		view.displayForest();

		forest1.unburnt();
		forest1.timeStepUpdate();
		//updatedForest = forest1.getTrees();
		//view.updateGrid(updatedForest);
		cout << endl;

		cout << "PRESS:\n";
		cout << "1. Press any key to update forest view\n";
		cout << "2. 'Space' key to stop simulation\n";
		cin >> val;

		value = (int)val;
	}

	cout << "END OF SIMULATION\n";

	system("PAUSE");
	return 0;
}