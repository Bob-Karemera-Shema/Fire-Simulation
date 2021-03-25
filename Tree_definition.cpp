#include <cstdlib>
#include <iostream>
#include <math.h>
#include <string>
#include <list>
#include <iterator>
#include "forest_header.h"

using namespace std;

Tree::Tree()
{
	state = 0;
}

int Tree::getState()
{
	return state;
}

void Tree::setState(int treeState)
{
	state = treeState;
}