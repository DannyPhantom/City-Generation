#pragma once

#include <vector>
#include "RoadCreator.h"
#include "SceneObject.h"
#include "Camera.h"
#include "Skybox.h"
#include <chrono>
#include <string>

class Texture;
struct LandPlot;

/*
	The main class of the program.
	Contains all the UI's, objects, basic controls, etc.
*/
class Scene
{
public:
	static Texture *windowsTexture;

	static const float minBuildingHeight;
	static const float maxBuildingHeight;
	static const float citySize;

	Scene();
	~Scene();

	/*
		Initializes the scene
	*/
	void initializeScene();

	/*
		Renders the scene
	*/
	void renderScene(float dt);

	/*
		Returns the scene's camera (controlled by the user)
	*/
	Camera *getCamera() { return &cam; }

private:

	/*
		Loads all the shaders
	*/
	void loadShaders();
	
	/*
		Loads all the objects
	*/
	void loadObjects();

	/*
		Loads some various stuff such as
		ssao kernel, ssao noise texture,
		etc.
	*/
	void loadOtherStuff();
	
	/*
		Places all the objects in the scene, i.e.
		assigns the position and scales for the skybox and
		the city
	*/
	void placeObjects();

	/*
		Returns the projection matrix for the scene
	*/
	glm::mat4 getProjectionMatrix();

	/*
		Returns the inverse projection matrix for the scene
	*/
	glm::mat4 getInverseProjectionMatrix();

	/*
		Renders the scene using phong shading
	*/
	void renderPhong();

	std::pair<float, float> getBuildingHeightBasedOnLocation(glm::vec2 buildingCenter);

	std::vector<LandPlot> subdividePlot(LandPlot p);

private:
	std::vector<SceneObject *> objects;

	Skybox s_box;

	glm::mat4 projectionMatrix;
	glm::mat4 inverseProjectionMatrix;

	//shaders
	GLuint basicPhongShader;
	GLuint shader2D;
	Camera cam;
};

