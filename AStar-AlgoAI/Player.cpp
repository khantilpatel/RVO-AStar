#include "Player.h"
#include "GameWorld.h"
#include <iostream>

//namespace model{

	Player::Player(glm::vec3 loc, glm::vec3 m_direction){
		this->m_pCurrent_location = new ds::CubeGeomerty(loc);
		this->direction = m_direction;
	}

	void Player::renderPlayer() // Assume you have all the vertices of polygon and the color
	{
		glBegin(GL_QUADS); 		
		ds::CubeGeomerty currentLocation = (m_map[static_cast<int>((*m_pCurrent_location).location.x)][static_cast<int>((*m_pCurrent_location).location.y)]).getCubeCoordinates();
		glColor3f(1.0f, 1.0f, 1.0f);//(*m_pCurrent_location).getCubeColor().x, (*m_pCurrent_location).getCubeColor().y ,(*m_pCurrent_location).getCubeColor().z); // Red			
		glVertex2f(currentLocation.a.x, currentLocation.a.y);     // Define vertices in counter-clockwise (CCW) order
		glVertex2f(currentLocation.b.x, currentLocation.b.y);     //  so that the normal (front-face) is facing you
		glVertex2f(currentLocation.c.x, currentLocation.c.y);
		glVertex2f(currentLocation.d.x, currentLocation.d.y);

		glEnd();		

		int height = (int)currentLocation.d.y - (int)currentLocation.a.y;
		int width  = (int)currentLocation.b.x - (int)currentLocation.a.x;

		// Generate Center points
		int x_dir_center = (int)currentLocation.a.x + 0.5 * width;
		int y_dir_center = (int)currentLocation.a.y + 0.5 * height;
		
		int x_dir_pt = 0;
		int y_dir_pt = 0;

		int x_dir = (int)direction.x;
		int y_dir = (int)direction.y;

		// Generate middle point on line in direction
		if(x_dir == 0 && y_dir == 1)
		{
			x_dir_pt = x_dir_center;
			y_dir_pt = y_dir_center + 0.5 * height;
		}

		if(x_dir == 0 && y_dir == -1)
		{
			x_dir_pt = x_dir_center;
			y_dir_pt = y_dir_center - 0.5 * height;
		}

		if(x_dir == 1 && y_dir == 0)
		{
			x_dir_pt = x_dir_center + 0.5 * width;
			y_dir_pt = y_dir_center;
		}

		if(x_dir == -1 && y_dir == 0)
		{
			x_dir_pt = x_dir_center - 0.5 * width;
			y_dir_pt = y_dir_center;
		}

		//Draw line
		glLineWidth(2.5);
	
		glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(x_dir_center, y_dir_center, 0.0);
		glVertex3f(x_dir_pt, y_dir_pt, 0.0);
		glEnd();


	}

	void Player::move_right(){
		//ds::CubeGeomerty currentLocation = *m_pCurrent_location;

		if(_GRID_RESOLUTION_X_AXIS > m_pCurrent_location->location.x +1)
		{
			m_pCurrent_location->location.x = m_pCurrent_location->location.x + 1;
		}
	}

	void Player::move_left(){
		

		if(0 <= m_pCurrent_location->location.x -1)
		{
			m_pCurrent_location->location.x = m_pCurrent_location->location.x - 1;
		}
	}

	void Player::move_up(){
		

		if(_GRID_RESOLUTION_Y_AXIS > m_pCurrent_location->location.y +1)
		{
			m_pCurrent_location->location.y = m_pCurrent_location->location.y + 1;
		}
	}

	void Player::move_down(){


		if(0 <= m_pCurrent_location->location.y -1)
		{
			m_pCurrent_location->location.y = m_pCurrent_location->location.y - 1;
		}
	
	}
//}