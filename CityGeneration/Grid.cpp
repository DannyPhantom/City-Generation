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

	const double roadWidth = 5.0f; //TODO REMOVE FOR PRODUCTION
	if (axis == Axis::X_AXIS)
	{
		//NOTE: roadWidth is undefined. Set up a constant or add a variable to it
		Road* splittingRoad = new Road(h, roadWidth, originX + splitLength, originY, 1);

		//split along the X Axis
		Grid* grid1 = new Grid(originX, originY, w - (splitLength+(roadWidth/2.0f)), h);
		Grid* grid2 = new Grid(originX + (splitLength+(roadWidth/2.0f)), originY,splitLength-(roadWidth/2.0f), h);

		vector<Grid*> newGrids;
		newGrids.push_back(grid1);
		newGrids.push_back(grid2);

		//do something with splittingRoad here

		addRoad(splittingRoad);

		return newGrids;
	} else if (axis == Axis::Y_AXIS)
	{
		//NOTE: roadWidth is undefined. Set up a constant or add a variable to it
		Road* splittingRoad = new Road(w, roadWidth, originX, originY + splitLength, 2);

		//split along the Y Axis

		Grid* grid1 = new Grid(originX, originY, w, h - (splitLength+(roadWidth/2.0f)));
		Grid* grid2 = new Grid(originX, originY + (splitLength+(roadWidth/2.0f)), w, h - (splitLength+(roadWidth/2.0f)));

		vector<Grid*> newGrids;
		newGrids.push_back(grid1);
		newGrids.push_back(grid2);

		//do something with splittingRoad here

		addRoad(splittingRoad);

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


//basic idea is to check for duplicates.
//If the list lacks duplicates of road then
//road is added to the list
void Grid::addRoad(Road* road)
{
	bool containsDuplicate = false;
	for (auto aRoad:roads)
	{
		bool statement1 = (aRoad->direction == road->direction);
		bool statement2 = (aRoad->origin_x == road->origin_x);
		bool statement3 = (aRoad->origin_y == road->origin_y);
		bool statement4 = (aRoad->width == road->width);
		bool statement5 = (aRoad->length == road->length);

		bool result = (statement1 & statement2) & statement3 & statement4 & statement5;

		if (result)
		{
			return;	//means a duplicate was found
		}
	}
	roads.push_back(road);	//getting here means no roads were found
}

vector<Road*> Grid::getRoads() {
	return roads;
}

double Grid::generateRandomNumber(double max, double min)
{
	return (int) (rand() % max + min);
}
