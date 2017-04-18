#include "Libraries/glew/glew.h"
#include "Libraries/freeglut/freeglut.h"
#include <math.h>
#include "Scene.h"
#include "DynamicRoadGeneration/DynamicRoadGenerator.h"
#include "DynamicRoadGeneration/Square.h"
#include "Camera.h"
#include "SceneParameters.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#define GLM_FORCE_RADIANS

DynamicRoadGenerator *g = NULL;
Scene *s = NULL;
bool closeProgram = false;
int lastFrameTime = 0;

void createScene() {
	std::vector<Square *> squares = g->getSquares();
	delete g;

	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	s = new Scene(squares);
	s->initializeScene();
}

/*
Main program loop.
Calculates the delta time that's been elapsed for the given frame,
calls the main scene method to process everything and draw
and show it to the screen
*/
void mainLoop(void) {
	//calculate dt
	float currentFrameTime = glutGet(GLUT_ELAPSED_TIME);
	float dt = currentFrameTime - lastFrameTime;
	lastFrameTime = currentFrameTime;

	//render the scene and do other relevant stuff
	if (s != NULL) {
		s->renderScene(dt / 1000.0);
	}
	else {
		if (g->isDone()) {
			createScene();
		}
		else {
			g->draw();
		}
	}

	//swap buffers
	glutSwapBuffers();

	//ask for another frame right away
	glutPostRedisplay();

	if (closeProgram) {
		glutLeaveMainLoop();
	}
}

/*
Method that is being called on any mouse move
(either active or passive)
@param x x position of the mouse
@param y y position of the mouse
*/
void mouseMoveAnyway(int x, int y) {
	//then we let the scene process the mouse movement
	//but before we transfer the mouse coordinate from
	//[0, width] and [0, height]
	//to
	//[-width/2, width/2] and [-height/2, height/2]
	//(which is later on transfered to [-1, 1])
	int halfWidth = SceneParameters::getScreenWidth() >> 1;
	int halfHeight = SceneParameters::getScreenHeight() >> 1;
	if (s != NULL) {
		s->getCamera()->processMouseMovement(x - halfWidth, y - halfHeight);
		//move the pointer to the center of the screen so that we don't have the mouse out there somewhere
		if (x != halfWidth || y != halfHeight) {
			glutWarpPointer(halfWidth, halfHeight);
		}
	}
	else {
		g->processMouseMovement((1.0f * x - halfWidth) / SceneParameters::getScreenWidth(), (1.0f * y - halfHeight) / SceneParameters::getScreenHeight());
	}

	glutPostRedisplay();
}

/*
Callback method for the active mouse movement
*/
void mouseMove(int x, int y) {
	mouseMoveAnyway(x, y);
}

/*
Callback method for the passive mouse movement
*/
void mouseMovePassive(int x, int y) {
	mouseMoveAnyway(x, y);
}

/*
Callback method for the mouse click
@param button button that was clicked
@param state either GLUT_DOWN or GLUT_UP
@param x x position of the click
@param y y position of the click
*/
void mouseClick(int button, int state, int x, int y) {
	if (s == NULL && state == GLUT_DOWN) {
		int halfWidth = SceneParameters::getScreenWidth() >> 1;
		int halfHeight = SceneParameters::getScreenHeight() >> 1;
		g->processMouseClick((1.0f * x - halfWidth) / SceneParameters::getScreenWidth(), (1.0f * y - halfHeight) / SceneParameters::getScreenHeight());
	}
}

/*
Callback function for any normal keyboard key press
@param key code of the key pressed
@param x x position of the mouse at the time of click
@param y y position of the mouse at the time of click
*/
void pressKey(unsigned char key, int x, int y) {
	if (s != NULL) {
		switch (key) {
			//move forward
		case 'w':
			s->getCamera()->setMoveCameraForward(true);
			break;
			//move backwards
		case 's':
			s->getCamera()->setMoveCameraBackward(true);
			break;
			//move left
		case 'a':
			s->getCamera()->setMoveCameraLeft(true);
			break;
			//move right
		case 'd':
			s->getCamera()->setMoveCameraRight(true);
			break;
			//export to obj
		case 'e':
			s->exportToObj();
			break;
		}
	}
	else {
		//enter
		if (key == 13) {
			g->stopCreating();
		//bakcspace
		} else if (key == 8) {
			g->processUndo();
		} else if (key == 'p') {
			g->setMode(DynamicRoadGenerator::MODE_ROAD_PLACEMENT);
		} else if (key == 'o') {
			g->setMode(DynamicRoadGenerator::MODE_DISABLING_SUBDIVISION);
		}
	}

	//exit the program (escape)
	if (key == 27) {
		closeProgram = true;
	}
}

/*
Callback function for any normal keyboard key release
@param key code of the key released
@param x x position of the mouse at the time of release
@param y y position of the mouse at the time of release
*/
void releaseKey(unsigned char key, int x, int y) {
	if (s != NULL) {
		switch (key) {
			//stop moving forward
		case 'w':
			s->getCamera()->setMoveCameraForward(false);
			break;
			//stop moving backwards
		case 's':
			s->getCamera()->setMoveCameraBackward(false);
			break;
			//stop moving left
		case 'a':
			s->getCamera()->setMoveCameraLeft(false);
			break;
			//stop moving right
		case 'd':
			s->getCamera()->setMoveCameraRight(false);
			break;
		}
	}
}

/*
Entry point.
Sets everything up
*/
int main(int argc, char **argv) {
	//initialize the scene parameters and
	//set the mouse mode to move
	SceneParameters::initialize();
	srand(time(NULL));

	//initialize the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(SceneParameters::getScreenWidth(), SceneParameters::getScreenHeight());
	glutCreateWindow("City Generation");

	//setup callbacks
	glutDisplayFunc(mainLoop);
	glutIdleFunc(mainLoop);

	glutKeyboardFunc(pressKey);
	glutKeyboardUpFunc(releaseKey);

	glutMotionFunc(mouseMove);
	glutPassiveMotionFunc(mouseMovePassive);
	glutMouseFunc(mouseClick);

	//initialize opengl functions
	glewInit();
	glEnable(GL_MULTISAMPLE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_DST_ALPHA);

	//initialize the scene
	g = new DynamicRoadGenerator();

	//start the main loop
	glutMainLoop();

	return 1;
}
