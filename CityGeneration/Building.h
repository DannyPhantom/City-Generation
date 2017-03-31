#pragma once

#include "Libraries\glm\glm.hpp"
#include "SceneObject.h"
#include <random>

class Building : public SceneObject
{
private:
	std::mt19937 rng;
	std::uniform_int_distribution<> dist;
protected:
	glm::vec3 centerPosition;
	glm::vec3 size;

	const float minHeight = 50;
	const float maxHeight = 150;

	const glm::vec2 numOfWindowsPerMeter = glm::vec2(3, 1);
public:
	Building(glm::vec3 center, glm::vec3 size);
	~Building();

	virtual void create() = 0;

	float getRandomFloat(float min, float max);
	int getRandomInt(int min, int max);
};

