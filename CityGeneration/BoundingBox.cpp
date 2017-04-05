#include "BoundingBox.h"



BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max) : min(min), max(max)
{
}


BoundingBox::~BoundingBox()
{
}

void BoundingBox::addCoord(glm::vec3 c) {
	if (c.x < min.x) {
		min.x = c.x;
	}

	if (c.y < min.y) {
		min.y = c.y;
	}

	if (c.z < min.z) {
		min.z = c.z;
	}

	if (c.x > max.x) {
		max.x = c.x;
	}

	if (c.y > max.y) {
		max.y = c.y;
	}

	if (c.z > max.z) {
		max.z = c.z;
	}
}
