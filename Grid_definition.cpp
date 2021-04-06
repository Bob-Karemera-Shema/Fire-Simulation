#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <list>
#include <iterator>
#include "forest_header.h"

using namespace std;

/// <summary>
/// updates the grid display at each time step
/// </summary>
/// <param name="current"></param>
void Grid::updateGrid(list<string> current)
{
	//using an iterator to traverse through the string list
	list<string>::iterator it = current.begin();

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (it != current.end())
			{
				grid[i][j] = *it;
				it++;
			}
		}
	}
}

/// <summary>
/// displays the grid at each time step
/// </summary>
void Grid::displayForest()
{
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			cout << grid[i][j];
		}
		cout << endl;
	}
}