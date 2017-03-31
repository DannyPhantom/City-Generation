/*
 * GridFactory.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: bemayer
 */

#include "GridFactory.h"

GridFactory::GridFactory() {
	// TODO Auto-generated constructor stub

}

GridFactory::~GridFactory() {
	// TODO Auto-generated destructor stub
}

GridHistory GridFactory::generateDefaultGrid()
{

	//just the initial values for the defautlt grid
	int originX = 0;
	int originY = 0;

	double w = 1000.0;	//These values will likely need some change
	double h = 1000.0;	//These values will likely need some change

	int levels = 2;		//Just in case

	Grid* initGrid = new Grid(originX, originY, w, h);
	GridHistory gridHistory = GridHistory();

	gridHistory.setInitialGrid(initGrid);


	vector<Grid*> level1 =	initGrid->splitGrid();

	gridHistory.addLevelToGrid(level1);

	vector<Grid*> level2;

	for (auto level: level1)
	{
		vector<Grid*> grid = level->splitGrid();

		//The grid variable will basically
		//always have at least two elements in it

		level2.push_back(grid.at(0));
		level2.push_back(grid.at(1));
	}


	gridHistory.addLevelToGrid(level2);
	return gridHistory;

}

GridHistory GridFactory::generateCustomSubGrids(Grid* initGrid, int numLevels)
{
	GridHistory gridHistory = GridHistory();
	gridHistory.setInitialGrid(initGrid);

	vector<Grid*> previousLevel;
	vector<Grid*> currentLevel;

	previousLevel.push_back(initGrid);

	for (int i = 1; i < numLevels; i++)
	{
			for (auto level : previousLevel)
			{
				vector<Grid*> grids = level->splitGrid();
				if (grids.size() > 0) {
					currentLevel.push_back(grids.at(0));
					currentLevel.push_back(grids.at(1));
				}
			}

			gridHistory.addLevelToGrid(currentLevel);
			previousLevel = currentLevel;
			currentLevel.clear();

	}

	return gridHistory;

}
