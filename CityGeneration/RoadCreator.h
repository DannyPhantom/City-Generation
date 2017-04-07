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

private:
	float medianWidth = 4.0;
	float roadWidth = 5.0;


};

#endif /* CITYGENERATION_ROADCREATOR_H_ */
