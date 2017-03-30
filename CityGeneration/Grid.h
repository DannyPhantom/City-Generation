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

	vector<Grid*> splitGrid(double splitLength, Axis axis);


	double getH() const;
	void setH(double h);
	double getOriginX() const;
	void setOriginX(double originX);
	double getOriginY() const;
	void setOriginY(double originY);
	double getW() const;
	void setW(double w);

private:

	double originX;
	double originY;

	double w,h;

	int generateRandomNumber(int max, int min);
};

#endif /* CITYGENERATION_GRID_H_ */
