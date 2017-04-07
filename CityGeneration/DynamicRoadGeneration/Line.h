#pragma once

#include "../Libraries/glm/glm.hpp"

class Line
{
public:
	Line();
	~Line();

	bool isPointNear(glm::vec2 point, glm::vec2 &result, bool &isValid);

	glm::vec2 start, end;
};

