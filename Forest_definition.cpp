#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <list>
#include <iterator>
#include <random>
#include "forest_header.h"

using namespace std;

/// <summary>
/// Forest class constructor
/// </summary>
Forest::Forest()
{
	Tree tree1;

	//initialise random number generator
	srand(time(NULL));

	//randomly initialise weather
	weather = rand() % 2 + 1;   //Sunny(1), Rainny(2)

	//randomly initialise moist area of the forest
	int nbrOfMoistRows = rand() % 4 + 1;
	int nbrOfMoistColumns = rand() % 4 + 1;
	moistStartingRow = rand() % 10 + 0;
	moistStartingColumn = rand() % 10 + 0;
	moistEndRow = moistStartingRow + nbrOfMoistRows;
	moistEndColumn = moistStartingColumn + nbrOfMoistColumns;

	//randomly initialise wind speed and direction
	windDirection = rand() % 4 + 1;      //North(1), South(2), East(3), West(4)
	windSpeed = rand() % 3 + 1;          //None(1), Low(2), High(3)

	//randomly generating number of initially burning trees
	initialBurningTrees = rand() % 50 + 1;
	int counter = 0;
	int row;
	int column;

	//randomly generating number of initially empty locations
	initialEmptyCells = rand() % 10 + 1;
	
	//assign tree objects to the treecollection[21][21] array
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

	counter = 0;    //counter reset to zero
	while (counter < initialEmptyCells)
	{
		//randomly initialise initial empty locations

		row = rand() % 20 + 0;      //randomly generate row index
		column = rand() % 20 + 0;   //randomly generate column index
		treeCollection[row][column].setState(2);
		counter++;
	}
}

/// <summary>
/// Updates tree objects' states after each time step
/// </summary>
void Forest::spreadFire()
{
	int not_Burning = 0;
	int burning = 1;
	int empty = 2;
	int affected = 3;  //unburnt neighbors whose state changes from unburnt to burning after a time step(unburnt trees affected by burning neighbors)
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

/// <summary>
/// traverses the forest array looking for unburnt trees with burning neighbors.
/// if a neighbor is burning and considering other variables like weather,
/// unburnt neighbors will catch fire or not depending on those variables.
/// </summary>
void Forest::unburntNeighbor()
{
	int not_Burning = 0;
	int burning = 1;
	int empty = 2;
	int affected = 3;  //unburnt neighbors whose state changes from unburnt to burning after a time step(unburnt trees affected by burning neighbors)
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (treeCollection[i][j].getState() == burning)
			{
				//North neighbor
				if (i != 0)
				{
					if (treeCollection[i - 1][j].getState() == not_Burning && groundMoisture(i - 1, j)
						&& windSp() && windDir(i, j, i - 1, j) && weatherCondition() && neighborProbability(i - 1, j))
					{
						treeCollection[i - 1][j].setState(affected);
					}
				}
				//South neighbor
				if (i != 20)
				{
					if (treeCollection[i + 1][j].getState() == not_Burning && groundMoisture(i + 1, j) 
						&& windSp() && windDir(i, j, i+1, j) && weatherCondition() && neighborProbability(i + 1, j))
					{
						treeCollection[i + 1][j].setState(affected);
					}
				}
				//West neighbor
				if (j != 0)
				{
					if (treeCollection[i][j - 1].getState() == not_Burning && groundMoisture(i, j - 1)
						&& windSp() && windDir(i, j, i, j-1) && weatherCondition() && neighborProbability(i, j-1))
					{
						treeCollection[i][j - 1].setState(affected);
					}
				}
				//East neighbor
				if (j != 20)
				{
					if (treeCollection[i][j + 1].getState() == not_Burning && groundMoisture(i, j + 1)
						&& windSp() && windDir(i, j, i, j+1) && weatherCondition() && neighborProbability(i, j+1))
					{
						treeCollection[i][j + 1].setState(affected);
					}
				}
			}
		}
	}
}

/// <summary>
/// returns a boolean value to determine whether a tree burns proportionally depending on number of burning neighbors
/// True: if number of burning neighbors is 2 or more
/// False: if number of burning neighbors is less than 2.
/// </summary>
/// <param name="a"></row index of unburnt tree>
/// <param name="b"></column index of unburnt tree>
/// <returns><boolean value>
bool Forest::neighborProbability(int a, int b)
{
	int burning = 1;
	int burningNeighbors = 0;
		//North neighbor
		if (a != 0)
		{
			if (treeCollection[a - 1][b].getState() == burning)
			{
				burningNeighbors++;
			}
		}
		//South neighbor
		if (a != 20)
		{
			if (treeCollection[a + 1][b].getState() == burning)
			{
				burningNeighbors++;
			}
		}
		//West neighbor
		if (b != 0)
		{
			if (treeCollection[a][b - 1].getState() == burning)
			{
				burningNeighbors++;
			}
		}
		//East neighbor
		if (b != 20)
		{
			if (treeCollection[a][b + 1].getState() == burning)
			{
				burningNeighbors++;
			}
		}

	if (burningNeighbors < 2) { return false; }
	else { return true; }
}

