#pragma once

#include <random>

class Randomizer
{
private:
	static std::mt19937 rng;
	static std::uniform_int_distribution<> dist;
	static bool initialized;

	Randomizer();
	~Randomizer();

	static void initialize();
public:
	static float getRandomFloat(float min, float max);
	static int getRandomInt(int min, int max);
};

