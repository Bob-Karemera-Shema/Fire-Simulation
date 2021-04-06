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
	char val;   //user input for each time step
	Forest forest1;  //forest object
	Grid view;  //grid object for display
	int value = 0;
	list<string> updatedForest;

	while (value!=120)
	{
		system("CLS");
		updatedForest = forest1.getTrees();  //get current forest state
		view.updateGrid(updatedForest);  //update grid
		view.displayForest();   //display forest grid on console

		forest1.unburntNeighbor();  //checking unburnt trees
		forest1.spreadFire();  //spreading fire

		cout << endl;
		cout << "Weather: " << forest1.getWeather() << endl;
		cout << "Moist Ground" << endl;
		cout << "Rows: " << forest1.getMoistRow() + 1 << endl;
		cout << "Columns: " << forest1.getMoistColumn() + 1 << endl;
		cout << "Wind Variables" << endl;
		cout << "Direction: " << forest1.getWindDirection() << endl;
		cout << "Speed: " << forest1.getWindSpeed() << endl;
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