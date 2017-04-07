#include "Line.h"



Line::Line()
{
}


Line::~Line()
{
}

bool Line::isPointNear(glm::vec2 point, glm::vec2 &result, bool &isValid) {
	if (glm::dot(end - start, point - start) < 0 || glm::dot(start - end, point - end) < 0) {
		return false;
	}
	else {
		result = start + glm::dot(end - start, point - start) / glm::dot(end - start, end - start) * (end - start);
		isValid = glm::length(result - start) > 0.1f && glm::length(result - end) > 0.1f;
		if (glm::length(point - result) > 0.1f) {
			return false;
		}
		else {
			return true;
		}
	}
}