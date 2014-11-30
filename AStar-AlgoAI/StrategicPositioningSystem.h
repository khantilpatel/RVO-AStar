#pragma once

//#include "Agent.h"
//#include "CubeGeometry.h"
#include "PathFindingAStar.h"
#include "LSPositionFindingAStar.h"
#include "AggresivePositionFinding.h"
#include "StrategicPositionFinding.h"


	class Agent;
	class StrategicPositioningSystem
	{
		private:
		
		PathFindingAStar pathfindingAStar;
		LSPositionFindingAStar lineOfSightAStar;
		AggresivePositionFinding aggresivePositionFinding;			
		StrategicPositionFinding strategicPositionFinding;
	public: 
		// Constructor decleration
		

		StrategicPositioningSystem();
		StrategicPositioningSystem(Agent* owner);
		Agent* m_pOwner;
		//Utility Methods

		void update();

		bool isTargetPlayerPresent();
	
		static bool  isLineOfSightPresent(ds::CubeGeomerty ,ds::CubeGeomerty );

		void FindNewPostionForLS();

		bool checkIfValidPointInGraph(ds::CubeGeomerty);

		bool checkIfWalkable(ds::CubeGeomerty);

		static bool  isClosest(ds::CubeGeomerty ,ds::CubeGeomerty );
		void pathFindingAStar();

	};

