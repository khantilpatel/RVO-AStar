
#pragma once

#include <vector>
#include <glm/glm.hpp>
#include "CubeGeometry.h"
#include "Node.h"
#include <glut/glut.h>

//namespace model{
	class Player{
	private:
		
	public:
		ds::CubeGeomerty * m_pCurrent_location;
		//Constructor ***********************************************
		Player();
		Player(glm::vec3, glm::vec3); // Initialize player with its starting location;

		// Helper Methods*********************************************

		void move_right();
		void move_left();
		void move_up();
		void move_down();
		glm::vec3 direction;
		void renderPlayer();
	};
//}