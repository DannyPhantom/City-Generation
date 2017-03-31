#pragma once

#include "Building.h"
#include <vector>
#include "Libraries/glew/glew.h"

class SimpleBuilding :
	public Building
{
private:
	void generateBlock(glm::vec3 size);
	void generateSide(glm::vec3 firstCorner, glm::vec3 secondCorner, glm::vec3 thirdCorner, glm::vec3 fourthCorner,
		std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals);
	void generateHorizontalPlane(glm::vec3 halfSize, float height, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals);
	void generateUVs(glm::vec3 size, std::vector<glm::vec2>& uvs);
public:
	SimpleBuilding(glm::vec3 center, glm::vec3 size);
	~SimpleBuilding();

	void create();

};

