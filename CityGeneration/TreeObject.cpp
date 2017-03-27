/*
 * TreeObject.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: bemayer
 */

#include "TreeObject.h"

TreeObject::TreeObject(Scope _scope)
{
	description = _scope;
}

TreeObject::TreeObject() {
	// TODO Auto-generated constructor stub

}

TreeObject::~TreeObject() {
	// TODO Auto-generated destructor stub
}

void TreeObject::addChild(TreeObject* objectToAdd)
{
	isLeaf = false;
	children.push_back(objectToAdd);
}

vector<TreeObject*> TreeObject::getChildren()
{
	return children;
}

void TreeObject::addChildren(vector<Scope> scopes)
{

	for (auto scope:scopes)
	{
		TreeObject* child = new TreeObject(scope);
		children.push_back(child);
	}


}

string TreeObject::getScopeName()
{
	return description.getName();
}

Scope TreeObject::getScope()
{
	return description;
}
