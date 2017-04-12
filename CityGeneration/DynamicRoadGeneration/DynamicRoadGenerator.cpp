#include "DynamicRoadGenerator.h"
#include "Line.h"
#include "Square.h"
#include "../Libraries/glew/glew.h"
#include <iostream>
#include <algorithm>


#define TWO_PI 6.28318530718

DynamicRoadGenerator::DynamicRoadGenerator()
{
	float corner = 0.98f;
	//top
	Line *l1 = new Line();
	l1->start = glm::vec2(-corner, corner);
	l1->end = glm::vec2(corner, corner);

	//right
	Line *l2 = new Line();
	l2->start = glm::vec2(corner, corner);
	l2->end = glm::vec2(corner, -corner);

	//bottom
	Line *l3 = new Line();
	l3->start = glm::vec2(corner, -corner);
	l3->end = glm::vec2(-corner, -corner);

	//left
	Line *l4 = new Line();
	l4->start = glm::vec2(-corner, -corner);
	l4->end = glm::vec2(-corner, corner);

	Square *sq = new Square();
	sq->top = l1;
	sq->right = l2;
	sq->bottom = l3;
	sq->left = l4;

	squares.push_back(sq); 
	creationInProcess = true;
}


DynamicRoadGenerator::~DynamicRoadGenerator()
{
}

void DynamicRoadGenerator::renderPoint(glm::vec2 pos) {
	glBegin(GL_POLYGON);
	for (double i = 0; i < TWO_PI; i += TWO_PI / 15) {
		glVertex3f(pos.x + cos(i) * 0.03f, pos.y + sin(i) * 0.03f, 0.0);
	}
	glEnd();
}

void DynamicRoadGenerator::draw() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); 
	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glScalef(1.0, -1.0, 1.0f);

	for (Square *sq : squares) {
		for (Line *line : sq->getLines()) {
			glColor3f(1, 1, 0);
			glBegin(GL_LINES);
			glVertex3f(line->start.x, line->start.y, 0);
			glVertex3f(line->end.x, line->end.y, 0);
			glEnd();
		}
	}

	if (point1 != NULL) {
		renderPoint(*point1);
	}

	if (point2 != NULL) {
		renderPoint(*point2);
	}

	glColor3f(1, 1, 0);
	if (point1Placed && point2 != NULL) {
		glBegin(GL_LINES);
		glVertex3f((*point1).x, (*point1).y, 0);
		glVertex3f((*point2).x, (*point2).y, 0);
		glEnd();
	}
}

void DynamicRoadGenerator::processMouseMovement(float x, float y) {
	x *= 2;
	y *= 2;

	glm::vec2 result;
	Line *closestLine = findClosestLine(glm::vec2(x, y));
	if (!point1Placed) {
		if (closestLine->isPointNear(glm::vec2(x, y), result)) {
			if (point1 != NULL) {
				delete point1;
				point1 = NULL;
			}
			point1 = new glm::vec2(result);
		}
	} else {
		if (point2 != NULL) {
			delete point2;
			point2 = NULL;
		}
		if (closestLine->isPointNear(glm::vec2(x, y), result)) {	
			point2 = new glm::vec2(result);
		}
		else {
			point2 = new glm::vec2(x, y);
		}

		if (findClosestLine(*point1)->isHorizontal()) {
			point2->x = point1->x;
		}
		else {
			point2->y = point1->y;
		}
	}
}

void DynamicRoadGenerator::processMouseClick(float x, float y) {
	x *= 2;
	y *= 2;

	glm::vec2 result;
	Line *closestLine = findClosestLine(glm::vec2(x, y));
	if (!point1Placed) {
		if (closestLine->isPointNear(glm::vec2(x, y), result)) {
			if (point1 != NULL) {
				delete point1;
				point1 = NULL;
			}
			point1 = new glm::vec2(result);
			point1Placed = true;
			point1Line = closestLine;
		}
	}
	else {
		if (point2 != NULL) {
			delete point2;
			point2 = NULL;
		}
		if (closestLine->isPointNear(glm::vec2(x, y), result)) {
			point2 = new glm::vec2(result);
			if (findClosestLine(*point1)->isHorizontal()) {
				point2->x = point1->x;
			}
			else {
				point2->y = point1->y;
			}
			Line *newLine = new Line();
			newLine->start = *point1;
			newLine->end = *point2;

			Square *sq = findSquareByTwoPoints(*point1, *point2);
			if (sq != NULL) {
				std::pair<Square*, Square*> newSquares = sq->splitByLine(newLine);
				squares.push_back(newSquares.first); squares.push_back(newSquares.second);
				removeSquare(sq);
			}

			delete point1; point1 = NULL;
			delete point2; point2 = NULL;
			point1Placed = false;
		}
	}
}

Line *DynamicRoadGenerator::findClosestLine(glm::vec2 point) {
	Line *closest = squares.front()->getLines().front();
	float distance = 100000;
	for (Square *sq : squares) {
		for (Line *l : sq->getLines()) {
			if (glm::dot(point - l->start, l->end - l->start) < 0
				|| glm::dot(point - l->end, l->start - l->end) < 0) {
				continue;
			}
			else {
				glm::vec2 lineVec = l->end - l->start;
				glm::vec2 pointOnLine = lineVec * glm::dot(lineVec, point - l->start) / glm::dot(lineVec, lineVec) + l->start;
				float dist = glm::length(pointOnLine - point);
				if (dist < distance) {
					distance = dist;
					closest = l;
				}
			}
		}
	}
	return closest;
}

Square *DynamicRoadGenerator::findSquareByTwoLines(Line *l1, Line *l2) {
	for (Square *sq : squares) {
		if (sq->lineBelongsTo(l1) && sq->lineBelongsTo(l2)) {
			return sq;
		}
	}

	return NULL;
}

void DynamicRoadGenerator::removeSquare(Square *sq) {
	squares.erase(std::remove(squares.begin(), squares.end(), sq), squares.end());
}

Square *DynamicRoadGenerator::findSquareByTwoPoints(glm::vec2 point1, glm::vec2 point2) {
	for (Square *sq : squares) {
		if (sq->pointBelongsTo(point1) && sq->pointBelongsTo(point2)) {
			return sq;
		}
	}

	return NULL;
}