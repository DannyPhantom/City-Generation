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
	int numRoads;


	for (Road* road:roads)
	{

		int numOfRoads = round(road->width/roadWidth);

		printf("Num of Roads is %i \n", numOfRoads);



		vec3 origin = vec3(road->origin_x, 0.0, road->origin_y);





		vec3 p1, p2, p3, p4, p5 , p6;

		if (road->direction == 1)
		{

		 p1 = origin;
		 p2 = origin + vec3(medianWidth, 0, 0);
		 p3 = p2 + vec3(0, 0, road->length);

		 p4 = p1;
		 p5 = p3;
		 p6 = p5 - vec3(medianWidth, 0, 0);
		} else {

			 p1 = origin;
			 p2 = origin + vec3(0, 0, -medianWidth);
			 p3 = p2 + vec3(road->length, 0, 0);

			 p4 = p1;
			 p5 = p3;
			 p6 = p5 - vec3(0, 0, -medianWidth);

		}

		//make the middle divider
		/*
		vec3 p1 = origin + (0.5f) * (vec3(road->width, 0, 0)) - vec3(medianWidth, 0, 0);
		vec3 p2 = origin + (0.5f) * (vec3(road->width, 0, 0)) + vec3(medianWidth, 0, 0);
		vec3 p3 = p2 + vec3(road->length, 0, 0);
		vec3 p4 = p1;
		vec3 p5 = p3;
		vec3 p6 = p3 - vec3(medianWidth, 0, 0);
		*/
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
		for (int i = 0; i < vertices.size(); i++)
		{
			normals.push_back(vec3(0, 1, 0));
			uvs.push_back(vec2(0, 0));
			colors.push_back(vec4(0, 0, 1, 1));
			indices.push_back(i);
		}

		Mesh *dividerMesh = new Mesh(vertices, uvs, colors, normals, indices, NULL, 1);
		addMesh(dividerMesh);
		numRoads++;
		//cout <<"Made a renderable road \n";


	}

	printf("Made %i renderable roads\n", numRoads);
	setupVBOs();
	setupVAOs();


}
