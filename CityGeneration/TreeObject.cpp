/*
 * TreeObject.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: bemayer
 */

#include "TreeObject.h"

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
