#include "BlockBuilding.h"
#include "WindowsTextureGenerator.h"
#include "Randomizer.h"
#include "Scene.h"


BlockBuilding::BlockBuilding(glm::vec3 center, glm::vec3 size) : Building(center, size)
{
}


BlockBuilding::~BlockBuilding()
{
}


void BlockBuilding::generateHorizontalPlane(glm::vec3 halfSize, float height, std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals) {
	vertices.push_back(glm::vec3(-halfSize.x, height, -halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
	vertices.push_back(glm::vec3(halfSize.x, height, -halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
	vertices.push_back(glm::vec3(halfSize.x, height, halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));

	vertices.push_back(glm::vec3(-halfSize.x, height, -halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
	vertices.push_back(glm::vec3(halfSize.x, height, halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
	vertices.push_back(glm::vec3(-halfSize.x, height, halfSize.z));		normals.push_back(glm::vec3(0, 1, 0));
}

void BlockBuilding::generateUVsForBlock(glm::vec3 size, std::vector<glm::vec2>& uvs) {
	glm::vec2 numOfWindows = round(glm::vec2((2 * size.x + 2 * size.z) * numOfWindowsPerMeter.x, size.y * numOfWindowsPerMeter.y));
	glm::vec2 percentageOfTextureUsed = glm::vec2(numOfWindows.x / WindowsTextureGenerator::numOfWindows, numOfWindows.y / WindowsTextureGenerator::numOfWindows);
	if (percentageOfTextureUsed.x > 1) percentageOfTextureUsed.x = 1;
	if (percentageOfTextureUsed.y > 1) percentageOfTextureUsed.y = 1;
	glm::vec2 percentageOfTextureLeft = glm::vec2(1, 1) - percentageOfTextureUsed;
	glm::vec2 uvOffset = glm::vec2(Randomizer::getRandomFloat(0, percentageOfTextureLeft.x), Randomizer::getRandomFloat(0, percentageOfTextureLeft.y));

	//front
	float xRight = size.x / ((2 * size.x + 2 * size.z));
	uvs.push_back(glm::vec2(0, 0));			uvs.push_back(glm::vec2(xRight, 0));			uvs.push_back(glm::vec2(xRight, 1));
	uvs.push_back(glm::vec2(0, 0));			uvs.push_back(glm::vec2(xRight, 1));			uvs.push_back(glm::vec2(0, 1));

	//left
	float xLeft = (2 * size.x + size.z) / ((2 * size.x + 2 * size.z));;
	uvs.push_back(glm::vec2(xLeft, 0));		uvs.push_back(glm::vec2(1, 0));				uvs.push_back(glm::vec2(1, 1));
	uvs.push_back(glm::vec2(xLeft, 0));		uvs.push_back(glm::vec2(1, 1));				uvs.push_back(glm::vec2(xLeft, 1));

	//back
	xRight = xLeft;
	uvs.push_back(glm::vec2(0.5, 0));		uvs.push_back(glm::vec2(xRight, 0));			uvs.push_back(glm::vec2(xRight, 1));
	uvs.push_back(glm::vec2(0.5, 0));		uvs.push_back(glm::vec2(xRight, 1));			uvs.push_back(glm::vec2(0.5, 1));

	//right
	xLeft = size.x / ((2 * size.x + 2 * size.z));
	uvs.push_back(glm::vec2(xLeft, 0));		uvs.push_back(glm::vec2(0.5, 0));			uvs.push_back(glm::vec2(0.5, 1));
	uvs.push_back(glm::vec2(xLeft, 0));		uvs.push_back(glm::vec2(0.5, 1));			uvs.push_back(glm::vec2(xLeft, 1));

	//top
	uvs.push_back(glm::vec2(0, 0));			uvs.push_back(glm::vec2(0, 0));				uvs.push_back(glm::vec2(0, 0));
	uvs.push_back(glm::vec2(0, 0));			uvs.push_back(glm::vec2(0, 0));				uvs.push_back(glm::vec2(0, 0));

	for (int i = 0; i < uvs.size(); i++) {
		uvs[i].x = uvs[i].x * percentageOfTextureUsed.x + uvOffset.x;
		uvs[i].y = 1 - (uvs[i].y * percentageOfTextureUsed.y + uvOffset.y);
	}
}

void BlockBuilding::generateBlock(glm::vec3 center, glm::vec3 size) {
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
	generateUVsForBlock(size, uvs);


	for (int i = 0; i < vertices.size(); i++) {
		vertices[i] += center;
		colors.push_back(glm::vec4(1, 1, 1, 1));
		indices.push_back(i);
	}

	Mesh *m = new Mesh(vertices, uvs, colors, normals, indices, Scene::windowsTexture, 10);
	addMesh(m);
}