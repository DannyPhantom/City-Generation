#pragma once

#include "../Libraries/glm/glm.hpp"

class Line
{
public:
	Line();
	~Line();

	bool isPointNear(glm::vec2 point, glm::vec2 &result);
	bool pointBelongsTo(glm::vec2 point);

	bool isHorizontal();
	bool isVertical();
	glm::vec2* getLeft();
	glm::vec2* getTop();
	glm::vec2* getRight();
	glm::vec2* getBot();

	glm::vec2 start, end;
};

