#include "Plane.h"



Plane::Plane(glm::vec3 start, glm::vec3 end, glm::vec3 color)
{
	create(start, end, color);
}


Plane::~Plane()
{
}

void Plane::create(glm::vec3 start, glm::vec3 end, glm::vec3 color) {
	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec4> colors;
	std::vector<GLuint> indices;

	vertices.push_back(start); vertices.push_back(glm::vec3(end.x, end.y, start.z)); vertices.push_back(end);
	vertices.push_back(start); vertices.push_back(end); vertices.push_back(glm::vec3(start.x, end.y, end.z));

	for (int i = 0; i < 6; i++) {
		normals.push_back(glm::vec3(0, 1, 0));
		uvs.push_back(glm::vec2(0, 0));
		colors.push_back(glm::vec4(color, 1.0));
		indices.push_back(i);
	}

	addMesh(new Mesh(vertices, uvs, colors, normals, indices, NULL, 2));
	setupVBOs();
	setupVAOs();
}