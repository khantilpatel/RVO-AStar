#pragma once

//#include "Agent.h"
//#include "CubeGeometry.h"
#include "PathFindingAStar.h"
#include "LSPositionFindingAStar.h"
#include "AggresivePositionFinding.h"
#include "DefensivePositionFinding.h"


	class Agent;
	class DefensivePositioningSystem
	{
		private:
		
		PathFindingAStar pathfindingAStar;
		LSPositionFindingAStar lineOfSightAStar;
		AggresivePositionFinding aggresivePositionFinding;	
		DefensivePositionFinding defensivePositionFinding ;
	public: 
		// Constructor decleration
		

		DefensivePositioningSystem();
		DefensivePositioningSystem(Agent* owner);
		Agent* m_pOwner;
		//Utility Methods

		void update();

		bool isTargetPlayerPresent();
	
		static bool  isLineOfSightPresent(ds::CubeGeomerty ,ds::CubeGeomerty );

		void FindNewPostionForLS();

		bool checkIfValidPointInGraph(ds::CubeGeomerty);

		bool checkIfWalkable(ds::CubeGeomerty);

		static bool  isClosest(ds::CubeGeomerty );

	};

