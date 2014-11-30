#include "SpatialHashing.h"
#include "GameWorld.h"


void construct_hash_table(std::vector<Agent*>& v_agents,
						  int grid_width, int grid_height, int cell_width, int cell_height )
{
		for(int i = 0 ; i< agent_hashtable.size(); i++)
		{
			agent_hashtable[i].clear();
		}

		for(int i = 0 ; i< v_agents.size(); i++)
		{
			glm::vec3 agent_position = v_agents[i]->m_Current_position_coordinate;

			int hash_index =  floor(agent_position.x/cell_width) + grid_width *(floor(agent_position.y/cell_height) );
			// std::cout<< "\nagent_id:"<<i<<" hash_index:"<<hash_index;
			std::vector<int>& bucket = agent_hashtable[hash_index];

			bucket.push_back(v_agents[i]->agent_id);
		}

}


bool getNearestNeighbour(std::vector<int>& returnAgentlist ,Agent* agent ,std::vector<std::vector<int> >& v_agents_hashtable, int _GRID_RESOLUTION_X_AXIS, int _GRID_RESOLUTION_Y_AXIS, int cell_width, int cell_height)
{
			glm::vec3 agent_position = agent->m_Current_position_coordinate;
	
			int hash_index =  floor(agent_position.x/cell_width) + _GRID_RESOLUTION_X_AXIS *(floor(agent_position.y/cell_height) );

			int current_X = floor(agent_position.x/cell_width);
			int current_Y = floor(agent_position.y/cell_height);

				int x = current_X ;
				int y = current_Y;
				if(m_map[x][y].getNodeType() != ds::NODE_COLLISION)
				{
					int hash_index_neighbour =  x + _GRID_RESOLUTION_X_AXIS * y;

					std::vector<int>& bucket = v_agents_hashtable[hash_index_neighbour];

					for(int i=0; i< bucket.size(); i++){
						int id = bucket[i];
						if(id!= agent->agent_id){
							returnAgentlist.push_back(bucket[i]);
						}
					}
				}

		
			if(_GRID_RESOLUTION_X_AXIS > (current_X+1)) // To the immidiate right
			{
				int x = current_X+1 ;
				int y = current_Y;
				if(m_map[x][y].getNodeType() != ds::NODE_COLLISION)
				{
					int hash_index_neighbour =  x + _GRID_RESOLUTION_X_AXIS * y;

					std::vector<int>& bucket = v_agents_hashtable[hash_index_neighbour];

					returnAgentlist.insert(returnAgentlist.end(), bucket.begin(), bucket.end());
				}

			}
			if(_GRID_RESOLUTION_X_AXIS > (current_X+1) && 0 <= (current_Y-1)) // To the Right-Down
			{
				int x = current_X+1 ;
				int y = current_Y-1;
				if(m_map[x][y].getNodeType() != ds::NODE_COLLISION)
				{
					int hash_index_neighbour =  x + _GRID_RESOLUTION_X_AXIS * y;

					std::vector<int>& bucket = v_agents_hashtable[hash_index_neighbour];

					returnAgentlist.insert(returnAgentlist.end(), bucket.begin(), bucket.end());
				}
			}
			if(0 <= (current_Y-1)) // To Below/Down
			{
				int x = current_X;
				int y = current_Y-1;
				if(m_map[x][y].getNodeType() != ds::NODE_COLLISION)
				{
					int hash_index_neighbour =  x + _GRID_RESOLUTION_X_AXIS * y;

					std::vector<int>& bucket = v_agents_hashtable[hash_index_neighbour];

					returnAgentlist.insert(returnAgentlist.end(), bucket.begin(), bucket.end());
				}
			}
			if(0 <= (current_X-1) && 0 <= (current_Y-1) ) //To Left-Down
			{
				int x = current_X-1 ;
				int y = current_Y-1;
				if(m_map[x][y].getNodeType() != ds::NODE_COLLISION)
				{
					int hash_index_neighbour =  x + _GRID_RESOLUTION_X_AXIS * y;

					std::vector<int>& bucket = v_agents_hashtable[hash_index_neighbour];

					returnAgentlist.insert(returnAgentlist.end(), bucket.begin(), bucket.end());
				}
			}

			if(0 <= (current_X-1)) //To Left
			{
				int x = current_X-1 ;
				int y = current_Y;
				if(m_map[x][y].getNodeType() != ds::NODE_COLLISION)
				{
					int hash_index_neighbour =  x + _GRID_RESOLUTION_X_AXIS * y;

					std::vector<int>& bucket = v_agents_hashtable[hash_index_neighbour];

					returnAgentlist.insert(returnAgentlist.end(), bucket.begin(), bucket.end());
				}
			}

			if(0 <= (current_X-1) && _GRID_RESOLUTION_Y_AXIS >(current_Y+1) ) //To Left-Up
			{
				int x = current_X-1 ;
				int y = current_Y+1;
				if(m_map[x][y].getNodeType() != ds::NODE_COLLISION)
				{
					int hash_index_neighbour =  x + _GRID_RESOLUTION_X_AXIS * y;

					std::vector<int>& bucket = v_agents_hashtable[hash_index_neighbour];

					returnAgentlist.insert(returnAgentlist.end(), bucket.begin(), bucket.end());
				}
			}

			if(_GRID_RESOLUTION_Y_AXIS >(current_Y+1) ) //To Up
			{
				int x = current_X ;
				int y = current_Y+1;
				if(m_map[x][y].getNodeType() != ds::NODE_COLLISION)
				{
					int hash_index_neighbour =  x + _GRID_RESOLUTION_X_AXIS * y;

					std::vector<int>& bucket = v_agents_hashtable[hash_index_neighbour];

					returnAgentlist.insert(returnAgentlist.end(), bucket.begin(), bucket.end());
				}
			}
			if(0 <= (current_X+1) && _GRID_RESOLUTION_Y_AXIS >(current_Y+1) ) //To UP-RIGHT
			{
				int x = current_X+1 ;
				int y = current_Y+1;
				if(m_map[x][y].getNodeType() != ds::NODE_COLLISION)
				{
					int hash_index_neighbour =  x + _GRID_RESOLUTION_X_AXIS * y;

					std::vector<int>& bucket = v_agents_hashtable[hash_index_neighbour];

					returnAgentlist.insert(returnAgentlist.end(), bucket.begin(), bucket.end());
				}
			}

	return true;
}