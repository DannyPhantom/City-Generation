/*
 * RoadCreator.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: bemayer
 */

#include "RoadCreator.h"

RoadCreator::RoadCreator() {
	// TODO Auto-generated constructor stub

}

RoadCreator::~RoadCreator() {
	// TODO Auto-generated destructor stub
}


//This method will take in a list of roads
//and then will divide them up so that there is
//a main median
//and lanes if needed
void RoadCreator::makeRenderableRoads(vector<Road*> roads)
{


	for (Road* road:roads)
	{

		int numOfRoads = round(road->width/roadWidth);



		vec3 origin = vec3(road->origin_x, 1.0, road->origin_y);


		//make the middle divider
		vec3 p1 = origin + (0.5f) * (vec3(road->width, 0, 0)) - vec3(medianWidth, 0, 0);
		vec3 p2 = origin + (0.5f) * (vec3(road->width, 0, 0)) + vec3(medianWidth, 0, 0);
		vec3 p3 = p2 + vec3(road->length, 0, 0);
		vec3 p4 = p1;
		vec3 p5 = p3;
		vec3 p6 = p3 - vec3(medianWidth, 0, 0);

		vector<vec3> vertices;

		vertices.push_back(p1);
		vertices.push_back(p2);
		vertices.push_back(p3);
		vertices.push_back(p4);
		vertices.push_back(p5);
		vertices.push_back(p6);


		vector<vec3> normals;
		vector<vec2> uvs;
		vector<vec4> colors;
		vector<GLuint> indices;
		//hard coded to make quads
		for (int i = 0; i < 6; i++)
		{
			normals.push_back(vec3(0, 1, 0));
			uvs.push_back(vec2(0, 0));
			colors.push_back(vec4(0, 0, 1, 1));
			indices.push_back(i);
		}

		Mesh *dividerMesh = new Mesh(vertices, uvs, colors, normals, indices, NULL, 2);
		addMesh(dividerMesh);



	}
	setupVBOs();
	setupVAOs();


}
