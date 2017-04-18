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
#include "ObjExporter.h"

Texture *Scene::windowsTexture = NULL;
std::vector<LandPlot> plots;

const float Scene::minBuildingHeight = 20;
const float Scene::maxBuildingHeight = 300;
const float Scene::citySize = 1000;
const int Scene::numOfSubdivisions = 12;
const float Scene::majorRoadSize = 30;

Scene::Scene(std::vector<Square*> grids) {
	userGrids = grids;
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

	//skybox
	glDepthMask(GL_FALSE);
	glUseProgram(skyboxShader);
	glUniformMatrix4fv(
				glGetUniformLocation(skyboxShader, "ProjectionMatrix"), 1,
				false, &(getProjectionMatrix()[0][0]));

	s_box->draw(skyboxShader, cam.getViewMatrix());

	glDepthMask(GL_TRUE);

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
}

void Scene::renderScene(float dt) {
	//update the camera's position
	cam.update(dt);
	//TODO: Add rendering for the skybox, and write its shaders
	renderPhong();
}

void Scene::loadShaders() {
	ShaderLoader loader;
	basicPhongShader = loader.loadShader(
			"CityGeneration/Shaders/PhongVertexShader.glsl",
			"CityGeneration/Shaders/PhongFragmentShader.glsl");
	shader2D = loader.loadShader("CityGeneration/Shaders/Shader2DVertex.glsl",
			"CityGeneration/Shaders/Shader2DFragment.glsl");
	skyboxShader = loader.loadShader(
			"CityGeneration/Shaders/SkyboxVertexShader.glsl",
			"CityGeneration/Shaders/SkyboxFragmentShader.glsl");
}

void Scene::loadOtherStuff() {
	WindowsTextureGenerator g;
	windowsTexture = g.generateTexture();
}

void Scene::loadObjects() {
	float planeY = -5.0f;
	plane = new Plane(glm::vec3(-citySize, planeY, -citySize), glm::vec3(citySize, planeY, citySize), glm::vec3(0.1f));
	objects.push_back(plane);

	float maxArea = 4 * citySize * citySize;

	for (Square *userGrid : userGrids) {
		Road *r1 = new Road(glm::length(*userGrid->bottom->getRight() - *userGrid->bottom->getLeft()) * citySize - majorRoadSize, majorRoadSize, userGrid->bottom->getLeft()->x * citySize + majorRoadSize / 2.0f, userGrid->bottom->getLeft()->y * citySize, 2);
		Road *r2 = new Road(glm::length(*userGrid->top->getRight() - *userGrid->top->getLeft()) * citySize - majorRoadSize, majorRoadSize, userGrid->top->getLeft()->x * citySize + majorRoadSize / 2.0f, userGrid->top->getLeft()->y * citySize, 2);
		Road *r3 = new Road(glm::length(*userGrid->left->getTop() - *userGrid->left->getBot()) * citySize - majorRoadSize, majorRoadSize, userGrid->left->getBot()->x * citySize, userGrid->left->getBot()->y * citySize + majorRoadSize / 2.0f, 1);
		Road *r4 = new Road(glm::length(*userGrid->right->getTop() - *userGrid->right->getBot()) * citySize - majorRoadSize, majorRoadSize, userGrid->right->getBot()->x * citySize, userGrid->right->getBot()->y * citySize + majorRoadSize / 2.0f, 1);
		std::vector<Road *> roads; roads.push_back(r1); roads.push_back(r2); roads.push_back(r3); roads.push_back(r4);
		RoadCreator* roadCreator = new RoadCreator();
		roadCreator->setMedianColor(glm::vec3(1, 0, 0));
		roadCreator->makeRenderableRoads(roads);
		objects.push_back(roadCreator);
		
		glm::vec2 start = *userGrid->bottom->getLeft() * citySize;
		glm::vec2 size = (*userGrid->top->getRight() - *userGrid->bottom->getLeft()) * citySize;
		float gridArea = size.x * size.y;

		std::vector<LandPlot> plots;

		if (userGrid->canBeSubdivided) {
			Grid grid(start.x + majorRoadSize / 2, start.y + majorRoadSize / 2, size.x - majorRoadSize, size.y - majorRoadSize);
			GridFactory fact;
			GridHistory hist = fact.generateCustomSubGrids(&grid, std::max(numOfSubdivisions - floor(log(maxArea / gridArea)) , 0.0f));
			plots = hist.getBuildingSpots();

			std::vector<Grid *> grids = hist.getLastLevelOfGrid();
			RoadCreator* roadCreator = new RoadCreator();
			roadCreator->makeRenderableRoads(grids.at(0)->getRoads());
			objects.push_back(roadCreator);
		}
		else {
			glm::vec2 halfRoadSize(majorRoadSize / 2.0f);
			LandPlot p;
			p.bot_left = *userGrid->bottom->getLeft() * citySize + halfRoadSize;
			p.top_left = *userGrid->top->getLeft() * citySize; p.top_left.x += halfRoadSize.x; p.top_left.y -= halfRoadSize.x;
			p.top_right = *userGrid->top->getRight() * citySize - halfRoadSize;
			p.bot_right = *userGrid->bottom->getRight() * citySize; p.bot_right.x -= halfRoadSize.x; p.bot_right.y += halfRoadSize.x;
			plots.push_back(p);
		}

		for (LandPlot plot : plots) {
			for (LandPlot p : subdividePlot(plot)) {
				::plots.push_back(p);
				glm::vec2 center = (p.bot_left + p.top_right) / 2.0f;
				glm::vec2 size = glm::vec2(p.bot_right.x - p.bot_left.x,
					p.top_left.y - p.bot_left.y);

				if (size.x == 0 || size.y == 0) {
					continue;
				}

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
				}
				else if (buildingType < 0.66f) {
					b = new SimpleBuilding(glm::vec3(center.x, 0, center.y),
						glm::vec3(size.x, 0, size.y), buildingHeightMin,
						buildingHeightMax);
				}
				else if (buildingType <= 1) {
					b = new ComplexBlockBuilding(glm::vec3(center.x, 0, center.y),
						glm::vec3(size.x, 0, size.y), buildingHeightMin,
						buildingHeightMax);
				}
				objects.push_back(b);
			}
		}


		s_box = new Skybox();
		s_box->updateScale(vec3(30000.0f));
	}
}

void Scene::exportToObj() {
	std::vector<SceneObject*> objectsToExport;
	for (SceneObject *obj : objects) {
		//ignore skybox
		if (obj != s_box) {
			objectsToExport.push_back(obj);
		}
	}
	ObjExporter *exp = new ObjExporter(objectsToExport, windowsTexture);
	exp->exportToObj();
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
