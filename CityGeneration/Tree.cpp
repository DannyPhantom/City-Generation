/*
 * Tree.cpp
 *
 *  Created on: Mar 24, 2017
 *      Author: bemayer
 */

#include "Tree.h"

Tree::Tree(TreeObject* _root) {
	// TODO Auto-generated constructor stub
	root = _root;
}

Tree::~Tree() {
	// TODO Auto-generated destructor stub
}


//This is a pretty standard implementation
//Of a getting Leaves on a tree when
//the the tree has multiple children
vector<TreeObject*> Tree::getLeafes()
{
	if (root->isLeaf)
	{
		vector<TreeObject*> emptyLeaves;
		return emptyLeaves;
	}
	//Hanging else case
	//This code will handle the case that the tree has children

	vector<TreeObject*> children = root->getChildren();
	vector<TreeObject*> leaves;
	for (auto child : children)
	{
		if (child->isLeaf)
		{
			leaves.push_back(child);
		} else {
			Tree childTree = Tree(child);

			vector<TreeObject*> childLeaves = childTree.getLeafes();

			leaves.insert(leaves.end(), childLeaves.begin(), childLeaves.end());
		}
	}

	return leaves;

}

vector<TreeObject*> Tree::getLeafesByName(string name)
{
	vector<TreeObject*> leaves = getLeafes();
	vector<TreeObject*> leavesByName;
	for (auto leaf:leaves)
	{
		string name_leaf = leaf->getScopeName();
		if (name.compare(name_leaf) == 0)
		{
			leavesByName.push_back(leaf);
		}
	}

	return leavesByName;
}
