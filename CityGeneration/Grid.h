/*
 * Grid.h
 *
 *  Created on: Mar 29, 2017
 *      Author: bemayer
 */

#ifndef CITYGENERATION_GRID_H_
#define CITYGENERATION_GRID_H_

#include <cstdlib>
#include <vector>
#include "Road.h"

enum Axis
{
	X_AXIS,
	Y_AXIS
};


using namespace std;
class Grid {
public:
	Grid(double _originX, double _originY, double _w, double _h);
	virtual ~Grid();

	vector<Grid*> splitGrid();

	vector<Grid*> splitGrid(double roadWidth, double splitLength, Axis axis);


	double getH() const;
	void setH(double h);
	double getOriginX() const;
	void setOriginX(double originX);
	double getOriginY() const;
	void setOriginY(double originY);
	double getW() const;
	void setW(double w);

	static void addRoad(Road* road);
	static vector<Road*> getRoads();
	static vector<Road*> roads;

private:




	double originX;
	double originY;

	double w,h;
};

#endif /* CITYGENERATION_GRID_H_ */
