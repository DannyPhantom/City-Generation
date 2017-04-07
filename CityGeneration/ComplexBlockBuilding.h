#pragma once

#include "BlockBuilding.h"

class ComplexBlockBuilding :
	public BlockBuilding
{
private:
	void scaleUVs(glm::vec3 scale);
public:
	ComplexBlockBuilding(glm::vec3 center, glm::vec3 size, float minHeight, float maxHeight);
	~ComplexBlockBuilding();

	void create();
};