/// <summary>
///  returns a boolean value to determine whether a tree burns depending on weather conditions at runtime
/// True: if it is sunny at runtime
/// False: if it is rainny at runtime
/// </summary>
/// <returns><boolean value>
bool Forest::weatherCondition()
{
	if (weather == 1) { return true; }  //Sunny: weather==1
	else { return false; }              //Rainny: weather==2
}

/// <summary>
/// Determines whether a tree burns ddepending on whether tree is located on moist or dry ground
/// </summary>
/// <param name="a"></row index of unburnt tree>
/// <param name="b"></column index of unburnt tree>
/// <returns></returns a boolean value>
bool Forest::groundMoisture(int a, int b)
{
	int moistBurningPossibility = 20;    //when ground is moist, there is 20% chance of burning
	int dryBurningPossibility = 80;      //when ground is dry, there is 80% chance of burning

	//initialise random number generator
	srand(time(NULL));
	int random = rand() % 100 + 0;       //randomly generate a number

	if (a >= moistStartingRow && a <= moistEndRow && b >= moistStartingColumn && b <= moistEndColumn)
	{
		//tree is on moist ground
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
		//tree is on dry ground
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

/// <summary>
/// Determines whether a tree catches fire depending on wind direction
/// Reference point for the four directions (North, South, East, West) is the tree at the center of the grid.
/// </summary>
/// <param name="a"></row index of unburnt tree>
/// <param name="b"></column index of unburnt tree>
/// <param name="c"></row index of tree at the center>
/// <param name="d"></column index of tree at the center>
/// <returns></returns>
bool Forest::windDir(int a, int b, int c, int d)
{
	if (windDirection == 1)
	{
		//Wind direction is north
		if (c <= a)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (windDirection == 2)
	{
		//Wind direction is south
		if (c >= a)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (windDirection == 3)
	{
		//Wind direction is east
		if (d >= b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (windDirection == 4)
	{
		//Wind direction is west
		if (d <= b)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

/// <summary>
///  Determines whether a tree catches fire depending on wind speed
/// </summary>
/// <returns></returns a boolean value>
bool Forest::windSp()
{
	//initialise random number generator
	srand(time(NULL));
	int random = rand() % 100 + 0;
	if (windSpeed == 1)
	{
		//wind speed: None
		if (random <= 20)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (windSpeed == 2)
	{
		//wind speed: Low
		if (random <= 80)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (windSpeed == 3)
	{
		//wind speed: High
		return true;
	}
}

/// <summary>
/// returns string representation of the state of each tree in the forest after a time step
/// </summary>
/// <returns></returns a string list>
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

/// <summary>
/// returns rows located on moist ground
/// </summary>
/// <returns></returns an integer value>
void Forest::getMoistArea()
{
	cout << "Rows: " << moistStartingRow + 1 << " - " << moistEndRow + 1 << endl;
	cout << "Columns: " << moistStartingColumn + 1 << " - " << moistEndColumn + 1 << endl;
}

/// <summary>
/// returns wind direction at runtime
/// </summary>
/// <returns></returns string value>
string Forest::getWindDirection()
{
	if (windDirection == 1)
	{
		return "North";
	}
	else if (windDirection == 2)
	{
		return "South";
	}
	else if (windDirection == 3)
	{
		return "East";
	}
	else if (windDirection == 4)
	{
		return "West";
	}
}

/// <summary>
/// returns wind speed at runtime
/// </summary>
/// <returns></returns string value>
string Forest::getWindSpeed()
{
	if (windSpeed == 1)
	{
		return "None";
	}
	else if (windSpeed == 2)
	{
		return "Low";
	}
	else if (windSpeed == 3)
	{
		return "High";
	}
}

/// <summary>
/// returns weather condition at runtime
/// </summary>
/// <returns></returns string value>
string Forest::getWeather()
{
	if (weather == 1) { return "Sunny"; }
	else { return "Rainny"; }
}

int Forest::burningTrees()
{
	int nbrOfBurning = 0;
	int burning = 1;
	for (int i = 0; i < 21; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (treeCollection[i][j].getState() == burning)
			{
				nbrOfBurning++;
			}
		}
	}

	return nbrOfBurning;
}