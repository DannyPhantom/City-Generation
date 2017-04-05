#pragma once

#include "Libraries\glm\glm.hpp"

class BoundingBox
{
private:
	glm::vec3 min, max;
public:
	BoundingBox(glm::vec3 min, glm::vec3 max);
	~BoundingBox();

	void addCoord(glm::vec3 c);

	glm::vec3 getMin() { return min; }
	glm::vec3 getMax() { return max; }
};

