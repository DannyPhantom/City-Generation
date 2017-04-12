#include "Line.h"



Line::Line()
{
}


Line::~Line()
{
}

bool Line::isPointNear(glm::vec2 point, glm::vec2 &result) {
	if (glm::dot(end - start, point - start) < 0 || glm::dot(start - end, point - end) < 0) {
		return false;
	}
	else {
		result = start + glm::dot(end - start, point - start) / glm::dot(end - start, end - start) * (end - start);
		if (glm::length(point - result) > 0.1f) {
			return false;
		}
		else {
			return true;
		}
	}
}

bool Line::pointBelongsTo(glm::vec2 point) {
	glm::vec2 result;
	if (isPointNear(point, result)) {
		if (glm::length(point - result) < 0.001f) {
			return true;
		}
	}
	return false;
}

bool Line::isHorizontal() {
	return start.y == end.y;
}

bool Line::isVertical() {
	return start.x == end.x;
}

glm::vec2* Line::getLeft() {
	if (start.x < end.x) return &start;
	return &end;
}

glm::vec2* Line::getTop() {
	if (start.y > end.y) return &start;
	return &end;
}

glm::vec2* Line::getRight() {
	if (start.x > end.x) return &start;
	return &end;
}

glm::vec2* Line::getBot() {
	if (start.y < end.y) return &start;
	return &end;
}
