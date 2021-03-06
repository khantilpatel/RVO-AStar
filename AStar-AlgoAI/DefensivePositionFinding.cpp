#include "DefensivePositionFinding.h"
#include <algorithm>


using namespace ds;
using namespace std;

DefensivePositionFinding::DefensivePositionFinding(void)
{

}


DefensivePositionFinding::~DefensivePositionFinding(void)
{
	
}


Node* DefensivePositionFinding::getClosestPosition(CubeGeomerty startNode, CubeGeomerty targetNode)
{
			nodeList.clear();

			int current_X = (int)targetNode.location.x;
			int current_Y = (int)targetNode.location.y;

			for(int x=0; x < _GRID_RESOLUTION_X_AXIS; x++)
			{
				//float current_X_coord = x * width_of_each_grid;


				for(int y=0; y < _GRID_RESOLUTION_Y_AXIS; y++)
				{
					if(m_map[x][y].getPF() == 4 && isLineOfSightPresent(targetNode, m_map[x][y].getCubeCoordinates()))
					{
					  addToOpenList(&(m_map[x][y]));
					}
				}
			}
				

			calculateHeuristics((m_map[static_cast<int>(startNode.location.x)][static_cast<int>(startNode.location.y)]));

			sort (nodeList.begin(), nodeList.end(), sortBy_Node_Huristics);
		
			return nodeList.front();

}



void DefensivePositionFinding::calculateHeuristics(Node& targetNode)
{	  	  

	for (std::vector<Node*>::iterator it = nodeList.begin() ; it != nodeList.end(); ++it)
	{
			int x_temp = abs((*it)->getX() - targetNode.getX());
			int y_temp = abs((*it)->getY() - targetNode.getY());
			(*it)->setH((x_temp+y_temp)*10);
	
	}
}

void DefensivePositionFinding::addToOpenList(Node* m_Node)
{
	if((NODE_COLLISION != m_Node->getNodeType()) ) // Avoid if the node is wall or something cant be passed by
	{
		if(LOCKED!= m_Node->getNodeStatus())
			 // Avoid if the node is closed already or Opened
			{
				//m_Node->setG(m_G + m_theParentNode.getG());// set the G Cost for this node and add it to the nodelist
				//m_Node->setParentNode(&m_theParentNode);// set the parent.
		//		m_Node->setNodeStatus(OPEN);
				nodeList.push_back(m_Node);
			}
		
	}

}


bool DefensivePositionFinding::setNodeStatusToClosed(Node &node, CubeGeomerty &targetNode)
{
	//Check if this is not the target node, if yes then hurry... we got our Path
	if((node).getX() == targetNode.location.x && node.getY() == targetNode.location.y)
	{
		return false;
	}
	else{
		node.setNodeStatus(CLOSSED);

		return true;
	}
}

bool DefensivePositionFinding::isLineOfSightPresent(ds::CubeGeomerty startLocation, ds::CubeGeomerty targetLocation)
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