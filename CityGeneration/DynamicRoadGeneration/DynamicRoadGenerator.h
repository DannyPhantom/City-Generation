#pragma once

#include <vector>
#include "../Libraries/glm/glm.hpp"
class Line;
class Square;

class DynamicRoadGenerator
{
private:
	std::vector<Square *> deletedSquares;
	std::vector<Square*> squares;

	Line *point1Line = NULL;
	glm::vec2 *point1 = NULL;
	bool point1Placed;
	glm::vec2 *point2 = NULL;

	bool creationInProcess;

	void renderPoint(glm::vec2 pos);
public:
	DynamicRoadGenerator();
	~DynamicRoadGenerator();

	void draw();
	void processUndo();
	void processMouseMovement(float x, float y);
	void processMouseClick(float x, float y);
	Line *findClosestLine(glm::vec2 point);
	Square *findSquareByTwoLines(Line *l1, Line *l2);
	Square *findSquareByTwoPoints(glm::vec2 point1, glm::vec2 point2);
	void removeSquare(Square *sq);

	void stopCreating() { creationInProcess = false; }
	bool isDone() { return !creationInProcess; }



	std::vector<Square *> getSquares() { return squares; }
};

