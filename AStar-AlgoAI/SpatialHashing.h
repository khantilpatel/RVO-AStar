
#include <vector>

#include "Agent.h"
#include <glm/glm.hpp>
#include <iostream>

void construct_hash_table(std::vector<Agent*>& v_agents,
						  int grid_width, int grid_height, int cell_width, int cell_height );



bool getNearestNeighbour(std::vector<int>& returnAgentlist , Agent* ,std::vector<std::vector<int> >& v_agents_hashtable, 
						 int grid_width, int grid_height, int cell_width, int cell_height);