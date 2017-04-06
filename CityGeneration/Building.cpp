#include "Building.h"
#include <cmath>
#include <random>


Building::Building(glm::vec3 center, glm::vec3 size, float minHeight, float maxHeight):
	centerPosition(center), size(size), minHeight(minHeight), maxHeight(maxHeight)
{
	setPosition(center);
}


Building::~Building()
{
}

void Building::generateSide(glm::vec3 firstCorner, glm::vec3 secondCorner, glm::vec3 thirdCorner, glm::vec3 fourthCorner,
	std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals) {
	glm::vec3 normal = glm::cross(secondCorner - firstCorner, fourthCorner - firstCorner);
	vertices.push_back(firstCorner);			normals.push_back(normal);
	vertices.push_back(secondCorner);			normals.push_back(normal);
	vertices.push_back(thirdCorner);			normals.push_back(normal);

	vertices.push_back(firstCorner);			normals.push_back(normal);
	vertices.push_back(thirdCorner);			normals.push_back(normal);
	vertices.push_back(fourthCorner);			normals.push_back(normal);
}
