#pragma once

//#include "Agent.h"
//#include "CubeGeometry.h"

#include "math_functions.h"
#include <vector>

#define RVO_INFTY 9e9f

using namespace std;
using namespace glm;

	class Agent;
	class ROVNavigationSystem
	{
		private:
		
		float prefSpeedDefault;
		float maxSpeedDefault;
		float safetyFactorDefault;
		float maxAccelDefault;
		int sampleCountDefault;


	
	public: 
		// Constructor decleration
		
		/*
		float prefSpeedDefault;
		float maxSpeedDefault;
		float safetyFactorDefault;
		float maxAccelDefault;
		int sampleCountDefault;

		*/
		ROVNavigationSystem();
		ROVNavigationSystem( float, float, float, float,int);
		//Agent* m_pOwner;
		//Utility Methods

		void simulateNewVelocity(Agent* ,vector<Agent*>&, vec2, bool,float);
		float computeTimeToCollison(const vec2& p, const vec2& v, const vec2& p2, float radius, bool collision);
	};

