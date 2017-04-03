#pragma once

#include "Libraries/glm/glm.hpp"
#include "SceneObject.h"

class Building : public SceneObject
{
protected:
	glm::vec3 centerPosition;
	glm::vec3 size;

	const float minHeight = 100;
	const float maxHeight = 350;

	const glm::vec2 numOfWindowsPerMeter = glm::vec2(0.4, 0.2);

	void generateSide(glm::vec3 firstCorner, glm::vec3 secondCorner, glm::vec3 thirdCorner, glm::vec3 fourthCorner,
		std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals);
public:
	Building(glm::vec3 center, glm::vec3 size);
	~Building();

	virtual void create() = 0;
};

