#include "ObjExporter.h"
#include "Mesh.h"
#include "WindowsTextureGenerator.h"
#include <iostream>
#include <fstream>


ObjExporter::ObjExporter(std::vector<SceneObject *> objects, Texture *buildingTexture) : objects(objects), buildingTexture(buildingTexture)
{

}


ObjExporter::~ObjExporter()
{
}

//code from http://www.flashbang.se/archives/155
void ObjExporter::exportTexture() {
	long imageSize = WindowsTextureGenerator::textureDimensions * WindowsTextureGenerator::textureDimensions * 3;
	unsigned char *data = new unsigned char[imageSize];
	buildingTexture->Bind(GL_TEXTURE0);
	glGetTexImage(GL_TEXTURE_2D, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
	buildingTexture->unBind(GL_TEXTURE0);
	// split x and y sizes into bytes
	int xa = WindowsTextureGenerator::textureDimensions % 256;
	int xb = (WindowsTextureGenerator::textureDimensions - xa) / 256;
	int ya = WindowsTextureGenerator::textureDimensions % 256;
	int yb = (WindowsTextureGenerator::textureDimensions - ya) / 256;
	//assemble the header
	unsigned char header[18] = { 0,0,2,0,0,0,0,0,0,0,0,0,(char)xa,(char)xb,(char)ya,(char)yb,24,0 };

	// write header and data to file
	std::fstream file("city.tga", std::ios::out | std::ios::binary | std::ios::trunc);
	file.write(reinterpret_cast<char *>(header), sizeof(char) * 18);
	file.write(reinterpret_cast<char *>(data), sizeof(char)*imageSize);
	file.close();

	delete[] data;
	data = NULL;
}

void ObjExporter::exportMesh(Mesh *m, std::ofstream &fileStream, int startingFaceIndex, glm::mat4 modelMatrix) {
	fileStream << "o Mesh" << (long long)m << "\n";
	for (glm::vec3 vertex : *m->getVertices()) {
		glm::vec4 v = modelMatrix * glm::vec4(vertex, 1.0f);
		fileStream << "v " << v.x << " " << v.y << " " << v.z << "\n";
	}

	for (glm::vec3 normal : *m->getNormals()) {
		fileStream << "vn " << normal.x << " " << normal.y << " " << normal.z << "\n";
	}

	for (glm::vec2 uv : *m->getUVs()) {
		fileStream << "vt " << uv.x << " " << uv.y << "\n";
	}

	if (!m->hasTexture()) {
		fileStream << "usemtl mtl" << (long long)m << "\n";
	}
	else {
		fileStream << "usemtl texturedMTL\n";
	}

	if (m->hasTexture()) {
		for (int i = 1; i <= m->getVertices()->size(); i += 3) {
			fileStream << "f ";
			fileStream << (startingFaceIndex + i) << "/" << (startingFaceIndex + i) << "/" << (startingFaceIndex + i) << " ";
			fileStream << (startingFaceIndex + i + 1) << "/" << (startingFaceIndex + i + 1) << "/" << (startingFaceIndex + i + 1) << " ";
			fileStream << (startingFaceIndex + i + 2) << "/" << (startingFaceIndex + i + 2) << "/" << (startingFaceIndex + i + 2) << "\n";
		}
	}
	else {
		for (int i = 1; i <= m->getVertices()->size(); i += 3) {
			fileStream << "f ";
			fileStream << (startingFaceIndex + i) << "//" << (startingFaceIndex + i) << " ";
			fileStream << (startingFaceIndex + i + 1) << "//" << (startingFaceIndex + i + 1) << " ";
			fileStream << (startingFaceIndex + i + 2) << "//" << (startingFaceIndex + i + 2) << "\n";
		}
	}
}

void ObjExporter::exportMeshMTL(Mesh *m, std::ofstream &fileStream) {
	if (!m->hasTexture()) {
		fileStream << "newmtl mtl" << (long long)m << "\n";
		fileStream << "Ns 96.078431\n";
		fileStream << "Ka 0.000000 0.000000 0.000000\n";
		fileStream << "Kd " << (*m->getColors())[0].r << " " << (*m->getColors())[0].g << " " << (*m->getColors())[0].b << "\n";
		fileStream << "Ks 0.500000 0.500000 0.500000\n";
		fileStream << "Ni 1.000000\n";
		fileStream << "d 1.000000\n";
		fileStream << "illum 2\n";
	}
}

void ObjExporter::exportToObj() {
	exportTexture();

	//obj file
	std::ofstream objStream;
	objStream.open("city.obj", std::ofstream::out | std::ofstream::trunc);

	objStream << "mtllib city.mtl\n";
	int startingFaceIndex = 0;
	for (SceneObject *obj : objects) {
		for (Mesh *m : *obj->getMeshes()) {
			exportMesh(m, objStream, startingFaceIndex, obj->getModelMatrix());
			startingFaceIndex += m->getIndices()->size();
		}
	}
	objStream.close();

	//mtl file
	std::ofstream mtlStream;
	mtlStream.open("city.mtl", std::ofstream::out | std::ofstream::trunc);

	mtlStream << "newmtl texturedMTL\n";
	mtlStream << "Ns 96.078431\n";
	mtlStream << "Ka 1.000000 1.000000 1.000000\n";
	mtlStream << "Kd 1.000000 1.000000 1.000000\n";
	mtlStream << "Ks 0.500000 0.500000 0.500000\n";
	mtlStream << "Ni 1.000000\n";
	mtlStream << "d 1.000000\n";
	mtlStream << "illum 2\n";
	mtlStream << "map_Ka city.tga\n";
	mtlStream << "map_Kd city.tga\n";

	for (SceneObject *obj : objects) {
		for (Mesh *m : *obj->getMeshes()) {
			exportMeshMTL(m, mtlStream);
		}
	}
	mtlStream.close();
}