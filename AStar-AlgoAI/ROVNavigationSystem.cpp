#include "ROVNavigationSystem.h"
#include "GameWorld.h"
#include <iostream>


// Constructor decleration
ROVNavigationSystem::ROVNavigationSystem()
{

}

ROVNavigationSystem::ROVNavigationSystem(float m_prefSpeedDefault, float m_maxSpeedDefault, 
										 float m_safetyFactorDefault, float m_maxAccelDefault,int m_sampleCountDefault)
{
	
	this->prefSpeedDefault = m_prefSpeedDefault;
	this->maxSpeedDefault = m_maxSpeedDefault;
	this->safetyFactorDefault = m_safetyFactorDefault;
	this->maxAccelDefault = m_maxAccelDefault;
	this->sampleCountDefault = m_sampleCountDefault;

}



void ROVNavigationSystem::simulateNewVelocity(Agent* m_pOwner, vector<Agent*>& agent_neighbors, vec2 prefVelocity, bool isCollison, float _timeStep)
{
	float min_penalty = RVO_INFTY;
	vec2 vCand;
	for (int n = 0; n < this->sampleCountDefault; n++) 
	{
		if (n == 0) {
			vCand = prefVelocity;
		} else {
			do {
				float randX = rand();
				randX *= 2.0f;

				float randY = rand();
				randY *= 2.0f;

				float x = randX - RAND_MAX ;
				float y = randY - RAND_MAX;

				vCand = vec2(x, y); //2.0f*rand() - RAND_MAX, 2.0f*rand() - RAND_MAX);

				float absVCand = absSq(vCand);
				float sqrRand_Max = sqr((float)RAND_MAX);

			} while (absSq(vCand) > sqr((float) RAND_MAX));
			vCand *= (this->maxSpeedDefault / RAND_MAX);
		}

		float dV; // distance between candidate velocity and preferred velocity
		if (isCollison) {
			dV = 0;
			if (agent_neighbors.size() > 1)
			{
				dV = 0;
			}
		} else {
			dV = abs(vCand - prefVelocity);
		}


		// searching for smallest time to collision
		float ct = RVO_INFTY; // time to collision
		// iterate over neighbors
		for(int i = 0; i< agent_neighbors.size(); i++)
		{
			float ct_j; // time to collision with agent j
			vec2 Vab;

			Agent* other = agent_neighbors[i];

			Vab = 2.0f * vCand - m_pOwner->m_Current_velocity_vector - other->m_Current_velocity_vector;

			float time = computeTimeToCollison(
				vec2(m_pOwner->m_Current_position_coordinate.x,m_pOwner->m_Current_position_coordinate.y),
				Vab,
				vec2(other->m_Current_position_coordinate.x,other->m_Current_position_coordinate.y),
				m_pOwner->m_radius + other->m_radius,
				isCollison);

			if (isCollison) {
				ct_j = -std::ceil(time / _timeStep);
				ct_j -= absSq(vCand) / sqr(this->maxSpeedDefault);
			}
			else {
				ct_j = time;
			}


			if (ct_j < ct) {
				ct = ct_j;
				// pruning search if no better penalty can be obtained anymore for this velocity
				if (this->safetyFactorDefault / ct + dV >= min_penalty) {
					break;
				}
			}
		}

		float penalty = this->safetyFactorDefault / ct + dV;
		if (penalty < min_penalty) {
			min_penalty = penalty;
			m_pOwner->m_Current_velocity_vector  = vCand;
		}
	}

}


float ROVNavigationSystem::computeTimeToCollison(const vec2& p, const vec2& v, const vec2& p2, float radius, bool collision)
{
	  vec2 ba = p2 - p;
    float sq_diam = radius * radius;
    float time;

    float discr = -sqr(det(v, ba)) + sq_diam * absSq(v);
    if (discr > 0) {
      if (collision) {
       time = (dotproduct(v , ba) + std::sqrt(discr)) / absSq(v);

        if (time < 0) {
          time = -RVO_INFTY;
        }
      } else {
        time = (dotproduct(v , ba) - std::sqrt(discr)) / absSq(v);
        if (time < 0) {
          time = RVO_INFTY;
        }
      }
    } else {
      if (collision) {
        time = -RVO_INFTY;
      } else {
        time = RVO_INFTY;
      }
    }
    return time;
}



