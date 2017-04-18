/*
 * RoadCreator.cpp
 *
 *  Created on: Apr 6, 2017
 *      Author: bemayer
 */

#include "RoadCreator.h"

RoadCreator::RoadCreator() {
	// TODO Auto-generated constructor stub
	medianColor = glm::vec3(0, 0, 1);
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
	//printf("roads is of %i \n", roads.size());
	int numRoads;


	for (Road* road:roads)
	{

		int numOfLanes = round(road->width/roadWidth);





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


		if (numOfLanes > 3 )
		{
			//printf("Making some multi laners \n");
			if (numOfLanes % 2 != 0)
			{
				numOfLanes += 1;
			}
			//if we have more than 3 roads we should subdivide so that we have divider roads

			int j = 0;
			vec3 movingOrigin = vec3(road->origin_x - road->width/2.0, 0.0, road->origin_y);
			vec3 step = vec3(road->width/((float) numOfLanes), 0, 0);

			if (road->direction == 1) {
			for (j = 0; j < (numOfLanes - 1); j++)
			{

				movingOrigin += step;
				if ( j != (numOfLanes/2 - 1) ) {
				vec3 newP1, newP2, newP3, newP4, newP5, newP6;
//				/movingOrigin += step;

				newP1 = movingOrigin;
				newP2 = movingOrigin + vec3(medianWidth, 0, 0);
				newP3 = newP2 + vec3(0, 0, road->length);

				newP4 = newP1;
				newP5 = newP3;
				newP6 = newP5 - vec3(medianWidth, 0, 0);

				 vector<vec3> vertices;

				 vertices.push_back(newP1);
				 vertices.push_back(newP2);
				 vertices.push_back(newP3);
				 vertices.push_back(newP4);
				 vertices.push_back(newP5);
				 vertices.push_back(newP6);

				 makeRoadMesh(vertices, vec3(1, 1, 1 ));
				}

			}
			} else {

				movingOrigin = vec3(road->origin_x  , 0.0, road->origin_y - road->width/2.0 );
				///movingOrigin = vec3(road->origin_x + road->width/2.0, 0,0);
				step = vec3(0, 0, road->width/((float) numOfLanes));

				for (j = 0; j < (numOfLanes - 1) ; j++)
				{
					//movingOrigin += step;
					movingOrigin += step;
					if (j != (numOfLanes/2 - 1)) {
					vec3 newP1, newP2, newP3, newP4, newP5, newP6;


					newP1 = movingOrigin;
					newP2 = movingOrigin + vec3(0, 0, -medianWidth);
					newP3 = newP2 + vec3(road->length, 0, 0);

					newP4 = newP1;
					newP5 = newP3;
					newP6 = newP5 - vec3(0, 0, -medianWidth);

					 vector<vec3> vertices;

					 vertices.push_back(newP1);
					 vertices.push_back(newP2);
					 vertices.push_back(newP3);
					 vertices.push_back(newP4);
					 vertices.push_back(newP5);
					 vertices.push_back(newP6);

					 makeRoadMesh(vertices, vec3(1, 1, 1 ));
					}
				}
			}

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

		makeRoadMesh(vertices, medianColor);
		/*
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
		*/
		//numRoads++;
		//cout <<"Made a renderable road \n";


	}

	//printf("Made %i renderable roads\n", numRoads);
	setupVBOs();
	setupVAOs();


}

void RoadCreator::makeRoadMesh(vector<vec3> vertices, vec3 color)
{

	vector<vec3> normals;
	vector<vec2> uvs;
	vector<vec4> colors;
	vector<GLuint> indices;
	//hard coded to make quads
	for (int i = 0; i < vertices.size(); i++)
	{
		normals.push_back(vec3(0, 1, 0));
		uvs.push_back(vec2(0, 0));
		colors.push_back(vec4(color, 1));
		indices.push_back(i);
	}

	Mesh *dividerMesh = new Mesh(vertices, uvs, colors, normals, indices, NULL, 1);
	addMesh(dividerMesh);
}
