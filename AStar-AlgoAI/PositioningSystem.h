#pragma once

//#include "Agent.h"
//#include "CubeGeometry.h"
#include "PathFindingAStar.h"
#include "LSPositionFindingAStar.h"




	class Agent;
	class PositioningSystem
	{
		private:
		
		PathFindingAStar pathfindingAStar;
		LSPositionFindingAStar lineOfSightAStar;

				
	public: 
		// Constructor decleration
		

		PositioningSystem();
		PositioningSystem(Agent* owner);
		Agent* m_pOwner;
		//Utility Methods

		void update();

		bool isTargetPlayerPresent();
	
		static bool  isLineOfSightPresent(ds::CubeGeomerty ,ds::CubeGeomerty );

		void FindNewPostionForLS();

		bool checkIfValidPointInGraph(ds::CubeGeomerty);

		bool checkIfWalkable(ds::CubeGeomerty);


	};

