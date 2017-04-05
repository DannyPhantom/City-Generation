#include "Scene.h"
#include "ShaderLoader.h"
#include "ObjLoader.h"
#include "SceneParameters.h"
#include "Libraries/glm/gtc/matrix_transform.hpp"
#include "Libraries/glm/gtc/type_ptr.hpp"
#include <chrono>
#include "Texture.h"
#include "WindowsTextureGenerator.h"
#include "SimpleBuilding.h"
#include "RoundBuilding.h"
#include "ComplexBlockBuilding.h"
#include "GridFactory.h"
#include "GridHistory.h"
#include "Grid.h"
#include "Randomizer.h"

Texture *Scene::windowsTexture = NULL;

Scene::Scene()
{
}

Scene::~Scene()
{
}

void Scene::initializeScene() {
	//define the projection matrix (it's constant and never changes)
	projectionMatrix = glm::perspective(
		glm::radians(90.0f),
		1.0f * SceneParameters::getScreenWidth() / SceneParameters::getScreenHeight(),
		SceneParameters::getZNear(),
		SceneParameters::getZFar()
	);

	//define the inverse of the projection matrix
	inverseProjectionMatrix = glm::inverse(projectionMatrix);

	//load all the stuff
	loadShaders();
	loadOtherStuff();
	loadObjects();
	placeObjects();
}

void Scene::renderPhong() {
	std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUseProgram(basicPhongShader);

	glUniformMatrix4fv(glGetUniformLocation(basicPhongShader, "ProjectionMatrix"), 1, false, &(getProjectionMatrix()[0][0]));

	for (SceneObject *obj : objects) {
		obj->draw(basicPhongShader, cam.getViewMatrix());
	}

	glUseProgram(0);
}

void Scene::renderScene(float dt) {
	//update the camera's position
	cam.update(dt);
	renderPhong();
}

void Scene::loadShaders() {
	ShaderLoader loader;
	basicPhongShader = loader.loadShader("CityGeneration/Shaders/PhongVertexShader.glsl", "CityGeneration/Shaders/PhongFragmentShader.glsl");
	shader2D = loader.loadShader("CityGeneration/Shaders/Shader2DVertex.glsl", "CityGeneration/Shaders/Shader2DFragment.glsl");
}

void Scene::loadOtherStuff() {
	WindowsTextureGenerator g;
	windowsTexture = g.generateTexture();
}

void Scene::loadObjects() {
	ObjLoader loader;
	//objects.push_back(loader.loadFromFile("CityGeneration/Models/bunny.obj"));
	//objects.push_back(new ComplexBlockBuilding(glm::vec3(100, 0, 0), glm::vec3(40, 0, 40)));

	Grid grid(-1000, -1000, 2000, 2000);
	GridFactory fact;
	GridHistory hist = fact.generateCustomSubGrids(&grid, 11);
	std::vector<LandPlot> plots = hist.getBuildingSpots();

	int i = 0;
	for (LandPlot plot : plots) {
		std::cout << "Plot " << i << ": BL = (" << plot.bot_left.x << ", " << plot.bot_left.y
				<<"); TL = (" << plot.top_left.x << ", " << plot.top_left.y
				<<"); TR = (" << plot.top_right.x << ", " << plot.top_right.y
				<<"); BR = (" << plot.bot_right.x << ", " << plot.bot_right.y << "\n";
				i++;
		glm::vec2 center = (plot.bot_left + plot.top_right) / 2.0f;
		glm::vec2 size = glm::vec2(plot.bot_right.x - plot.bot_left.x, plot.top_left.y - plot.bot_left.y);
		Building *b = NULL;
		float buildingType = Randomizer::getRandomFloat(0.0f, 1.0f);
		if (buildingType < 0.33f) {
			b = new RoundBuilding(glm::vec3(center.x, 0, center.y), glm::vec3(size.x, 0, size.y));
		}
		else if (buildingType < 0.66f) {
			b = new SimpleBuilding(glm::vec3(center.x, 0, center.y), glm::vec3(size.x, 0, size.y));
		}
		else if (buildingType <= 1) {
			b = new ComplexBlockBuilding(glm::vec3(center.x, 0, center.y), glm::vec3(size.x, 0, size.y));
		}
		objects.push_back(b);
		/*std::cout << "Pos : " << center.x << " " << center.y << std::endl;
		std::cout << "Size : " << size.x << " " << size.y << std::endl;*/
	}
}

void Scene::placeObjects() {
}

glm::mat4 Scene::getProjectionMatrix() {
	return projectionMatrix;
}

glm::mat4 Scene::getInverseProjectionMatrix() {
	return inverseProjectionMatrix;
}
