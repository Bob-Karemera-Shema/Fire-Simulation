#ifndef forest_h
#define forest_h

#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <list>
#include <iterator>

using namespace std;

class Tree
{
	int state; //holds information about the state of the tree
public:
	Tree();
	int getState();
	void setState(int treeState);
};

class Forest
{
	Tree treeCollection[21][21];
	int groundMoistureRow;
	int groundMoistureColumn;
	int initialBurningTrees;
	int windSpeed;
	int windDirection;
public:
	Forest();
	int randomGenerator(int a, int b);
	bool groundMoisture(int a, int b);
	bool windDir(int a, int b, int c, int d);
	bool windSp();
	void spreadFire();
	void unburntNeighbor();
	list<string> getTrees();
	int getMoistRow();
	int getMoistColumn();
	string getWindDirection();
	string getWindSpeed();
};

class Grid
{
	string grid[21][21];
public:
	Grid();
	void updateGrid(list<string> current);
	void displayForest();
};

#endif
