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
	float* getWindowIntensities();

public:
	WindowsTextureGenerator();
	virtual ~WindowsTextureGenerator();

	Texture *generateTexture();


	const int textureDimensions = 512;
	static const int numOfWindows = 64;
};

#endif /* CITYGENERATION_WINDOWSTEXTUREGENERATOR_H_ */
