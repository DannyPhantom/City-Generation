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

/*
 *  * Comp(type, param){A|B|...|Z} - Will be tough. Given a scope, create more scopes out of it.
 * 		Each Scope is a 2Dplane. EG: If type=='sidefaces', then generate four different scopes,
 * 		each is a 2D-plane with the parameters (x, y, 0). Some will have a rotation factor applied.
 * 		A translation factor, too.
 * 		Will also deal with faces, edges. (Ignore vertices for now)
 */
std::vector<Scope> Comp(std::string type, Scope orig, std::vector<std::string> names)
{
	/*Will only implement sidefaces, sideedges and topedges for now*/

	std::vector<Scope> outputScopes;

	if(type == "sidefaces")
	{
		/*
		 * 1) Create 4 faces, one for each side. Two will likely be (x, y, 0), the other two (0, y, z)
		 * 2) Translate the faces to the proper areas
		 */

		vec3 sideFaceSize = vec3(0.0f, orig.getScale().y, orig.getScale().z);
		vec3 frontFaceSize = vec3(orig.getScale().x, orig.getScale().y, 0.0f);

		float side_length = orig.getScale().z;
		float front_width = orig.getScale().x;

		Scope leftFace(orig.getTranslation()-(front_width/2.0f), orig.getRotation(), sideFaceSize);
		Scope rightFace(orig.getTranslation()+(front_width/2.0f), orig.getRotation(), sideFaceSize);
		Scope frontFace(orig.getTranslation()-(side_length/2.0f), orig.getRotation(), frontFaceSize);
		Scope backFace(orig.getTranslation()+(side_length/2.0f), orig.getRotation(), frontFaceSize);

		for(int i = 0; i < names.size(); i++)
		{
			frontFace.setName(names[i]);
			leftFace.setName(names[i]);
			backFace.setName(names[i]);
			rightFace.setName(names[i]);

			outputScopes.push_back(frontFace);
			outputScopes.push_back(leftFace);
			outputScopes.push_back(rightFace);
			outputScopes.push_back(backFace);
		}
	}
	else if (type == "sideedges")
	{

	}
}

/*take an axis, a vector of values, and a vector of names. Return a vector of
 * 			scopes, one per name. This subdivides the scope into different parts with their own names.
 * 			This should also be able to deal with double-axes (like XY, XZ), but ignore this for nwo.*/

std::vector<Scope> Subdiv(char axis, std::vector<float> sizes, Scope orig, std::vector<std::string> names)
{
	std::vector<Scope> subdivided;
	float totalSize = 0.0f;
	float lastSize = 0.0f;

	if(axis == "x" || axis == "X")
	{
		totalSize = 0.0f;
		lastSize = 0.0f;
		for(int i = 0; i < names.size(); i++)
		{
			for(int j = 0; j < sizes.size(); j++)
			{
				glm::vec3 dimensions = glm::vec3(sizes[j], orig.getScale().y, orig.getScale().z);
				totalSize += sizes[i];

				//Note: The following assumes that the translation does NOT have the coordinates centered. Need to rework if they are
				glm::vec3 position = glm::vec3(orig.getTranslation().x + lastSize, orig.getTranslation().y, orig.getTranslation().z);
				Scope subScope(position, orig.getRotation(), dimensions);

				subScope.setName(names[i]);

				subdivided.push_back(subScope);
				lastSize += sizes[j];
			}
		}
	}
	else if(axis == "y" || axis == "Y")
	{
		totalSize = 0.0f;
		lastSize = 0.0f;
		for (int i = 0; i < names.size(); i++)
		{
			for(int j = 0; j < sizes.size(); j++)
			{
				glm::vec3 dimensions = glm::vec3(orig.getScale().x, sizes[j], orig.getScale().z);
				totalSize += sizes[j];

				//Note: The following assumes that the translation does NOT have the coordinates centered. Need to rework if they are
				glm::vec3 position = glm::vec3(orig.getTranslation().x, orig.getTranslation().y + lastSize, orig.getTranslation().z);
				Scope subScope(position, orig.getRotation(), dimensions);

				subScope.setName(names[i]);

				subdivided.push_back(subScope);
				lastSize += sizes[j];
			}
		}
	}
	else if(axis == "z" || axis == "Z")
	{
		totalSize = 0.0f;
		lastSize = 0.0f;
		for(int i = 0; i < names.size(); i++)
		{
			for(int j = 0; j < sizes.size(); j++)
			{
				glm::vec3 dimensions = glm::vec3(orig.getScale().x, orig.getScale().y, sizes[j]);
				totalSize += sizes[j];

				//Note: The following assumes that the translation does NOT have the coordinates centered. Need to rework if they are
				glm::vec3 position = glm::vec3(orig.getTranslation().x, orig.getTranslation().y, orig.getTranslation().z + lastSize);
				Scope subScope(position, orig.getRotation(), dimensions);

				subScope.setName(names[i]);

				subdivided.push_back(subScope);
				lastSize += sizes[j];
			}
		}
	}
	else
	{
		std::cerr << "ERROR: Bad input. R does not contain a valid axis\n";
	}
	return subdivided;
}

/*
 * Takes the axis of a 2D-plane, a value (eg. window-spacing), and a number n.
 * 			n = 2D-plane's length along the axis/value. This subdivides the scope into
 * 			n scopes, all with the same name and size.
 * 			Warning: there's a chance length/window_spacing is not an integer. In this case:
 * 			take length/window_spacing, round the answer, take length/(rounded_answer), get new_window_spacing
 * 			Use the new spacing.
 */
std::vector<Scope> Repeat(char axis, int spacing, Scope orig, std::string name)
{
	std::vector<Scope> split;

	float n;
	float n2;
	float modded_spacing;

	std::vector<float> sizes;
	std::vector<std::string> names;

	if(axis == "x" || axis == "X")
	{
		n = orig.getScale().x/spacing;
		n2 = ceil(n);

		modded_spacing = orig.getScale().x/n2;
	}
	else if(axis == "y" || axis == "Y")
	{
		n = orig.getScale().y/spacing;
		n2 = ceil(n);

		modded_spacing = orig.getScale().y/n2;
	}
	else if(axis == "z" || axis == "Z")
	{
		n = orig.getScale().z/spacing;
		n2 = ceil(n);

		modded_spacing = orig.getScale().z/n2;
	}

	for (int i = 0; i++; i < n2)
	{
		sizes.push_back(modded_spacing);
		names.push_back(name);
	}

	split = Subdiv(axis, sizes, orig, names);
}


