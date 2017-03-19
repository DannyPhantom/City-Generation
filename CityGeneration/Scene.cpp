#include "Scene.h"
#include "ShaderLoader.h"
#include "ObjLoader.h"
#include "SceneParameters.h"
#include "Libraries\glm\gtc\matrix_transform.hpp"
#include <chrono>

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
	loadObjects();
	loadOtherStuff();
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
	//std::cout << "Phong:" << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - t1).count() << std::endl;
}

void Scene::renderScene(float dt) {
	//update the camera's position
	cam.update(dt);
	renderPhong();
}

void Scene::loadShaders() {
	ShaderLoader loader;
	basicPhongShader = loader.loadShader("Shaders/PhongVertexShader.glsl", "Shaders/PhongFragmentShader.glsl");
}

void Scene::loadOtherStuff() {
	
}

void Scene::loadObjects() {
	ObjLoader loader;
	objects.push_back(loader.loadFromFile("Models/bunny.obj"));
}

void Scene::placeObjects() {
}

glm::mat4 Scene::getProjectionMatrix() {
	return projectionMatrix;
}

glm::mat4 Scene::getInverseProjectionMatrix() {
	return inverseProjectionMatrix;
}