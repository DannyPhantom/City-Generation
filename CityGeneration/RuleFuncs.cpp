/*
 * RuleFuncs.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: marc.desorcy
 */

#include "RuleFuncs.h"

RuleFuncs::RuleFuncs() {
	// TODO Auto-generated constructor stub

}

RuleFuncs::~RuleFuncs() {
	// TODO Auto-generated destructor stub
}

Scope S(float x, float y, float z, Scope orig, std::string name)
{
	Scope sScope = orig;
	sScope.setName(name);
	sScope.setScale(glm::vec3(x, y, z));

	return sScope;
}

Scope T(float x, float y, float z, Scope orig, std::string name)
{
	Scope tScope = orig;
	tScope.setName(name);
	tScope.setTranslation(glm::vec3(x, y, z));

	return tScope;
}

Scope R(char axis, float angle, Scope orig, std::string name)
{
	Scope rScope = orig;
	rScope.setName(name);

	glm::vec3 normal;
	glm::mat4 rotation;

	if(axis == "x" || axis == "X")
	{
		normal = glm::vec3(1.0, 0.0, 0.0);
		rotation = glm::rotate(angle, normal);
	}
	else if(axis == "y" || axis == "Y")
	{
		normal = glm::vec3(0.0, 1.0, 0.0);
		rotation = glm::rotate(angle, normal);
	}
	else if(axis == "z" || axis == "Z")
	{
		normal = glm::vec3(0.0, 0.0, 1.0);
		rotation = glm::rotate(angle, normal);
	}
	else
	{
		std::cerr << "ERROR: Bad input. R does not contain a valid axis\n";
		normal = glm::vec3(0.0, 0.0, 0.0);
		rotation = glm::mat4();
	}

	rScope.setRotation(rotation);
}
