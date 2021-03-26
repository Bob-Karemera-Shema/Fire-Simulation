#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <list>
#include <iterator>
#include <random>
#include "forest_header.h"

using namespace std;

Forest::Forest()
{
	Tree tree1;

	//initialise random number generator
	srand(time(NULL));

	//initialise ground moisture attribute
	groundMoistureRow = rand() % 20 + 0;
	groundMoistureColumn = rand() % 20 + 0;

	//randomly generating number of initially burning trees
	initialBurningTrees = rand() % 10 + 1;
	int counter = 0;
	int row;
	int column;
	
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			treeCollection[i][j] = tree1;
		}
	}

	while (counter < initialBurningTrees)
	{
		//randomly initialise initial burning trees

		row = rand() % 20 + 0;      //randomly generate row index
		column = rand() % 20 + 0;   //randomly generate column index
		treeCollection[row][column].setState(1);
		counter++;
	}
}

void Forest::spreadFire()
{
	int not_Burning = 0;
	int burning = 1;
	int empty = 2;
	int affected = 3;
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (treeCollection[i][j].getState() == burning)
			{
				treeCollection[i][j].setState(empty);
			}
			else if (treeCollection[i][j].getState() == affected)
			{
				treeCollection[i][j].setState(burning);
			}
			else if (treeCollection[i][j].getState() == empty) {}
		}
	}
}

void Forest::unburntNeighbor()
{
	int not_Burning = 0;
	int burning = 1;
	int empty = 2;
	int affected = 3;
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (treeCollection[i][j].getState() == burning)
			{
				//North neighbor
				if (i != 0)
				{
					if (treeCollection[i - 1][j].getState() == not_Burning && burnProbability(i - 1, j))
					{
						treeCollection[i - 1][j].setState(affected);
					}
				}
				//South neighbor
				if (i != 20)
				{
					if (treeCollection[i + 1][j].getState() == not_Burning && burnProbability(i + 1, j))
					{
						treeCollection[i + 1][j].setState(affected);
					}
				}
				//West neighbor
				if (j != 0)
				{
					if (treeCollection[i][j - 1].getState() == not_Burning && burnProbability(i, j - 1))
					{
						treeCollection[i][j - 1].setState(affected);
					}
				}
				//East neighbor
				if (j != 20)
				{
					if (treeCollection[i][j + 1].getState() == not_Burning && burnProbability(i, j + 1))
					{
						treeCollection[i][j + 1].setState(affected);
					}
				}
			}
		}
	}
}

bool Forest::burnProbability(int a, int b)
{
	int moistBurningPossibility = 20;    //when ground is moist, there is 20% chance of burning
	int dryBurningPossibility = 50;      //when ground is moist, there is 50% chance of burning

	int random = rand() % 100 + 0;

	if (a <= groundMoistureRow && b <= groundMoistureColumn)
	{
		if (random <= moistBurningPossibility)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (random <= dryBurningPossibility)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

list<string> Forest::getTrees()
{
	string cellContent;
	list<string> current;

	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (treeCollection[i][j].getState() == 0)
			{
				cellContent = "& ";
				current.push_back(cellContent);
			}
			else if (treeCollection[i][j].getState() == 1)
			{
				cellContent = "X ";
				current.push_back(cellContent);
			}
			else
			{
				cellContent = "  ";
				current.push_back(cellContent);
			}
		}
	}

	return current;
}


int Forest::getMoistRow()
{
	return groundMoistureRow;
}

int Forest::getMoistColumn()
{
	return groundMoistureColumn;
}