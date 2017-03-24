/*
 * Tree.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: bemayer
 */

#include "Tree.h"

Tree::Tree() {
	// TODO Auto-generated constructor stub

}

Tree::~Tree() {
	// TODO Auto-generated destructor stub
}

vector<TreeObject*> Tree::getLeafes()
{
	vector<TreeObject*> children = root->getChildren();
	for (auto child : children)
	{

	}

}
