/*
 * TreeObject.h
 *
 *  Created on: Mar 24, 2017
 *      Author: bemayer
 */

#ifndef CITYGENERATION_TREEOBJECT_H_
#define CITYGENERATION_TREEOBJECT_H_

#include <string>
#include <vector>

#include "Scope.h"

class TreeObject {
public:
	TreeObject();
	virtual ~TreeObject();

	void addChild(TreeObject* objectToAdd);
	vector<TreeObject *> getChildren();

private:
	bool isLeaf = true;
	string name;
	Scope description;
	vector<TreeObject*> children;
};

#endif /* CITYGENERATION_TREEOBJECT_H_ */
