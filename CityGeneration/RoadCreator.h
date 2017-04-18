/*
 * RoadCreator.h
 *
 *  Created on: Apr 6, 2017
 *      Author: bemayer
 */

#ifndef CITYGENERATION_ROADCREATOR_H_
#define CITYGENERATION_ROADCREATOR_H_

#include <vector>;
#include "Road.h"
#include "math.h"
#include "SceneObject.h"
#include "Libraries/glm/glm.hpp"


using namespace std;
using namespace glm;

class RoadCreator : public SceneObject {
public:
	RoadCreator();
	virtual ~RoadCreator();


	void makeRenderableRoads(vector<Road*> roads);
	void makeRoadMesh(vector<vec3> vertices, vec3 color);
	void setMedianColor(glm::vec3 color) { medianColor = color; }

private:
	float medianWidth = 0.5;
	float roadWidth = 5.0;

	glm::vec3 medianColor;
};

#endif /* CITYGENERATION_ROADCREATOR_H_ */
