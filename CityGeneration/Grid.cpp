/*
 * Grid.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: bemayer
 */

#include "Grid.h"
#include <cmath>
#include <iostream>
#include "Libraries/glm/glm.hpp"
#include "Randomizer.h"

vector<Road*> Grid::roads;

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
	double firstRand = Randomizer::getRandomFloat(0.0f, 1.0f);
	vector<Grid*> newGrids;
	int numAttempts = 0;
	double roadWidth = 10.0f; //TODO REMOVE FOR PRODUCTION

	while (newGrids.size() == 0 && numAttempts++ < 10) {
		if (firstRand >= 0.5)
		{
			//split the grid along the X axis
			newGrids = splitGrid(roadWidth, Randomizer::getRandomFloat(0.40f, w * 0.70f), Axis::X_AXIS);
		} else {
			//split the grid along the Y axis
			newGrids = splitGrid(roadWidth, Randomizer::getRandomFloat(0.40f, h * 0.70f), Axis::Y_AXIS);
		}
		roadWidth *= Randomizer::getRandomFloat(0.5, 0.9);
	}

	return newGrids;
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
vector<Grid*> Grid::splitGrid(double roadWidth, double splitLength, Axis axis)
{


	vector<Grid*> newGrids;

	if (roadWidth > splitLength || roadWidth > w - splitLength || roadWidth > h - splitLength) {
		return newGrids;
	}

	if (axis == Axis::X_AXIS)
	{
		//NOTE: roadWidth is undefined. Set up a constant or add a variable to it
		Road* splittingRoad = new Road(h, roadWidth, originX + splitLength, originY, 1);

		//split along the X Axis
		Grid* grid1 = new Grid(originX, originY, (splitLength-(roadWidth/2.0f)), h);
		Grid* grid2 = new Grid(originX + (splitLength+(roadWidth/2.0f)), originY, w - splitLength-(roadWidth/2.0f), h);

		glm::vec2 center1 = glm::vec2(grid1->originX + grid1->w/2.0f, grid1->originY + grid1->h/2.0f);
		glm::vec2 size1 = glm::vec2(grid1->w, grid1->h);

		std::cout << "Pos : " << center1.x << " " << center1.y << std::endl;
		std::cout << "Size : " << size1.x << " " << size1.y << std::endl;

		glm::vec2 center2 = glm::vec2(grid2->originX + grid2->w/2.0f, grid2->originY + grid2->h/2.0f);
		glm::vec2 size2 = glm::vec2(grid2->w, grid2->h);

		std::cout << "Pos : " << center2.x << " " << center2.y << std::endl;
		std::cout << "Size : " << size2.x << " " << size2.y << std::endl << std::endl;

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

		Grid* grid1 = new Grid(originX, originY, w, (splitLength-(roadWidth/2.0f)));
		Grid* grid2 = new Grid(originX, originY + (splitLength+(roadWidth/2.0f)), w, h - (splitLength+(roadWidth/2.0f)));

		glm::vec2 center1 = glm::vec2(grid1->originX + grid1->w/2.0f, grid1->originY + grid1->h/2.0f);
		glm::vec2 size1 = glm::vec2(grid1->w, grid1->h);

		std::cout << "Pos : " << center1.x << " " << center1.y << std::endl;
		std::cout << "Size : " << size1.x << " " << size1.y << std::endl;

		glm::vec2 center2 = glm::vec2(grid2->originX + grid2->w/2.0f, grid2->originY + grid2->h/2.0f);
		glm::vec2 size2 = glm::vec2(grid2->w, grid2->h);

		std::cout << "Pos : " << center2.x << " " << center2.y << std::endl;
		std::cout << "Size : " << size2.x << " " << size2.y << std::endl << std::endl;

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
