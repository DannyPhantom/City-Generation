#include "RoundBuilding.h"
#include <algorithm>
#include "Scene.h"
#include "WindowsTextureGenerator.h"
#include "Randomizer.h"

#define TWO_PI (6.28318530718f)
#define NUM_OF_POINTS_ON_CIRCLE (40)
#define CIRCLE_STEP (TWO_PI / NUM_OF_POINTS_ON_CIRCLE)

RoundBuilding::RoundBuilding(glm::vec3 center, glm::vec3 size) : Building(center, size)
{
	create();
}


RoundBuilding::~RoundBuilding()
{
}

std::vector<glm::vec3> RoundBuilding::getCircle() {
	int numOfCuts = Randomizer::getRandomInt(0, 4);
	float radius = std::min(size.x, size.z) * 0.5f * Randomizer::getRandomFloat(0.8, 0.99);

	//create circle
	std::vector<glm::vec3> perfectCircle;
	for (double angle = 0; angle <= TWO_PI; angle += CIRCLE_STEP) {
		perfectCircle.push_back(glm::vec3(radius*cos(angle), 0, radius*sin(angle)));
	}

	//create cuts
	int cutStart = 0;
	int cutLength = 0;
	for (int i = 0; i < numOfCuts; i++) {
		cutStart = cutStart + cutLength + Randomizer::getRandomInt(1, NUM_OF_POINTS_ON_CIRCLE / 4);
		cutLength = Randomizer::getRandomInt(1, NUM_OF_POINTS_ON_CIRCLE / 4);
		if (cutStart + cutLength < NUM_OF_POINTS_ON_CIRCLE) {
			for (int j = cutStart; j < cutStart + cutLength; j++) {
				perfectCircle[j] = glm::vec3(0, 0, 0);
			}
		}
	}

	std::vector<glm::vec3> newCircle;
	for (glm::vec3 circlePoint : perfectCircle) {
		if (circlePoint.x != 0 || circlePoint.z != 0) {
			newCircle.push_back(circlePoint);
		}
	}

	return newCircle;
}

void RoundBuilding::create() {
	float buildingHeight = Randomizer::getRandomFloat(minHeight, maxHeight);
	std::vector<glm::vec3> circle = getCircle();

	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec4> colors;
	std::vector<GLuint> indices;
	for (int i = 0; i < circle.size() - 1; i++) {

		glm::vec3 point1 = circle[i];
		glm::vec3 point2 = circle[i + 1];
		glm::vec3 point3 = circle[i + 1]; point3.y = buildingHeight;
		glm::vec3 point4 = circle[i]; point4.y = buildingHeight;

		generateSide(point1, point2, point3, point4, vertices, normals);
	}

	generateUVs(circle, buildingHeight, uvs);
	smoothNormals(normals);
	generateRoof(circle, buildingHeight, vertices, normals, uvs);

	for (int i = 0; i < vertices.size(); i++) {
		colors.push_back(glm::vec4(0, 0, 0, 1));
		indices.push_back(i);
	}

	Mesh *m = new Mesh(vertices, uvs, colors, normals, indices, Scene::windowsTexture, 10);
	addMesh(m);

	setupVBOs();
	setupVAOs();
}

void RoundBuilding::generateUVs(std::vector<glm::vec3> circle, float buildingHeight, std::vector<glm::vec2>& uvs) {
	float circleLength = 0;
	for (int i = 0; i < circle.size(); i++) {
		circleLength += glm::length(circle[(i + 1) % circle.size()] - circle[i]);
	}

	glm::vec2 numOfWindows = round(glm::vec2(circleLength * numOfWindowsPerMeter.x, buildingHeight * numOfWindowsPerMeter.y));
	glm::vec2 percentageOfTextureUsed = glm::vec2(numOfWindows.x / WindowsTextureGenerator::numOfWindows, numOfWindows.y / WindowsTextureGenerator::numOfWindows);
	if (percentageOfTextureUsed.x > 1) percentageOfTextureUsed.x = 1;
	if (percentageOfTextureUsed.y > 1) percentageOfTextureUsed.y = 1;
	glm::vec2 percentageOfTextureLeft = glm::vec2(1, 1) - percentageOfTextureUsed;
	glm::vec2 uvOffset = glm::vec2(Randomizer::getRandomFloat(0, percentageOfTextureLeft.x), Randomizer::getRandomFloat(0, percentageOfTextureLeft.y));

	float uvStart = 0;
	for (int i = 0; i < circle.size()-1; i++) {
		float uvLength = glm::length(circle[(i + 1) % circle.size()] - circle[i]) / circleLength;
		uvs.push_back(glm::vec2(uvStart, 0));
		uvs.push_back(glm::vec2(uvStart + uvLength, 0));
		uvs.push_back(glm::vec2(uvStart + uvLength, 1));
		uvs.push_back(glm::vec2(uvStart, 0));
		uvs.push_back(glm::vec2(uvStart + uvLength, 1));
		uvs.push_back(glm::vec2(uvStart, 1));
		uvStart += uvLength;
	}
	
	for (int i = 0; i < uvs.size(); i++) {
		uvs[i].x = uvs[i].x * percentageOfTextureUsed.x + uvOffset.x;
		uvs[i].y = 1 - (uvs[i].y * percentageOfTextureUsed.y + uvOffset.y);
	}
}

void RoundBuilding::smoothNormals(std::vector<glm::vec3>& normals) {
	//go 6 at a time which represent 1 side
	for (int i = 0; i < normals.size(); i += 6) {
		int prevIndex = i - 1;
		if (prevIndex < 0) prevIndex = normals.size() - 1;

		normals[i] = normals[i + 3] = normals[i + 5] = (normals[i] + normals[prevIndex]) / 2.0f;
		normals[i + 1] = normals[i + 2] = normals[i + 4] = (normals[i + 1] + normals[(i + 6) % normals.size()]) / 2.0f;
	}
}

void RoundBuilding::generateRoof(std::vector<glm::vec3> circle, float buildingHeight, std::vector<glm::vec3> &vertices, std::vector<glm::vec3> &normals, std::vector<glm::vec2> &uvs) {
	for (int i = 0; i < circle.size(); i++) {
		glm::vec3 p1 = circle[i]; p1.y = buildingHeight;
		glm::vec3 p2 = circle[(i + 1) % circle.size()]; p2.y = buildingHeight;
		vertices.push_back(p1);										normals.push_back(glm::vec3(0, 1, 0));			uvs.push_back(glm::vec2(0, 0));
		vertices.push_back(p2);										normals.push_back(glm::vec3(0, 1, 0));			uvs.push_back(glm::vec2(0, 0));
		vertices.push_back(glm::vec3(0, buildingHeight, 0));		normals.push_back(glm::vec3(0, 1, 0));			uvs.push_back(glm::vec2(0, 0));
	}
}