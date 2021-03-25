#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <list>
#include <iterator>
#include "forest_header.h"

using namespace std;

Grid::Grid()
{
	string cellContent;

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (i == 10 && j == 10)
			{
				cellContent = "X ";
				grid[i][j]= cellContent;       //initialising state of the middle tree
				continue;
			}

			cellContent = "& ";
			grid[i][j] = cellContent;
		}
	}
}

void Grid::updateGrid(list<string> current)
{
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