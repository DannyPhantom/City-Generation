#include "SimpleBuilding.h"
#include "WindowsTextureGenerator.h"
#include "Scene.h"

SimpleBuilding::SimpleBuilding(glm::vec3 center, glm::vec3 size) : Building(center, size)
{
	create();
}


SimpleBuilding::~SimpleBuilding()
{
}

void SimpleBuilding::create() {
	glm::vec3 blockSize = size;
	int numOfBlocks = getRandomInt(3, 7);
	glm::vec3 minSize = 0.25f * size;
	float blockHeight = 0.8 * minHeight;

	for (int i = 0; i < numOfBlocks && blockSize.x > minSize.x && blockSize.z > minSize.z && blockHeight <= maxHeight; i++) {
		blockSize -= blockSize * getRandomFloat(0.05, 0.15);
		blockHeight += (maxHeight - minHeight) * getRandomFloat(0.05, 0.15);
		blockSize.y = blockHeight;
		generateBlock(blockSize);
	}

	setupVBOs();
	setupVAOs();
}

void SimpleBuilding::generateBlock(glm::vec3 size) {
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec4> colors;
	std::vector<GLuint> indices;

	//half size
	glm::vec3 hSize = size / 2.0f;

	//front
	generateSide(glm::vec3(-hSize.x, 0, -hSize.z), glm::vec3(hSize.x, 0, -hSize.z), glm::vec3(hSize.x, size.y, -hSize.z), glm::vec3(-hSize.x, size.y, -hSize.z), vertices, normals);
	//left
	generateSide(glm::vec3(-hSize.x, 0, hSize.z), glm::vec3(-hSize.x, 0, -hSize.z), glm::vec3(-hSize.x, size.y, -hSize.z), glm::vec3(-hSize.x, size.y, hSize.z), vertices, normals);
	//back
	generateSide(glm::vec3(hSize.x, 0, hSize.z), glm::vec3(-hSize.x, 0, hSize.z), glm::vec3(-hSize.x, size.y, hSize.z), glm::vec3(hSize.x, size.y, hSize.z), vertices, normals);
	//right
	generateSide(glm::vec3(hSize.x, 0, -hSize.z), glm::vec3(hSize.x, 0, hSize.z), glm::vec3(hSize.x, size.y, hSize.z), glm::vec3(hSize.x, size.y, -hSize.z), vertices, normals);
	//top
	generateHorizontalPlane(hSize, size.y, vertices, normals);
	//uvs
	generateUVs(size, uvs);


	for (int i = 0; i < vertices.size(); i++) {
		colors.push_back(glm::vec4(1, 1, 1, 1));
		indices.push_back(i);
	}

	Mesh *m = new Mesh(vertices, uvs, colors, normals, indices, Scene::windowsTexture, 10);
	addMesh(m);
}

void SimpleBuilding::generateSide(glm::vec3 firstCorner, glm::vec3 secondCorner, glm::vec3 thirdCorner, glm::vec3 fourthCorner,
	std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals) {
	glm::vec3 normal = glm::cross(secondCorner - firstCorner, fourthCorner - firstCorner);
	vertices.push_back(firstCorner);			normals.push_back(normal);
	vertices.push_back(secondCorner);			normals.push_back(normal);
	vertices.push_back(thirdCorner);			normals.push_back(normal);

	vertices.push_back(firstCorner);			normals.push_back(normal);
	vertices.push_back(thirdCorner);			normals.push_back(normal);
	vertices.push_back(fourthCorner);			normals.push_back(normal);
}


void SimpleBuilding::generateHorizontalPlane(glm::vec3 halfSize, float height, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals) {
	vertices.push_back(glm::vec3(-halfSize.x, height, -halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
	vertices.push_back(glm::vec3(halfSize.x, height, -halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
	vertices.push_back(glm::vec3(halfSize.x, height, halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));

	vertices.push_back(glm::vec3(-halfSize.x, height, -halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
	vertices.push_back(glm::vec3(halfSize.x, height, halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
	vertices.push_back(glm::vec3(-halfSize.x, height, halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
}

void SimpleBuilding::generateUVs(glm::vec3 size, std::vector<glm::vec2>& uvs) {
	glm::vec2 numOfWindows = round(glm::vec2((2 * size.x + 2 * size.z) * numOfWindowsPerMeter.x, size.y * numOfWindowsPerMeter.y));
	glm::vec2 percentageOfTextureUsed = glm::vec2(numOfWindows.x / WindowsTextureGenerator::numOfWindows, numOfWindows.y / WindowsTextureGenerator::numOfWindows);
	if (percentageOfTextureUsed.x > 1) percentageOfTextureUsed.x = 1;
	if (percentageOfTextureUsed.y > 1) percentageOfTextureUsed.y = 1;
	glm::vec2 percentageOfTextureLeft = glm::vec2(1, 1) - percentageOfTextureUsed;
	glm::vec2 uvOffset = glm::vec2(getRandomFloat(0, percentageOfTextureLeft.x), getRandomFloat(0, percentageOfTextureLeft.y));

	//front
	uvs.push_back(glm::vec2(0, 0));			uvs.push_back(glm::vec2(0.25, 0));			uvs.push_back(glm::vec2(0.25, 1));
	uvs.push_back(glm::vec2(0, 0));			uvs.push_back(glm::vec2(0.25, 1));			uvs.push_back(glm::vec2(0, 1));

	//left
	uvs.push_back(glm::vec2(0.75, 0));		uvs.push_back(glm::vec2(1, 0));				uvs.push_back(glm::vec2(1, 1));
	uvs.push_back(glm::vec2(0.75, 0));		uvs.push_back(glm::vec2(1, 1));				uvs.push_back(glm::vec2(0.75, 1));

	//back
	uvs.push_back(glm::vec2(0.5, 0));		uvs.push_back(glm::vec2(0.75, 0));			uvs.push_back(glm::vec2(0.75, 1));
	uvs.push_back(glm::vec2(0.5, 0));		uvs.push_back(glm::vec2(0.75, 1));			uvs.push_back(glm::vec2(0.5, 1));

	//right
	uvs.push_back(glm::vec2(0.25, 0));		uvs.push_back(glm::vec2(0.5, 0));			uvs.push_back(glm::vec2(0.5, 1));
	uvs.push_back(glm::vec2(0.25, 0));		uvs.push_back(glm::vec2(0.5, 1));			uvs.push_back(glm::vec2(0.25, 1));

	//top
	uvs.push_back(glm::vec2(0, 0));			uvs.push_back(glm::vec2(0, 0));				uvs.push_back(glm::vec2(0, 0));
	uvs.push_back(glm::vec2(0, 0));			uvs.push_back(glm::vec2(0, 0));				uvs.push_back(glm::vec2(0, 0));

	for (int i = 0; i < uvs.size(); i++) {
		uvs[i].x = uvs[i].x * percentageOfTextureUsed.x + uvOffset.x;
		uvs[i].y = 1 - (uvs[i].y * percentageOfTextureUsed.y + uvOffset.y);
	}
}