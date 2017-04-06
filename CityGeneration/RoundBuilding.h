#pragma once
#include "Building.h"

class RoundBuilding :
	public Building
{
private:
	void generateUVs(glm::vec3 size, std::vector<glm::vec2>& uvs);
	std::vector<glm::vec3> getCircle();
	void generateUVs(std::vector<glm::vec3> circle, float buildingHeight, std::vector<glm::vec2>& uvs);
	void smoothNormals(std::vector<glm::vec3>& normals);
	void generateRoof(std::vector<glm::vec3> circle, float buildingHeight, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs);
public:
	RoundBuilding(glm::vec3 center, glm::vec3 size, float minHeight, float maxHeight);
	~RoundBuilding();

	void create();
};

