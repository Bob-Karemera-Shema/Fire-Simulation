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
	//Tree current;
public:
	Forest();
	bool burnProbability();
	void timeStepUpdate();
	void unburnt();
	list<string> getTrees();
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
