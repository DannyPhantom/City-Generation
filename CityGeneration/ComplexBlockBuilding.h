#pragma once

#include "BlockBuilding.h"

class ComplexBlockBuilding :
	public BlockBuilding
{
private:
public:
	ComplexBlockBuilding(glm::vec3 center, glm::vec3 size);
	~ComplexBlockBuilding();

	void create();
};

