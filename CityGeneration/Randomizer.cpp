#include "Randomizer.h"

std::mt19937 Randomizer::rng;
std::uniform_int_distribution<> Randomizer::dist;
bool Randomizer::initialized = false;


Randomizer::Randomizer()
{
	rng = std::mt19937(std::random_device{}());
	dist = std::uniform_int_distribution<>(0, RAND_MAX);
}


Randomizer::~Randomizer()
{
}

float Randomizer::getRandomFloat(float min, float max) {
	initialize();
	return ((float)dist(rng) / RAND_MAX) * (max - min) + min;
}

int Randomizer::getRandomInt(int min, int max) {
	initialize();
	return (int)std::round(getRandomFloat(min, max));
}

void Randomizer::initialize() {
	if (!initialized) {
		rng = std::mt19937(std::random_device{}());
		dist = std::uniform_int_distribution<>(0, RAND_MAX);
		initialized = true;
	}
}
