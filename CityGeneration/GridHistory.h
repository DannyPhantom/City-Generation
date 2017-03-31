/*
 * GridHistory.h
 *
 *  Created on: Mar 29, 2017
 *      Author: bemayer
 *      Edited by: Marc DeSorcy
 */

#ifndef CITYGENERATION_GRIDHISTORY_H_
#define CITYGENERATION_GRIDHISTORY_H_

#include <vector>
#include "Grid.h"

using namespace std;

struct LandPlot{
	glm::vec2 bot_left;
	glm::vec2 bot_right;
	glm::vec2 top_left;
	glm::vec2 top_right;
};

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


	//The below method obtains land plots for Igor's purposes
	vector<LandPlot> getBuildingSpots();



private:
	vector<vector<Grid*>> gridHistoryLevels;
};

#endif /* CITYGENERATION_GRIDHISTORY_H_ */
