/*
 * GridHistory.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: bemayer
 */

#include "GridHistory.h"

GridHistory::GridHistory() {
	// TODO Auto-generated constructor stub

}

GridHistory::~GridHistory() {
	// TODO Auto-generated destructor stub
}

Grid* GridHistory::getInitialGrid()
{
	Grid* initGrid = gridHistoryLevels.at(0).at(0); //Assumes the grid at the first level only has the initial grid
	return initGrid;
}


//gets the subgrids at level n of the gridhistory object
vector<Grid*> GridHistory::getNthLevelOfGrid(int n)
{
	return gridHistoryLevels.at(n);
}


//replaces the nth level of the grid with the level grid
void GridHistory::replaceNthLevelOfGrid(int index, vector<Grid*> level)
{
	gridHistoryLevels.at(index) = level;
}

//This will add level to the back of the gridHistoryLevels object
void GridHistory::addLevelToGrid(vector<Grid*> level)
{
	gridHistoryLevels.push_back(level);
}


//This method will return the most recent subgrids
vector<Grid*> GridHistory::getLastLevelOfGrid()
{
	return gridHistoryLevels.at(gridHistoryLevels.size() - 1);
}


//returns the last level of the grid
int GridHistory::getLevels()
{
	return gridHistoryLevels.size();
}

void GridHistory::setInitialGrid(Grid* initGrid)
{
	vector<Grid*> level0;
	level0.push_back(initGrid);
	gridHistoryLevels.push_back(level0);
}
