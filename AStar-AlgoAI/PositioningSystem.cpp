#include "PositioningSystem.h"
#include "GameWorld.h"
#include <iostream>


	// Constructor decleration
	PositioningSystem::PositioningSystem()
	{

	}

	PositioningSystem::PositioningSystem(Agent* owner)
	{
		m_pOwner = owner;
		pathfindingAStar = PathFindingAStar();
		lineOfSightAStar = LSPositionFindingAStar();
	}


	//Utility Methods

	void PositioningSystem::update()
	{
		//m_map[static_cast<int>((*m_pOwner->m_pCurrent_location).location.x)][static_cast<int>((*m_pOwner->m_pCurrent_location).location.y)].setNodeType(NODE_WALKABLE);
			// MultiAgent Changes, set the next move target as NODE_COLLISION so that other agents wont select it as target.
		if(nullptr != m_pOwner->m_pCurrent_Move_target)
		{
		//	m_map[static_cast<int>((*m_pOwner->m_pCurrent_Move_target).location.x)][static_cast<int>((*m_pOwner->m_pCurrent_Move_target).location.y)].setNodeType(NODE_WALKABLE);
		}
		// Check if there is line of sight to the target
		// using ray casting 
		if(isTargetPlayerPresent()){
			if( m_pOwner->m_Agent_Action == NOTHING  && isLineOfSightPresent(*m_pOwner->m_pCurrent_location, *m_pOwner->m_pCurrent_target))
			{
				m_pOwner->m_Agent_Action = SHOOTING;
			}else if(m_pOwner->m_Agent_Action == NOTHING && !isLineOfSightPresent(*m_pOwner->m_pCurrent_location, *m_pOwner->m_pCurrent_target))
			{
				FindNewPostionForLS(); // 1:Set Action to Moving 2:Find new Move Location 3:Find Path to new move
			}
			else if( m_pOwner->m_Agent_Action == SHOOTING  && isLineOfSightPresent(*m_pOwner->m_pCurrent_location, *m_pOwner->m_pCurrent_target))
			{
				return ;
			}
			else if (m_pOwner->m_Agent_Action == SHOOTING && !isLineOfSightPresent(*m_pOwner->m_pCurrent_location, *m_pOwner->m_pCurrent_target))
			{
				FindNewPostionForLS(); // 1:Set Action to Moving 2:Find new Move Location 3:Find Path to new move
				 
			}
			else if (m_pOwner->m_Agent_Action == MOVING && !isLineOfSightPresent(*m_pOwner->m_pCurrent_Move_target, *m_pOwner->m_pCurrent_target))
			{
				FindNewPostionForLS(); // 1:Set Action to Moving 2:Find new Move Location 3:Find Path to new move
			}
		}
	}

	void PositioningSystem::FindNewPostionForLS() // 1:Set Action to Moving 2:Find new Move Location 3:Find Path to new move
	{
		//1. Find the New cube to move which has Line of sight.
		ds::Node* pathNodes = lineOfSightAStar.A_Star(*m_pOwner->m_pCurrent_location,  *m_pOwner->m_pCurrent_target);
		Node node = *pathNodes;
		
		//2. Find the convinient path to the new move location.
		ds::CubeGeomerty* next_move_cube = new ds::CubeGeomerty((*pathNodes).getCubeCoordinates().location);
		pathNodes = pathfindingAStar.A_Star(*m_pOwner->m_pCurrent_location, *next_move_cube);
		
		//3. Set the Agent action to MOve as the agent wil be moving to the new cube for next few frames.		
		m_pOwner->m_Agent_Action = MOVING;

		if(m_pOwner->m_pCurrent_Move_target !=nullptr){
			m_map[static_cast<int>((*m_pOwner->m_pCurrent_Move_target).location.x)][static_cast<int>((*m_pOwner->m_pCurrent_Move_target).location.y)].setNodeStatus(OPEN);
		}
		m_pOwner->m_pCurrent_Move_target = new ds::CubeGeomerty((*pathNodes).getCubeCoordinates().location);

		m_map[static_cast<int>((*m_pOwner->m_pCurrent_Move_target).location.x)][static_cast<int>((*m_pOwner->m_pCurrent_Move_target).location.y)].setNodeStatus(LOCKED);

		// MultiAgent Changes, set the next move target as NODE_COLLISION so that other agents wont select it as target.
		//m_map[static_cast<int>((*m_pOwner->m_pCurrent_Move_target).location.x)][static_cast<int>((*m_pOwner->m_pCurrent_Move_target).location.y)].setNodeType(NODE_COLLISION);
		//4. Create a vector of nodes to move through to get to the new cube;
		std::cout <<"\n**************************";
		m_pOwner->m_Move_path_nodes.clear();
			while(true)
		{
			if(nullptr != pathNodes){	
		
				Node node = *pathNodes; // Dereference the object for the parent node
				// Add here
						

				m_pOwner->m_Move_path_nodes.push_back(new ds::CubeGeomerty(node.getCubeCoordinates().location));
						
				std::cout << "\nAI:(" << node.getX() << "," << node.getY() << ")";

				pathNodes = node.getParentNode();
				//node.setNodeStatus(PATH);
						
			}
			else
			{
				break;
			}
		}
	
	}

	bool PositioningSystem::isTargetPlayerPresent()
	{
		ds::CubeGeomerty*  cg = m_pOwner->m_pCurrent_target;
		bool result = true;
		if(cg == NULL)
		{
			result = false;
		}

		return result;
	}



	bool PositioningSystem::isLineOfSightPresent(ds::CubeGeomerty startLocation, ds::CubeGeomerty targetLocation)
	{
		bool result = true; 
		//if(isTargetPlayerPresent)
		{
			// Point 1 startLocation
			// Point 2 targetLocation

			// Bresenham's line algorithm
			//ds::CubeGeomerty targetLocation = *(m_pOwner->m_pCurrent_target);
			const bool steep = (fabs(targetLocation.location.y - startLocation.location.y) > fabs(targetLocation.location.x - startLocation.location.x));
			if(steep)
			{
				std::swap(startLocation.location.x, startLocation.location.y);
				std::swap(targetLocation.location.x, targetLocation.location.y);
			}

			if(startLocation.location.x > targetLocation.location.x)
			{
				std::swap(startLocation.location.x, targetLocation.location.x);
				std::swap(startLocation.location.y, targetLocation.location.y);
			}

			const float dx = targetLocation.location.x - startLocation.location.x;
			const float dy = fabs(targetLocation.location.y - startLocation.location.y);

			float error = dx / 2.0f;
			const int ystep = (startLocation.location.y < targetLocation.location.y) ? 1 : -1;
			int y = (int)startLocation.location.y;

			const int maxX = (int)targetLocation.location.x;

			for(int x=(int)startLocation.location.x; x<maxX; x++)
			{
				if(steep)
				{
					if(m_map[y][x].getNodeType() == ds::NODE_COLLISION  )
					{
						result = false; 
						break;
					}

					if(x != (int)startLocation.location.x || y != (int)startLocation.location.y) {
						if(m_map[y][x].getNodeStatus() == LOCKED )
						{
							result = false; 
							break;
						}
					}
					//std::cout<<  "cube:" << y << ","<< x << "\n";
					//    SetPixel(y,x, color);
				}
				else
				{
					if(m_map[x][y].getNodeType() == ds::NODE_COLLISION )
					{
						result = false; 
						break;
					}

					if(x != (int)startLocation.location.x || y != (int)startLocation.location.y){
						if(m_map[x][y].getNodeStatus() == LOCKED)
						{
							result = false; 
							break;
						}
					}
					//std::cout<<  "cube:" << x << ","<< y << "\n";
				}

				error -= dy;
				if(error < 0)
				{
					y += ystep;
					error += dx;
				}
			}


		}
		return result;
	}




