#pragma once


//#include <vector>
//#include <glm/glm.hpp>
//#include "CubeGeometry.h"
#include "Node.h"
#include <glut/glut.h>
#include "math_functions.h"
//#include "SpatialHashing.h"
//#include "PositioningSystem.h"

//namespace model{
class PositioningSystem;
class AggresivePositioningSystem;
class DefensivePositioningSystem;
class StrategicPositioningSystem;
class ROVNavigationSystem;
//class PathFindingAStar;
	enum AgentAction{
		SHOOTING, MOVING, NOTHING
	};

	class Agent{
	private:
		//glm::vec3 currentNodeLocation; // Location of player in the Grid.
		//glm::vec3 targetNodeLocation; // Location of player in the Grid.
		
		//ds::CubeGeomerty nodeCoordinates;
	public:

		int agent_id;
		ds::CubeGeomerty* m_pCurrent_location; // Current node of the agent when Action is SHOOTING and The Target node when Action is .
		
		ds::CubeGeomerty m_pCurrent_location_value;

		ds::CubeGeomerty m_pCurrentNode;

		ds::CubeGeomerty m_pNextNode;

		glm::vec3 m_pCurrent_direction;
		
		// For ROV implementaion /////////////////
		glm::vec3 m_Current_position_coordinate;

		glm::vec2 m_Current_velocity_vector;

		float m_radius;

		float m_Current_velocity;
		////////////////////////////////////////////
		ds::CubeGeomerty* m_pCurrent_target; // Current of the target player.

		ds::CubeGeomerty* m_pCurrent_Move_target; // Node to which agent has to move on when Action is MOVING.

		ds::CubeGeomerty m_pCurrent_Move_target_value;

		std::vector<ds::CubeGeomerty*> m_Move_path_nodes;

		AgentAction m_Agent_Action;

		PositioningSystem* m_Position_system; // Instance of AI class for Position decision system

		AggresivePositioningSystem* m_Position_System_Aggresive;
		
		DefensivePositioningSystem* m_Position_System_Defensive ;

		StrategicPositioningSystem* m_Strategic_System_Defensive;

		ROVNavigationSystem* m_ROVNavigationSystem;

		//PathFindingAStar pathfindingAStar;
		glm::vec3 draw_color;

		glm::vec3 direction;

		//Constructor ***********************************************
		Agent();
		Agent(int, ds::CubeGeomerty&,ds::CubeGeomerty&, glm::vec3,glm::vec3,float,float, ROVNavigationSystem*); // Initialize player with its starting location;

		// Helper Methods*********************************************
		//glm::vec3 getCurrentNodeLocation();
		//void setCurrentNodeLocation(glm::vec3);

		//	ds::CubeGeomerty getCubeCoordinates();
		//	void setCubeCoordinates(ds::CubeGeomerty);

		void drawAgent();

		void drawAgent(ds::CubeGeomerty*);

		void MoveAgent();

		void UpdateAI(float);

		void render();
	};
//}