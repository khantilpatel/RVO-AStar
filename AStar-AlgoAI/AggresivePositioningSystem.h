#pragma once

//#include "Agent.h"
//#include "CubeGeometry.h"
#include "PathFindingAStar.h"
#include "LSPositionFindingAStar.h"
#include "AggresivePositionFinding.h"



	class Agent;
	class AggresivePositioningSystem
	{
		private:
		
		PathFindingAStar pathfindingAStar;
		LSPositionFindingAStar lineOfSightAStar;
		AggresivePositionFinding aggresivePositionFinding;			
	public: 
		// Constructor decleration
		

		AggresivePositioningSystem();
		AggresivePositioningSystem(Agent* owner);
		Agent* m_pOwner;
		//Utility Methods

		void update();

		bool isTargetPlayerPresent();
	
		static bool  isLineOfSightPresent(ds::CubeGeomerty ,ds::CubeGeomerty );

		void FindNewPostionForLS();

		bool checkIfValidPointInGraph(ds::CubeGeomerty);

		bool checkIfWalkable(ds::CubeGeomerty);

		static bool  isClosest(ds::CubeGeomerty ,ds::CubeGeomerty );

	};

