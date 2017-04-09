/*
 * Skybox.h
 *
 *  Created on: Apr 7, 2017
 *      Author: marc.desorcy
 */

//#ifndef CITYGENERATION_SKYBOX_H_
//#define CITYGENERATION_SKYBOX_H_

#pragma once

#include <string>
#include "Quad2D.h"
#include "SceneObject.h"
#include "Texture.h"
#include "Libraries/glew/glew.h"
//#include "Libraries/stb_image.h"


class Skybox:public SceneObject {
public:
	Skybox();
	virtual ~Skybox();

	void create();
	void draw(GLuint program, glm::mat4 viewMatrix);

	Texture* loadCubemap(std::vector<const GLchar*> faces);

	//GLuint getCubemapTexture(){return textureObj;}

private:

	//GLuint textureObj;						//Id of the texture

};

//#endif /* CITYGENERATION_SKYBOX_H_ */
