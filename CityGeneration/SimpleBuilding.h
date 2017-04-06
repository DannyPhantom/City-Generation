#pragma once

#include "BlockBuilding.h"
#include <vector>
#include "Libraries/glew/glew.h"

class SimpleBuilding :
	public BlockBuilding
{
private:
	void generateRoof(glm::vec3 halfSize, float heightStart, float heightEnd);
public:
	SimpleBuilding(glm::vec3 center, glm::vec3 size, float minHeight, float maxHeight);
	~SimpleBuilding();

	void create();

};

