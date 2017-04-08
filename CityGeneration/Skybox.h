/*
 * Skybox.h
 *
 *  Created on: Apr 7, 2017
 *      Author: marc.desorcy
 */

#ifndef CITYGENERATION_SKYBOX_H_
#define CITYGENERATION_SKYBOX_H_

#include <string>
#include "Quad2D.h"
#include "Texture.h"
#include "SceneObject.h"
#include "Libraries/glew/glew.h"
#include "Libraries/stb_image.h"

class Skybox:public SceneObject {
public:
	Skybox();
	virtual ~Skybox();

	bool loadCubemap(std::vector<const GLchar*> faces);

	GLuint getCubemapTexture(){return textureObj;}

private:
	GLuint textureObj;						//Id of the texture

	void create();
};

#endif /* CITYGENERATION_SKYBOX_H_ */
