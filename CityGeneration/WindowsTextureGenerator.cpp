/*
 * WindowsTextureGenerator.cpp
 *
 *  Created on: Mar 27, 2017
 *      Author: dannyphantom
 */

#include "WindowsTextureGenerator.h"
#include "Quad2D.h"
#include <iostream>
#include <math.h>
#include "Randomizer.h"

WindowsTextureGenerator::WindowsTextureGenerator() {
}

WindowsTextureGenerator::~WindowsTextureGenerator() {

}

float* WindowsTextureGenerator::getWindowIntensities() {
	float** intensities = new float*[textureDimensions];
	for (int i=0; i<textureDimensions; i++) {
		intensities[i] = new float[textureDimensions];
	}

	int pixelsPerWindow = (int)(textureDimensions / numOfWindows);

	for (int windowX = 0; windowX < numOfWindows; windowX++) {
		for (int windowY = 0; windowY < numOfWindows; windowY++) {
			float windowIntensity = Randomizer::getRandomFloat(0.0f, 1.0f);
			windowIntensity = pow(windowIntensity, 5);

			int fadePoint = Randomizer::getRandomInt(0, pixelsPerWindow);
			int fadePixels = pixelsPerWindow - fadePoint;
			for (int i=0; i<pixelsPerWindow; i++) {
				for (int j=0; j<pixelsPerWindow; j++) {
					if (i == 0 || j == 0 || i == pixelsPerWindow - 1 || j == pixelsPerWindow - 1) {
						intensities[windowY * pixelsPerWindow + i][windowX * pixelsPerWindow + j] = 0;
					} else {
						float fade = 1.0f;
						if (i > fadePoint) {
							fade = (1.5 * fadePixels - i) / (fadePixels * 1.5);
							fade = pow(fade, 2);
						}
						intensities[windowY * pixelsPerWindow + i][windowX * pixelsPerWindow + j] = windowIntensity * fade;
					}
				}
			}
		}
	}

	float *intensitiesInOneRow = new float[textureDimensions * textureDimensions * 3];
	for (int i = 0; i < textureDimensions; i++) {
		for (int j = 0; j < textureDimensions; j++) {
			int index = (i * textureDimensions + j) * 3;
			intensitiesInOneRow[index] = intensities[i][j];
			intensitiesInOneRow[index+1] = intensities[i][j];
			intensitiesInOneRow[index+2] = intensities[i][j];
		}
	}

	for (int i=0; i<textureDimensions; i++) {
		delete[] intensities[i];
	}
	delete[] intensities;

	return intensitiesInOneRow;
}

Texture *WindowsTextureGenerator::generateTexture() {

	float* windowIntensities = getWindowIntensities();

	//Create the texture
	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//texture is stored as a simple RGB thingy (values are from 0 to 1 in R^3)
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureDimensions, textureDimensions, 0, GL_RGB, GL_FLOAT, windowIntensities);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	Texture *text = new Texture(GL_TEXTURE_2D, texture);

	return text;
}

