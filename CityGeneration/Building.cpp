#include "Building.h"
#include <cmath>
#include <random>


Building::Building(glm::vec3 center, glm::vec3 size): centerPosition(center), size(size)
{
	rng = std::mt19937(std::random_device{}());
	dist = std::uniform_int_distribution<>(0, RAND_MAX);
}


Building::~Building()
{
}

float Building::getRandomFloat(float min, float max) {
	return ((float)dist(rng) / RAND_MAX) * (max - min) + min;
}

int Building::getRandomInt(int min, int max) {
	return (int) std::round(getRandomFloat(min, max));
}