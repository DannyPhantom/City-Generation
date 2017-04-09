/*
 * Skybox.cpp
 *
 *  Created on: Apr 7, 2017
 *      Author: marc.desorcy
 */
//#define STB_IMAGE_IMPLEMENTATION
#include "Skybox.h"

glm::vec3 skyboxVertices[] = {
    // Positions
	glm::vec3(-1.0f,  1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f,  1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f, -1.0f),

	glm::vec3(-1.0f, -1.0f,  1.0f),
	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f, -1.0f),
	glm::vec3(-1.0f,  1.0f,  1.0f),
	glm::vec3(-1.0f, -1.0f,  1.0f),

	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),

	glm::vec3(-1.0f, -1.0f,  1.0f),
	glm::vec3(-1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f, -1.0f,  1.0f),
	glm::vec3(-1.0f, -1.0f,  1.0f),

	glm::vec3(-1.0f,  1.0f, -1.0f),
	glm::vec3(1.0f,  1.0f, -1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(1.0f,  1.0f,  1.0f),
	glm::vec3(-1.0f,  1.0f,  1.0f),
	glm::vec3(-1.0f,  1.0f, -1.0f),

	glm::vec3(-1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f,  1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(1.0f, -1.0f, -1.0f),
	glm::vec3(-1.0f, -1.0f,  1.0f),
	glm::vec3(1.0f, -1.0f,  1.0f)
};

Skybox::Skybox() {
	// TODO Auto-generated constructor stub
	create();
}

Skybox::~Skybox() {
	// TODO Auto-generated destructor stub
}

void Skybox::create()
{
	const glm::vec4 color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	std::vector<glm::vec3> vertices, normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec4> colors;
	std::vector<GLuint> indices;

	for(int i = 0; i < (sizeof(skyboxVertices)/sizeof(*skyboxVertices)); i+=3)
	{
		vertices.push_back(skyboxVertices[i]);
		vertices.push_back(skyboxVertices[i+1]);
		vertices.push_back(skyboxVertices[i+2]);
		glm::vec3 normal = -glm::cross(skyboxVertices[i+1] - skyboxVertices[i], skyboxVertices[i+2] - skyboxVertices[i]);

		normals.push_back(normal);
		normals.push_back(normal);
		normals.push_back(normal);
	}

	for (int j = 0; j < vertices.size(); j++)
	{
		colors.push_back(color);
		indices.push_back(j);
		uvs.push_back(glm::vec2(0.0f, 0.0f));
	}

	std::vector<const GLchar*> faces;
	faces.push_back("CityGeneration/Textures/ame_starfield/starfield_rt.tga");
	faces.push_back("CityGeneration/Textures/ame_starfield/starfield_lf.tga");
	faces.push_back("CityGeneration/Textures/ame_starfield/starfield_up.tga");
	faces.push_back("CityGeneration/Textures/ame_starfield/starfield_dn.tga");
	faces.push_back("CityGeneration/Textures/ame_starfield/starfield_bk.tga");
	faces.push_back("CityGeneration/Textures/ame_starfield/starfield_ft.tga");

	Texture *tex = loadCubemap(faces);

	Mesh *m = new Mesh(vertices, uvs, colors, normals, indices, tex, 12);
	this->addMesh(m);

	this->setupVBOs();
	this->setupVAOs();
}

Texture* Skybox::loadCubemap(std::vector<const GLchar*> faces)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    //glActiveTexture(GL_TEXTURE1);

    int width,height,n;
    unsigned char* image;
    bool loaded = true;
    Texture *text = NULL;

    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    for(GLuint i = 0; i < faces.size(); i++)
    {
    	image = stbi_load(faces[i], &width, &height, &n, 4);
		if (image != NULL)
		{
			//image = SOIL_load_image(faces[i], &width, &height, 0, SOIL_LOAD_RGB);
			glTexImage2D(
					GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0,
					GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image
			);
		}
		else
		{
			std::cout << "Could not load texture " << faces[i] << std::endl;
			loaded = false;
		}
    }
    	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    	text = new Texture(GL_TEXTURE_CUBE_MAP,  textureID);
    	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

    	stbi_image_free(image);

    	//textureObj = textureID;
    	return text;

}

void Skybox::draw(GLuint program, glm::mat4 viewMatrix)
{
	//setup general uniforms
	glUniform1i(glGetUniformLocation(program, "skybox"), 0);
	glm::mat4 mvMatrix = viewMatrix * modelMatrix;
	glm::mat3 normalMatrix = glm::transpose(glm::inverse(glm::mat3(mvMatrix)));
	glUniformMatrix4fv(glGetUniformLocation(program, "ModelViewMatrix"), 1, false, &mvMatrix[0][0]);
	glUniformMatrix3fv(glGetUniformLocation(program, "NormalMatrix"), 1, false, &normalMatrix[0][0]);

	//process and draw one mesh at a time
	for (unsigned int i = 0; i < meshes.size(); i++) {
		Mesh *mesh = meshes.at(i);
		//bind the texture for the object if there is one
		if (mesh->hasTexture()) {
			mesh->getTexture()->Bind(GL_TEXTURE0);
			//glUniform1i(glGetUniformLocation(program, "TextureValid"), true);
		}
		/*else {
			glUniform1i(glGetUniformLocation(program, "TextureValid"), false);
		}*/
		// Draw mesh
		glBindVertexArray(mesh->getVAO());
		glDrawElements(GL_TRIANGLES, mesh->getIndices()->size(), GL_UNSIGNED_INT, 0);

		//disable everything
		glBindVertexArray(0);
		if (mesh->hasTexture()) {
			mesh->getTexture()->unBind(GL_TEXTURE0);
		}
	}
}
