/*
 * WindowsTextureGenerator.h
 *
 *  Created on: Mar 27, 2017
 *      Author: dannyphantom
 */

#ifndef CITYGENERATION_WINDOWSTEXTUREGENERATOR_H_
#define CITYGENERATION_WINDOWSTEXTUREGENERATOR_H_

#include "Texture.h"
#include "Libraries/glew/glew.h"
#include <vector>

class WindowsTextureGenerator {
private:
	const int textureDimensions = 512;
	const int numOfWindows = 64;

	float* getWindowIntensities();

public:
	WindowsTextureGenerator();
	virtual ~WindowsTextureGenerator();

	Texture *generateTexture();
};

#endif /* CITYGENERATION_WINDOWSTEXTUREGENERATOR_H_ */
