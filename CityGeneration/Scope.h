/*
 * Scope.h
 *
 *  Created on: Mar 24, 2017
 *      Author: bemayer
 */

#ifndef CITYGENERATION_SCOPE_H_
#define CITYGENERATION_SCOPE_H_

#include "Libraries/glm/glm.hpp"


#include <string>

using namespace std;
using namespace glm;

class Scope {
public:
	Scope();
	Scope(vec3 _translation, vec3 _rotation, vec3 _scale, string _name);

	virtual ~Scope();

	void setTranslation(vec3 _translation);
	vec3 getTranslation();

	void setRotation(vec3 _rotation);
	vec3 getRotation();

	void setScale(vec3 _scale);
	vec3 getScale();


	void setName(string _name);
	string getName();
private:
	string name;
	vec3 translation;
	vec3 rotation;
	vec3 scale;
};

#endif /* CITYGENERATION_SCOPE_H_ */
