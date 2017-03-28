#pragma once

#include "Libraries/glew/glew.h"

/*
	Represents a simple 2D Quad
	that is drawn to the screen
	(this is done fullscreen).
	This class has to be surrounded with the glUseProgram call,
	as well as any other calls as desired (i.e. texture attachements, etc.)
	The only requirement is that the shader has to use vertices as in location=0,
	and uv's have to be in location=1
*/
class Quad2D
{
public:
	Quad2D();
	~Quad2D();

	/*
		Issues a draw call
	*/
	void draw();
private:

	/*
		Generates VBO's and VAO
	*/
	void create();

	GLuint vao;
};
