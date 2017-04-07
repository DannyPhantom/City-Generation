#include "DynamicRoadGenerator.h"
#include "Line.h"
#include "Square.h"
#include "../Libraries/glew/glew.h"


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

	lines.push_back(l1);
	lines.push_back(l2);
	lines.push_back(l3);
	lines.push_back(l4);

	Square *sq = new Square();
	sq->addLine(l1);
	sq->addLine(l2);
	sq->addLine(l3);
	sq->addLine(l4);

	squares.push_back(sq);
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

	for (Line *line : lines) {
		glColor3f(1, 1, 0);
		glBegin(GL_LINES);
		glVertex3f(line->start.x, line->start.y, 0);
		glVertex3f(line->end.x, line->end.y, 0);
		glEnd();
	}

	glColor3f(1, 1, 0);
	if (point1 != NULL) {
		if (!point1Valid) { 
			glColor3f(1, 0, 0);
		}
		renderPoint(*point1);
	}

	glColor3f(1, 1, 0);
	if (point2 != NULL) {
		if (!point2Valid) {
			glColor3f(1, 0, 0);
		}
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
	y *= -2;

	glm::vec2 result;
	bool isValid;
	for (Line *l : lines) {
		if (l->isPointNear(glm::vec2(x, y), result, isValid)) {
			if (!point1Placed) {
				point1 = new glm::vec2(result);
				point1Valid = isValid;
				point1Placed = false;
			}
			else if (point1Placed && point2 == NULL) {
				point2 = new glm::vec2(result);
				point2Valid = isValid;
			}
		}
	}
}

void DynamicRoadGenerator::processMouseClick(float x, float y) {
	x *= 2;
	y *= -2;

	glm::vec2 result;
	bool isValid;
	for (Line *l : lines) {
		if (l->isPointNear(glm::vec2(x, y), result, isValid) && isValid) {
			if (point1 == NULL) {
				point1 = new glm::vec2(result);
				point1Placed = true;
			}
			else if (point1Placed && point2 == NULL) {
				point2 = new glm::vec2(result);
				Line *l = new Line();
				l->start = *point1;
				l->end = *point2;
				delete point1;
				delete point2;
				point1 = NULL; point2 = NULL;
				point1Placed = false;
			}
		}
	}
}
