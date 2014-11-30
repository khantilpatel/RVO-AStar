#include "Agent.h"
#include "GameWorld.h"
#include "PositioningSystem.h"
#include "AggresivePositioningSystem.h"
#include "DefensivePositioningSystem.h"
#include "StrategicPositioningSystem.h"
//#include "math_functions.h"
#include "SpatialHashing.h"
#include "ROVNavigationSystem.h"

#include <iostream>
	//class PositioningSystem;
	Agent::Agent(int m_agent_id,ds::CubeGeomerty& loc , ds::CubeGeomerty& target, glm::vec3 m_direction, glm::vec3 color, float velocity,float m_pradius, ROVNavigationSystem* m_pROVNavigationSystem)
	{
		//ds::Node n = m_map[static_cast<int>(loc.x)][static_cast<int>(loc.y)];
		m_pCurrent_location = &loc;
		m_pCurrent_location_value = loc;
		m_Agent_Action = NOTHING;
		draw_color = color;
		direction = m_direction;
		m_Position_system = new PositioningSystem(this);
		m_Position_System_Aggresive = new AggresivePositioningSystem(this);
		m_Position_System_Defensive = new DefensivePositioningSystem(this);
		m_Strategic_System_Defensive = new StrategicPositioningSystem(this);

		m_ROVNavigationSystem = m_pROVNavigationSystem; 
		m_Current_velocity = velocity; //meter per sec

		m_Current_position_coordinate = loc.center;
	
		agent_id = m_agent_id;
	
		m_pCurrent_Move_target = &target;
		m_pCurrent_Move_target_value = target;
		m_Current_velocity_vector = glm::vec2(0.0f,0.0f);
		m_radius = m_pradius;
	}
	/*
	* Function that handles the drawing of a circle using the line loop
	* method. This will create a hollow circle.
	*
	* Params:
	* x (GLFloat) - the x position of the center point of the circle
	* y (GLFloat) - the y position of the center point of the circle
	* radius (GLFloat) - the radius that the painted circle will have
	*/
	void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius){
		int i;
		int lineAmount = 100; //# of triangles used to draw circle
		//GLfloat radius = 0.8f; //radius
		GLfloat twicePi = 2.0f * 3.14159;
		glBegin(GL_LINE_LOOP);

		for (i = 0; i <= lineAmount; i++) {
			glVertex2f(
				x + (radius * cos(i * twicePi / lineAmount)),
				y + (radius* sin(i * twicePi / lineAmount))
				);
		}
		glEnd();
	}

	void Agent::drawAgent() // Assume you have all the vertices of polygon and the color
	{
		//glBegin(GL_QUADS); 
		//CubeGeomerty drawPolygon = (m_map[static_cast<int>((*m_pCurrent_location).location.x)][static_cast<int>((*m_pCurrent_location).location.y)]).getCubeCoordinates();
	
	//	glColor3f(nodeCoordinates.getCubeColor().x, nodeCoordinates.getCubeColor().y ,nodeCoordinates.getCubeColor().z); // Red			
		glColor3f(draw_color.x,draw_color.y,draw_color.z);
		//glVertex2f(drawPolygon.a.x, drawPolygon.a.y);     // Define vertices in counter-clockwise (CCW) order
		//glVertex2f(drawPolygon.b.x, drawPolygon.b.y);     //  so that the normal (front-face) is facing you
		//glVertex2f(drawPolygon.c.x, drawPolygon.c.y);
		//glVertex2f(drawPolygon.d.x, drawPolygon.d.y);
		drawHollowCircle(m_Current_position_coordinate.x, m_Current_position_coordinate.y,m_radius);
	//	drawPolygon.
		//Center x = 	x + 1/2 of width 
		//Center y = 	y + 1/2 of height

		//glEnd();		

	}

	void Agent::drawAgent(CubeGeomerty* drawlocation) // Assume you have all the vertices of polygon and the color
	{
		glBegin(GL_QUADS); 
		CubeGeomerty drawPolygon = (m_map[static_cast<int>((*drawlocation).location.x)][static_cast<int>((*drawlocation).location.y)]).getCubeCoordinates();
	//	glColor3f(nodeCoordinates.getCubeColor().x, nodeCoordinates.getCubeColor().y ,nodeCoordinates.getCubeColor().z); // Red			

		glColor3f(draw_color.x,draw_color.y,draw_color.z);
		glVertex2f(drawPolygon.a.x, drawPolygon.a.y);     // Define vertices in counter-clockwise (CCW) order
		glVertex2f(drawPolygon.b.x, drawPolygon.b.y);     //  so that the normal (front-face) is facing you
		glVertex2f(drawPolygon.c.x, drawPolygon.c.y);
		glVertex2f(drawPolygon.d.x, drawPolygon.d.y);

		glEnd();		
	}

	void Agent::render(){ 
			drawAgent();
		
	}
	void Agent::UpdateAI(float delta_time){
		
			//std::cout<<"\nid:"<<agent_id <<" |Update";
		//this->m_Position_system->update(); // Propogate the update to the AI instance
		//this->m_Position_System_Aggresive->update();
		//m_Position_System_Defensive->update();
		m_Strategic_System_Defensive->pathFindingAStar();
		
		m_Agent_Action = MOVING;

		if(m_Agent_Action == SHOOTING || m_Agent_Action == NOTHING)
		{
			//drawAgent();
			//std::cout <<"Before: "<< m_map[static_cast<int>((*m_pCurrent_location).location.x)][static_cast<int>((*m_pCurrent_location).location.y)].getNodeStatus();
			m_map[static_cast<int>((*m_pCurrent_location).location.x)][static_cast<int>((*m_pCurrent_location).location.y)].setNodeStatus(LOCKED);
			//std::cout <<"After: " <<m_map[static_cast<int>((*m_pCurrent_location).location.x)][static_cast<int>((*m_pCurrent_location).location.y)].getNodeStatus();
		//	(m_map[currentCoord.getX()][currentCoord.getY()]).setNodeType(NODE_COLLISION);
		}
	   else
		if (m_Agent_Action == MOVING)
		{
			//std::cout<<"\nid:"<<agent_id <<" |Moving";
			if(!m_Move_path_nodes.empty()){

				float calc_distance= distance_absSq(m_Current_position_coordinate, m_pNextNode.center);
				if(m_pNextNode.center == glm::vec3(0.0f,0.0f,0.0f)){
					//if true then change the current node to next node in the path.
					//and calculate the new direction to move towards

				 CubeGeomerty* tempNextCubeCoor = m_Move_path_nodes.back(); // get the node
				  m_pCurrentNode  =  (m_map[static_cast<int>((*tempNextCubeCoor).location.x)][static_cast<int>((*tempNextCubeCoor).location.y)]).getCubeCoordinates();
				  m_Move_path_nodes.pop_back(); // distroy the node

				  tempNextCubeCoor = m_Move_path_nodes.back();
				  m_Move_path_nodes.pop_back();
				  m_pNextNode = (m_map[static_cast<int>((*tempNextCubeCoor).location.x)][static_cast<int>((*tempNextCubeCoor).location.y)]).getCubeCoordinates();
				 
				  m_Current_position_coordinate = m_pCurrentNode.center;
				}
				else if((m_pNextNode.proximity*0.5 > calc_distance  && !m_Move_path_nodes.empty())){
				
				 
				  CubeGeomerty* tempNextCubeCoor = m_Move_path_nodes.back();
				  m_Move_path_nodes.pop_back();
				  m_pNextNode = (m_map[static_cast<int>((*tempNextCubeCoor).location.x)][static_cast<int>((*tempNextCubeCoor).location.y)]).getCubeCoordinates();
				  m_pCurrentNode = m_pNextNode;
				}
				else if(m_Move_path_nodes.empty())
				{
					m_Agent_Action = SHOOTING;
					m_pCurrent_direction = glm::vec3(0.0f,0.0f,0.0f);
				}

				// just do at legacy
				m_pCurrent_location = &m_pCurrentNode;
				     // get the next node to calculate the direction
				glm::vec3 dir = m_pNextNode.center - m_Current_position_coordinate;
				//std::cout << "\nAgent:"<< agent_id <<" NextCenter:(x:"<<m_pNextNode.center.x << ",y:"<<m_pNextNode.center.y <<")\n" ;
				m_pCurrent_direction = glm::normalize(dir);

				float width_of_each_grid = 640  / _GRID_RESOLUTION_X_AXIS;
				float height_of_each_grid =  480 / _GRID_RESOLUTION_Y_AXIS;

				std::vector<int> returnAgentlist;
				returnAgentlist.reserve(10);
				getNearestNeighbour(returnAgentlist, this, agent_hashtable, _GRID_RESOLUTION_X_AXIS, 
					_GRID_RESOLUTION_Y_AXIS, width_of_each_grid, height_of_each_grid);

				std::vector<Agent*> agent_neighbors;
				bool isCollision = false;

				//std::cout<<"\nid:"<<agent_id <<" |AgentsList";
				for(int i =0; i< returnAgentlist.size();i++)
				{
					//std::cout << ":" <<returnAgentlist[i];
					Agent* temp_agent = m_agents[returnAgentlist[i]];
					float agent_dist = distance_absSq(m_Current_position_coordinate,temp_agent->m_Current_position_coordinate);
					if(agent_dist < (m_radius + temp_agent->m_radius))
					{
							isCollision = true;
					}

					agent_neighbors.push_back( temp_agent);
				}

				
				vec3 prefVelocity  = m_pCurrent_direction * ( m_Current_velocity);

				m_ROVNavigationSystem->simulateNewVelocity(this,agent_neighbors,glm::vec2(prefVelocity.x, prefVelocity.y),
					isCollision, delta_time);

				m_Current_position_coordinate += vec3(m_Current_velocity_vector.x * delta_time,
													m_Current_velocity_vector.y * delta_time,
													0.0f);

			}
			else 
			{
				
				m_Agent_Action = SHOOTING;
			//	m_map[static_cast<int>((*m_pCurrent_Move_target).location.x)][static_cast<int>((*m_pCurrent_Move_target).location.y)].setNodeType(NODE_COLLISION);
			//	this->drawAgent();

			}
		}

	}




//}