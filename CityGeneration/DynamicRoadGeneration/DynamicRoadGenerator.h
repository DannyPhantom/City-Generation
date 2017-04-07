#pragma once

#include <vector>
#include "../Libraries/glm/glm.hpp"
class Line;
class Square;

class DynamicRoadGenerator
{
private:
	std::vector<Line*> lines;
	std::vector<Square*> squares;

	glm::vec2 *point1 = NULL;
	bool point1Valid, point1Placed;
	glm::vec2 *point2 = NULL;
	bool point2Valid;

	void renderPoint(glm::vec2 pos);
public:
	DynamicRoadGenerator();
	~DynamicRoadGenerator();

	void draw();
	void processMouseMovement(float x, float y);
	void processMouseClick(float x, float y);
};

