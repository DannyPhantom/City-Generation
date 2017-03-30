/*
 * GridFactory.h
 *
 *  Created on: Mar 29, 2017
 *      Author: bemayer
 */

#ifndef CITYGENERATION_GRIDFACTORY_H_
#define CITYGENERATION_GRIDFACTORY_H_

#include "GridHistory.h"
#include "Grid.h"

class GridFactory {
public:
	GridFactory();
	virtual ~GridFactory();

	static GridHistory generateDefaultGrid();
	static GridHistory generateCustomSubGrids(Grid* initGrid, int numLevels);
};

#endif /* CITYGENERATION_GRIDFACTORY_H_ */
