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
#include "Road.h"
#include <algorithm>

Texture *Scene::windowsTexture = NULL;
std::vector<LandPlot> plots;
std::vector<Road *> roads;

const float Scene::minBuildingHeight = 20;
const float Scene::maxBuildingHeight = 300;
const float Scene::citySize = 2000;

Scene::Scene() {
}

Scene::~Scene() {
}

void Scene::initializeScene() {
	//define the projection matrix (it's constant and never changes)
	projectionMatrix = glm::perspective(glm::radians(90.0f),
			1.0f * SceneParameters::getScreenWidth()
					/ SceneParameters::getScreenHeight(),
			SceneParameters::getZNear(), SceneParameters::getZFar());

	//define the inverse of the projection matrix
	inverseProjectionMatrix = glm::inverse(projectionMatrix);

	//load all the stuff
	loadShaders();
	loadOtherStuff();
	loadObjects();
	placeObjects();
}

void Scene::renderPhong() {
	std::chrono::high_resolution_clock::time_point t1 =
			std::chrono::high_resolution_clock::now();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glUseProgram(basicPhongShader);

	glUniformMatrix4fv(
			glGetUniformLocation(basicPhongShader, "ProjectionMatrix"), 1,
			false, &(getProjectionMatrix()[0][0]));

	for (SceneObject *obj : objects) {
		obj->draw(basicPhongShader, cam.getViewMatrix());
	}

	glUseProgram(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glLoadMatrixf(&projectionMatrix[0][0]);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glLoadMatrixf(&cam.getViewMatrix()[0][0]);

	glColor3f(1, 1, 1);
	for (LandPlot p : plots) {
		glBegin(GL_LINE_STRIP);
		glVertex3f(p.bot_left.x, 0, p.bot_left.y);
		glVertex3f(p.bot_right.x, 0, p.bot_right.y);
		glVertex3f(p.top_right.x, 0, p.top_right.y);
		glVertex3f(p.top_left.x, 0, p.top_left.y);
		glVertex3f(p.bot_left.x, 0, p.bot_left.y);
		glEnd();
	}

	glColor3f(1, 1, 0);
	for (Road *r : roads) {
		glBegin(GL_LINES);
		glVertex3f(r->origin_x, 0, r->origin_y);
		if (r->direction == 1)
			glVertex3f(r->origin_x, 0, r->origin_y + r->length);
		if (r->direction == 2)
			glVertex3f(r->origin_x + r->length, 0, r->origin_y);
		glEnd();
	}
}

void Scene::renderScene(float dt) {
	//update the camera's position
	cam.update(dt);
	renderPhong();
}

void Scene::loadShaders() {
	ShaderLoader loader;
	basicPhongShader = loader.loadShader(
			"CityGeneration/Shaders/PhongVertexShader.glsl",
			"CityGeneration/Shaders/PhongFragmentShader.glsl");
	shader2D = loader.loadShader("CityGeneration/Shaders/Shader2DVertex.glsl",
			"CityGeneration/Shaders/Shader2DFragment.glsl");
}

void Scene::loadOtherStuff() {
	WindowsTextureGenerator g;
	windowsTexture = g.generateTexture();
}

void Scene::loadObjects() {
	ObjLoader loader;
	//objects.push_back(loader.loadFromFile("CityGeneration/Models/bunny.obj"));
	//objects.push_back(new ComplexBlockBuilding(glm::vec3(100, 0, 0), glm::vec3(40, 0, 40)));

	Grid grid(-citySize / 2.0f, -citySize / 2.0f, citySize, citySize);
	GridFactory fact;
	GridHistory hist = fact.generateCustomSubGrids(&grid, 11);
	plots = hist.getBuildingSpots();

	for (LandPlot plot : plots) {
		for (LandPlot p : subdividePlot(plot)) {
			glm::vec2 center = (p.bot_left + p.top_right) / 2.0f;
			glm::vec2 size = glm::vec2(p.bot_right.x - p.bot_left.x,
					p.top_left.y - p.bot_left.y);
			std::pair<float, float> buildingHeight =
					getBuildingHeightBasedOnLocation(center);
			float buildingHeightMin = buildingHeight.first;
			float buildingHeightMax = buildingHeight.second;

			Building *b = NULL;
			float buildingType = Randomizer::getRandomFloat(0.0f, 1.0f);
			if (buildingType < 0.33f) {
				b = new RoundBuilding(glm::vec3(center.x, 0, center.y),
						glm::vec3(size.x, 0, size.y), buildingHeightMin,
						buildingHeightMax);
			} else if (buildingType < 0.66f) {
				b = new SimpleBuilding(glm::vec3(center.x, 0, center.y),
						glm::vec3(size.x, 0, size.y), buildingHeightMin,
						buildingHeightMax);
			} else if (buildingType <= 1) {
				b = new ComplexBlockBuilding(glm::vec3(center.x, 0, center.y),
						glm::vec3(size.x, 0, size.y), buildingHeightMin,
						buildingHeightMax);
			}
			objects.push_back(b);
		}
	}

	std::vector<Grid *> grids = hist.getLastLevelOfGrid();
	for (Grid *g : grids) {
		for (Road *r : g->getRoads()) {
			roads.push_back(r);
		}
	}

	RoadCreator* roadCreator = new RoadCreator();
	roadCreator->makeRenderableRoads(grids.at(0)->getRoads());


	objects.push_back(roadCreator);

}

void Scene::placeObjects() {
}

glm::mat4 Scene::getProjectionMatrix() {
	return projectionMatrix;
}

glm::mat4 Scene::getInverseProjectionMatrix() {
	return inverseProjectionMatrix;
}

std::pair<float, float> Scene::getBuildingHeightBasedOnLocation(
		glm::vec2 buildingCenter) {
	float distanceFromCenter = glm::length(buildingCenter);
	//downtown
	if (distanceFromCenter < citySize / 5) {
		return std::make_pair(
				minBuildingHeight
						+ (maxBuildingHeight - minBuildingHeight) * 0.6f,
				maxBuildingHeight);
		//midtown
	} else if (distanceFromCenter < citySize / 3) {
		return std::make_pair(
				minBuildingHeight
						+ (maxBuildingHeight - minBuildingHeight) * 0.3f,
				maxBuildingHeight * 0.6);
		//border-ish of the city
	} else {
		return std::make_pair(minBuildingHeight, maxBuildingHeight * 0.3);
	}
}

std::vector<LandPlot> Scene::subdividePlot(LandPlot p) {
	std::vector<LandPlot> newLandPlots;
	int xSubdivisions = 1;
	int ySubdivisions = 1;
	float maxSize = 0.1 * citySize;

	float plotXSize = p.bot_right.x - p.bot_left.x;
	if (plotXSize > maxSize) {
		xSubdivisions = floor(plotXSize / maxSize);
	}

	float plotYSize = p.top_left.y - p.bot_left.y;
	if (plotYSize > maxSize) {
		ySubdivisions = floor(plotYSize / maxSize);
	}

	glm::vec2 origin = p.bot_left;
	glm::vec2 originalOrigin = origin;
	glm::vec2 buildingSize = glm::vec2(floor(plotXSize / xSubdivisions), floor(plotYSize / ySubdivisions));
	glm::vec2 spacingBetweenBuildings = glm::vec2(
			(plotXSize - xSubdivisions * buildingSize.x) / (xSubdivisions + 1),
			(plotYSize - ySubdivisions * buildingSize.y) / (ySubdivisions + 1)
			);

	for (int i = 0; i < xSubdivisions; i++) {
		origin.y = originalOrigin.y;
		origin.x += spacingBetweenBuildings.x;
		for (int j = 0; j < ySubdivisions; j++) {
			origin.y += spacingBetweenBuildings.y;
			LandPlot plot;
			plot.bot_left = origin;
			plot.bot_right = glm::vec2(origin.x + buildingSize.x, origin.y);
			plot.top_left = glm::vec2(origin.x, origin.y + buildingSize.y);
			plot.top_right = glm::vec2(origin.x + buildingSize.x, origin.y + buildingSize.y);
			newLandPlots.push_back(plot);
			origin.y += buildingSize.y;
		}
		origin.x += buildingSize.x;
	}

	return newLandPlots;
}
