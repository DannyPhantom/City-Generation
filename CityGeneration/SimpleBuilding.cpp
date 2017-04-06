#include "SimpleBuilding.h"
#include "WindowsTextureGenerator.h"
#include "Scene.h"
#include "Randomizer.h"

SimpleBuilding::SimpleBuilding(glm::vec3 center, glm::vec3 size, float minHeight, float maxHeight) : BlockBuilding(center, size, minHeight, maxHeight)
{
	create();
}


SimpleBuilding::~SimpleBuilding()
{
}

void SimpleBuilding::create() {
	glm::vec3 blockSize = size;
	int numOfBlocks = Randomizer::getRandomInt(3, 7);
	glm::vec3 minSize = 0.25f * size;
	float blockHeight = 0.4 * minHeight;

	for (int i = 0; i < numOfBlocks && blockSize.x > minSize.x && blockSize.z > minSize.z && blockHeight <= maxHeight; i++) {
		blockSize -= blockSize * Randomizer::getRandomFloat(0.05, 0.15);
		blockHeight += (maxHeight - minHeight) * Randomizer::getRandomFloat(0.05, 0.15);
		blockSize.y = blockHeight;
		generateBlock(glm::vec3(0, 0, 0), blockSize);
	}

	generateRoof(blockSize / 2.0f, blockHeight, blockHeight + (maxHeight - minHeight) * Randomizer::getRandomFloat(0.1, 0.25));

	setupVBOs();
	setupVAOs();
}

void SimpleBuilding::generateRoof(glm::vec3 halfSize, float heightStart, float heightEnd) {
	const glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec4> colors;
	std::vector<GLuint> indices;

	//front
	glm::vec3 v1 = glm::vec3(-halfSize.x, heightStart, -halfSize.z);
	glm::vec3 v2 = glm::vec3(halfSize.x, heightStart, -halfSize.z);
	glm::vec3 v3 = glm::vec3(0, heightEnd, 0);
	glm::vec3 normal = -glm::cross(v2 - v1, v3 - v1);
	vertices.push_back(v1);		normals.push_back(normal);	
	vertices.push_back(v2);		normals.push_back(normal);
	vertices.push_back(v3);		normals.push_back(normal);

	//left
	v1 = glm::vec3(-halfSize.x, heightStart, halfSize.z);
	v2 = glm::vec3(-halfSize.x, heightStart, -halfSize.z);
	v3 = glm::vec3(0, heightEnd, 0);
	normal = -glm::cross(v2 - v1, v3 - v1);
	vertices.push_back(v1);		normals.push_back(normal);
	vertices.push_back(v2);		normals.push_back(normal);
	vertices.push_back(v3);		normals.push_back(normal);

	//back
	v1 = glm::vec3(halfSize.x, heightStart, halfSize.z);
	v2 = glm::vec3(-halfSize.x, heightStart, halfSize.z);
	v3 = glm::vec3(0, heightEnd, 0);
	normal = -glm::cross(v2 - v1, v3 - v1);
	vertices.push_back(v1);		normals.push_back(normal);
	vertices.push_back(v2);		normals.push_back(normal);
	vertices.push_back(v3);		normals.push_back(normal);

	//right
	v1 = glm::vec3(halfSize.x, heightStart, -halfSize.z);
	v2 = glm::vec3(halfSize.x, heightStart, halfSize.z);
	v3 = glm::vec3(0, heightEnd, 0);
	normal = -glm::cross(v2 - v1, v3 - v1);
	vertices.push_back(v1);		normals.push_back(normal);
	vertices.push_back(v2);		normals.push_back(normal);
	vertices.push_back(v3);		normals.push_back(normal);

	for (int i = 0; i < vertices.size(); i++) {
		colors.push_back(color);
		indices.push_back(i);
		uvs.push_back(glm::vec2(0.0f, 0.0f));
	}

	Mesh *m = new Mesh(vertices, uvs, colors, normals, indices, NULL, 4);
	addMesh(m);
}
