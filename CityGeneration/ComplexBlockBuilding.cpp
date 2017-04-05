#include "ComplexBlockBuilding.h"
#include "Randomizer.h"
#include "Scene.h"
#include <algorithm>
#include <math.h>
#include "Mesh.h"

#include "BoundingBox.h"


ComplexBlockBuilding::ComplexBlockBuilding(glm::vec3 center, glm::vec3 size) : BlockBuilding(center, size)
{
	create();
}


ComplexBlockBuilding::~ComplexBlockBuilding()
{
}

/*void ComplexBlockBuilding::create() {
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
}*/

void ComplexBlockBuilding::create() {
	glm::vec3 blockSize = size;
	int numOfBlocks = Randomizer::getRandomInt(3, 12);
	float blockHeight = Randomizer::getRandomFloat(minHeight, maxHeight);
	float buildingHeight = blockHeight;
	blockSize.y = buildingHeight;
	generateBlock(glm::vec3(0, 0, 0), blockSize);

	BoundingBox boundingBox(-size / 2.0f, size / 2.0f);

	for (int i = 0; i < numOfBlocks && blockHeight > buildingHeight * 0.2f; i++) {
		glm::vec3 offset = glm::vec3(Randomizer::getRandomFloat(-0.25f, 0.25f) * size.x, 0, Randomizer::getRandomFloat(-0.25f, 0.25f) * size.z);
		
		float targetWidthX = 0;
		float targetWidthZ = 0;

		//going to negative x
		if (offset.x > 0) {
			targetWidthX = Randomizer::getRandomFloat(1.2f, 1.5f) * (offset.x - boundingBox.getMin().x);
		}
		//going to positive x
		else {
			targetWidthX = Randomizer::getRandomFloat(1.2f, 1.5f) * (boundingBox.getMax().x - offset.x);
		}

		//going to negative z
		if (offset.z > 0) {
			targetWidthZ = Randomizer::getRandomFloat(1.2f, 1.5f) * (offset.z - boundingBox.getMin().z);
		}
		//going to positive z
		else {
			targetWidthZ = Randomizer::getRandomFloat(1.2f, 1.5f) * (boundingBox.getMax().z - offset.z);
		}

		//reduce one of the widths at random. 10% for each axis
		float reduceWidth = Randomizer::getRandomFloat(0.0f, 1.0f);
		if (reduceWidth < 0.1f) {
			targetWidthX *= Randomizer::getRandomFloat(0.1f, 0.6f);
		}
		else if (reduceWidth < 0.2f) {
			targetWidthZ *= Randomizer::getRandomFloat(0.1f, 0.6f);
		}

		//now calculate the actual offset
		int xDir = -signbit(offset.x);
		int zDir = -signbit(offset.z);
		offset += glm::vec3(xDir * targetWidthX / 2.0f, 0, zDir * targetWidthZ / 2.0f);

		//and block size
		blockHeight *= Randomizer::getRandomFloat(0.6f, 0.9f);
		blockSize = glm::vec3(targetWidthX, blockHeight, targetWidthZ);

		generateBlock(offset, blockSize);

		//update boundingBox
		boundingBox.addCoord(offset + blockSize / 2.0f);
		boundingBox.addCoord(offset - blockSize / 2.0f);
	}

	setupVBOs();
	setupVAOs();

	//finally, centerize and scale the building
	setPosition(position - (boundingBox.getMax() + boundingBox.getMin()) / 2.0f);
	glm::vec3 scale = 1.0f / (boundingBox.getMax() - boundingBox.getMin());
	scale.x *= size.x * 0.4f;
	scale.z *= size.z * 0.4f;
	scale.y = 1;
	setScale(scale);
}
