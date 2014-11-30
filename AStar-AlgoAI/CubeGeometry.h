
#pragma once
#include <vector>
#include <glm/glm.hpp>

namespace ds{

class CubeGeomerty{
	private:
		glm::vec4 color;		

	public:
		// The four vertices of the block to be drawn
		glm::vec3 a;
		glm::vec3 b;
		glm::vec3 c;
		glm::vec3 d;
		glm::vec3 center;
		float proximity;
		glm::vec3 location; // Actual location on the Grid
		//glm::vec3& asPtr;
		glm::vec3 direction; // Actual direction of the player
		//glm::vec4 getCubeColor();
	//	void setCubeColor(glm::vec4);
	
		CubeGeomerty();
		CubeGeomerty::CubeGeomerty(glm::vec3);
		CubeGeomerty::CubeGeomerty(glm::vec3, glm::vec3);
		CubeGeomerty(glm::vec3, glm::vec3, glm::vec3, glm::vec3, glm::vec3, float, glm::vec3);

	};

}