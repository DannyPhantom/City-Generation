#pragma once
#include "Building.h"
class BlockBuilding :
	public Building
{
protected:
	void generateBlock(glm::vec3 center, glm::vec3 size);
	void generateHorizontalPlane(glm::vec3 halfSize, float height, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals);
	void generateUVsForBlock(glm::vec3 size, std::vector<glm::vec2>& uvs);

public:
	BlockBuilding(glm::vec3 center, glm::vec3 size);
	~BlockBuilding();

	virtual void create() = 0;
};

