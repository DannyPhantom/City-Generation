/*
 * Tree.h
 *
 *  Created on: Mar 24, 2017
 *      Author: bemayer
 */

#ifndef CITYGENERATION_TREE_H_
#define CITYGENERATION_TREE_H_

#include "TreeObject.h"

class Tree {
public:
	Tree();
	virtual ~Tree();

	vector<TreeObject*> getLeafes();
private:
	TreeObject* root;


};

#endif /* CITYGENERATION_TREE_H_ */
