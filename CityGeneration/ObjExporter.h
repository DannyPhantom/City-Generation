#pragma once

#include "SceneObject.h"
#include "Texture.h"
#include <vector>

class ObjExporter
{
private:
	std::vector<SceneObject *> objects;
	Texture *buildingTexture;

	void exportMesh(Mesh *m, std::ofstream &fileStream, int startingFaceIndex, glm::mat4 modelMatrix);
	void exportMeshMTL(Mesh *m, std::ofstream &fileStream);
	void exportTexture();
public:
	ObjExporter(std::vector<SceneObject *> objects, Texture *buildingTexture);
	~ObjExporter();

	void exportToObj();
};

