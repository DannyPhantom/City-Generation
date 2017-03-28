#include "Scene.h"
#include "ShaderLoader.h"
#include "ObjLoader.h"
#include "SceneParameters.h"
#include "Libraries/glm/gtc/matrix_transform.hpp"
#include "Libraries/glm/gtc/type_ptr.hpp"
#include <chrono>
#include "Texture.h"
#include "WindowsTextureGenerator.h"

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

	/*glUseProgram(basicPhongShader);

	glUniformMatrix4fv(glGetUniformLocation(basicPhongShader, "ProjectionMatrix"), 1, false, &(getProjectionMatrix()[0][0]));

	for (SceneObject *obj : objects) {
		obj->draw(basicPhongShader, cam.getViewMatrix());
	}*/
	glUseProgram(shader2D);
	//create a rectangle with 4 vertices
		float vertices[] = { -1, 1,		//BL
				-1, -1, 	//TL
				1, 1,		//BR
				1, -1,		//TR
				};

		// and create the uv's for the vertices
		float uvs[] = { 0, 0,		//BL
				0, 1, 	//TL
				1, 0,		//BR
				1, 1,		//TR
				};

		GLuint VBO_vertices, VBO_uvs;

		//passing model attributes to the GPU
		GLuint VAO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		//vertices
		glGenBuffers(1, &VBO_vertices);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_vertices);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(0);

		//uv's
		glGenBuffers(1, &VBO_uvs);
		glBindBuffer(GL_ARRAY_BUFFER, VBO_uvs);
		glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		glEnableVertexAttribArray(1);

		glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

		glBindVertexArray(VAO);

		//indicate that we use a texture
		glUniform1i(glGetUniformLocation(shader2D, "textureValid"), true);

		glm::mat4 identity(1.0f);
		glm::mat4 translation;
		glm::mat4 scale;
		glm::mat4 modelMatrix;

		//perform some setup
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glDisable(GL_DEPTH_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//pass in the model matrix
		translation = glm::translate(identity,
				glm::vec3(0.0f, 0.0f, 0.0f));

		//scale in y negatively if y is flipped
		scale = glm::scale(identity, glm::vec3(1.0f, 1.0f, 1.0));

		modelMatrix = translation * scale;
		glUniformMatrix4fv(glGetUniformLocation(shader2D, "modelMatrix"), 1,
				GL_FALSE, glm::value_ptr(modelMatrix));

		//attach the texture
		windowsTexture->Bind(GL_TEXTURE0);

		//draw the box
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

		windowsTexture->unBind(GL_TEXTURE0);

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);

		glBindVertexArray(0);

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
	objects.push_back(loader.loadFromFile("CityGeneration/Models/bunny.obj"));
}

void Scene::placeObjects() {
}

glm::mat4 Scene::getProjectionMatrix() {
	return projectionMatrix;
}

glm::mat4 Scene::getInverseProjectionMatrix() {
	return inverseProjectionMatrix;
}
