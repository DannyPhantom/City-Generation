/*
 * Road.h
 *
 *  Created on: Mar 29, 2017
 *      Author: Marc DeSorcy
 */

#ifndef CITYGENERATION_ROAD_H_
#define CITYGENERATION_ROAD_H_

#define _X 1
#define _Y 2

/*
 * How to pass grid information for plotting buildings:
 * For each subgrid at the lowest level;
 * 	pass info about origin location, length, and width
 * 	...that should literally be it. Easy, huh?
 *
 */

class Road {
public:
	Road();
	Road(double l, double w, double x, double y, int d);
	virtual ~Road();
private:
	double length;
	double width;
	double origin_x;
	double origin_y;
	int direction;


	//Optional - endpoints for x and y.

	/*How to store roads?
	 * 1)*/

};

#endif /* CITYGENERATION_ROAD_H_ */
