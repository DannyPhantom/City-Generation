/*
 * Tree.h
 *
 *  Created on: Mar 24, 2017
 *      Author: bemayer
 */

#ifndef CITYGENERATION_TREE_H_
#define CITYGENERATION_TREE_H_

#include <string>
#include "TreeObject.h"

class Tree {
public:
	Tree(TreeObject* _root);
	virtual ~Tree();

	vector<TreeObject*> getLeafes();
	vector<TreeObject*> getLeafesByName(string name);
private:
	TreeObject* root;


};

#endif /* CITYGENERATION_TREE_H_ */
