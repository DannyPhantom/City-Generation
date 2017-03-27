/*
 * Scope.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: bemayer
 */

#include "Scope.h"

Scope::Scope()
{
	// TODO Auto-generated constructor stub
	 rotation = vec3(0, 0, 0);
	 translation = vec3(0, 0, 0);
	 scale = vec3(0, 0, 0);
}

Scope::~Scope() {
	// TODO Auto-generated destructor stub
}

void Scope::setTranslation(vec3 _translation)
{
	translation = _translation;
}

vec3 Scope::getTranslation()
{
	return translation;
}

void Scope::setRotation(vec3 _rotation)
{
	rotation = _rotation;
}

vec3 Scope::getRotation()
{
	return rotation;
}

void Scope::setScale(vec3 _scale)
{
	scale = _scale;
}

Scope::Scope(vec3 _translation, vec3 _rotation, vec3 _scale, string _name)
{
	translation = _translation;
	rotation = _rotation;
	scale = _scale;
	name = _name;
}

vec3 Scope::getScale()
{
	return scale;
}

void Scope::setName(string _name)
{
	name = _name;
}

string Scope::getName()
{
	return name;
}
