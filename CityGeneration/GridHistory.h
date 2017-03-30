/*
 * GridHistory.h
 *
 *  Created on: Mar 29, 2017
 *      Author: bemayer
 */

#ifndef CITYGENERATION_GRIDHISTORY_H_
#define CITYGENERATION_GRIDHISTORY_H_

#include <vector>
#include "Grid.h"

using namespace std;

class GridHistory {
public:
	GridHistory();
	virtual ~GridHistory();

	Grid* getInitialGrid();
	void setInitialGrid(Grid* initGrid);


	vector<Grid*> getNthLevelOfGrid(int n);
	void replaceNthLevelOfGrid(int index, vector<Grid*> level);


	void addLevelToGrid(vector<Grid*> level);
	vector<Grid*> getLastLevelOfGrid();

	int getLevels();





private:
	vector<vector<Grid*>> gridHistoryLevels;
};

#endif /* CITYGENERATION_GRIDHISTORY_H_ */
