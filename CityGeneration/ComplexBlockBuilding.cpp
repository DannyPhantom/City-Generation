#include "ComplexBlockBuilding.h"
#include "Randomizer.h"
#include "Scene.h"
#include <algorithm>


ComplexBlockBuilding::ComplexBlockBuilding(glm::vec3 center, glm::vec3 size) : BlockBuilding(center, size)
{
	create();
}


ComplexBlockBuilding::~ComplexBlockBuilding()
{
}

void ComplexBlockBuilding::create() {
	glm::vec3 blockSize = size;
	int numOfBlocks = Randomizer::getRandomInt(3, 12);
	float blockHeight = Randomizer::getRandomFloat(minHeight, maxHeight);
	float buildingHeight = blockHeight;
	blockSize.y = buildingHeight;
	generateBlock(glm::vec3(0, 0, 0), blockSize);

	for (int i = 0; i < numOfBlocks && blockHeight > buildingHeight * 0.3f; i++) {
		blockSize = glm::vec3(Randomizer::getRandomFloat(0.2, 0.8) * size.x, 0.0f, Randomizer::getRandomFloat(0.2, 0.8) * size.z);
		blockHeight -= buildingHeight * Randomizer::getRandomFloat(0.05f, 0.3f);
		blockSize.y = blockHeight;

		glm::vec3 offset = glm::vec3(Randomizer::getRandomFloat(-0.4f, 0.4f) * size.x, 0, Randomizer::getRandomFloat(-0.4f, 0.4f) * size.z);

		generateBlock(offset, blockSize);
	}

	setupVBOs();
	setupVAOs();
}
