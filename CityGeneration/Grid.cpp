/*
 * Grid.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: bemayer
 */

#include "Grid.h"

Grid::Grid(double _originX, double _originY, double _w, double _h) {
	// TODO Auto-generated constructor stub
	originX = _originX;
	originY = _originY;
	w = _w;
	h = _h;

}

Grid::~Grid() {
	// TODO Auto-generated destructor stub
}

double Grid::getH() const {
	return h;
}

void Grid::setH(double h) {
	this->h = h;
}

double Grid::getOriginX() const {
	return originX;
}

void Grid::setOriginX(double originX) {
	this->originX = originX;
}

double Grid::getOriginY() const {
	return originY;
}

void Grid::setOriginY(double originY) {
	this->originY = originY;
}

double Grid::getW() const {
	return w;
}

void Grid::setW(double w) {
	this->w = w;
}

vector<Grid*> Grid::splitGrid()
{
	int firstRand = generateRandomNumber(1, 0);
	if (firstRand == 1)
	{
		//split the grid along the X axis
		return splitGrid(generateRandomNumber(w * 0.90, 0.0), Axis::X_AXIS);
	} else {
		//split the grid along the Y axis
		return splitGrid(generateRandomNumber(h * 0.90, 0.0), Axis::Y_AXIS);
	}
}


//This method will split the current grid along the x
//or the y axis based on the parameter of splitLength

/* X split
 *
 *
 * ------
 * | |  |
 * | |  |
 * ------
 *
 * Y split
 *
 * ------
 * |    |
 * |____|
 * |    |
 * ------
 */
vector<Grid*> Grid::splitGrid(double splitLength, Axis axis)
{
	if (axis == Axis::X_AXIS)
	{
		//split along the X Axis
		Grid* grid1 = new Grid(originX, originY, w - splitLength, h);
		Grid* grid2 = new Grid(originX + splitLength, originY,splitLength, h);

		vector<Grid*> newGrids;
		newGrids.push_back(grid1);
		newGrids.push_back(grid2);

		return newGrids;
	} else if (axis == Axis::Y_AXIS)
	{
		//split along the Y Axis

		Grid* grid1 = new Grid(originX, originY, w, h - splitLength);
		Grid* grid2 = new Grid(originX, originY + splitLength, w, h - splitLength);

		vector<Grid*> newGrids;
		newGrids.push_back(grid1);
		newGrids.push_back(grid2);

		return newGrids;

	} else
	{
		vector<Grid*> aGrid;
		aGrid.push_back(new Grid(originX, originY, w, h));	//just an easy error prevention case
		return aGrid;
	}

}

int Grid::generateRandomNumber(int max, int min)
{
	return rand() % max + min;
}

double Grid::generateRandomNumber(double max, double min)
{
	return ((float)rand() / RAND_MAX) * (max - min) + min;
}
