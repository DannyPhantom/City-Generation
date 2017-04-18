#pragma once
#include "SceneObject.h"

class Plane : public SceneObject
{
private:
	void create(glm::vec3 start, glm::vec3 end, glm::vec3 color);
public:
	Plane(glm::vec3 start, glm::vec3 end, glm::vec3 color);
	~Plane();
};

