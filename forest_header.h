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
	int state; //holds information about the state of the tree: unburnt(0), burning(1), empty/burnt(2), affected(3)
public:
	Tree();    //Constructor for Tree class
	int getState();  //returns the state of a tree object
	void setState(int treeState);  //sets the state of a tree object
};

class Forest
{
	Tree treeCollection[21][21];   //array holding all trees in the forest
	int groundMoistureRow;         //number of rows located in the moist area of the forest
	int groundMoistureColumn;      //number of columns located in the moist area of the forest
	int initialBurningTrees;       //number of initially burning trees
	int initialEmptyCells;         //number of initially empty cells
	int weather;                   //weather at runtime: Sunny(1), Rainny(2)
	int windSpeed;                 //wind speed at runtime: None(1), Low(2), High(3)
	int windDirection;             //wind direction at runtime: North(1), South(2), East(3), West(4)
public:
	Forest();      //Constructor for Forest class
	bool groundMoisture(int a, int b);      //returns whether a tree is in moist area or not
	bool neighborProbability(int a, int b); //returns whether a tree burns or not proportional to burning neighbors
	bool windDir(int a, int b, int c, int d); //returns whether a tree burns or not depending on wind direction
	bool windSp();     //returns whether a tree burns or not depending on wind direction
	bool weatherCondition();     //returns whether a tree burns or not depending on weather conditions
	void spreadFire();           //updates the state of tree objects in the forest
	void unburntNeighbor();      //checks whether uburnt trees burn or not on the next time step
	list<string> getTrees();     //returns updated grid view of the forest
	int getMoistRow();           //returns moist rows of the forest
	int getMoistColumn();        //returns moist columns of the forest
	string getWindDirection();   //returns wind direction
	string getWindSpeed();       //returns wind speed
	string getWeather();         //returns weather condition
};

class Grid
{
	string grid[21][21];       //string array holding visual representation of current forest state
public:
	Grid();                    //Grid class constructor
	void updateGrid(list<string> current);  //updates visual representation of current forest state
	void displayForest();   //displays current forest state
};

#endif
