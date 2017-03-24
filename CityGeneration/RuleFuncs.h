/*
 * RuleFuncs.h
 *
 *  Created on: Mar 24, 2017
 *      Author: marc.desorcy
 */

#ifndef CITYGENERATION_RULEFUNCS_H_
#define CITYGENERATION_RULEFUNCS_H_

/*NOTICE: Make new class!!! (call it whatever)
 * Create functions for S(), T() Comp(), Subdiv(), Repeat(), and R()
 * S() - Takes a scope, returns a copy of the scope with the given size.
 *       Scope will be a class (Bernie's working on it). Has rotation, translation, scale
 * T() - Sets translation vector on scope.
 * R() - Sets rotation as vectors on scope (only doing one axis).
 * 		- Make sure to have a parameter to specify WHICH axis
 * Comp(type, param){A|B|...|Z} - Will be tough. Given a scope, create more scopes out of it.
 * 		Each Scope is a 2Dplane. EG: If type=='sidefaces', then generate four different scopes,
 * 		each is a 2D-plane with the parameters (x, y, 0). Some will have a rotation factor applied.
 * 		A translation factor, too.
 * 		Will also deal with faces, edges. (Ignore vertices for now)
 * 	Subdiv() - take an axis, a vector of values, and a vector of names. Return a vector of
 * 			scopes, one per name. This subdivides the scope into different parts with their own names.
 * 			This should also be able to deal with double-axes (like XY, XZ), but ignore this for nwo.
 * 	Repeat() - Takes the axis of a 2D-plane, a value (eg. window-spacing), and a number n.
 * 				n = 2D-plane's length along the axis/value. This subdivides the scope into
 * 				n scopes, all with the same name and size.
 * 				Warning: there's a chance length/window_spacing is not an integer. In this case:
 * 				take length/window_spacing, round the answer, take length/(rounded_answer), get new_window_spacing
 * 				Use the new spacing.
 *
 * 	REMEMBER: Comp, Subdiv and Repeat need to take a list of new scope names as parameters, then return
 * 	scopes with those names.
 *
 *
 *
 * */

#include Scope.h

class RuleFuncs {
public:
	RuleFuncs();
	virtual ~RuleFuncs();

	Scope S(float x, float y, float z, Scope orig, std::string name);
	Scope T(float x, float y, float z, Scope orig, std::string name);
	Scope R(float x, float y, float z, Scope orig, std::string name);

	std::vector<Scope> Comp(std::string type, Scope orig, std::vector<std::string> names);
	std::vector<Scope> Subdiv(char axis, std::vector<float> sizes, Scope orig, std::vector<std::string> names);
	std::vector<Scope> Repeat(char axis, int num_of_els, std::string name);
};

#endif /* CITYGENERATION_RULEFUNCS_H_ */
