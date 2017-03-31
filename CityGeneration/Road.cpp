/*
 * Road.cpp
 *
 *  Created on: Mar 29, 2017
 *      Author: Marc
 */

#include "Road.h"

Road::Road() {
	// TODO Auto-generated constructor stub

}

Road::Road(double l, double w, double x, double y, int d){
	length = l;
	width = w;
	origin_x = x;
	origin_y = y;
	direction = d;
}

Road::~Road() {
	// TODO Auto-generated destructor stub
}

