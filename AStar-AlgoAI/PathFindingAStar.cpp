#include "PathFindingAStar.h"
#include <algorithm>


using namespace ds;
using namespace std;

PathFindingAStar::PathFindingAStar(void)
{
}


PathFindingAStar::~PathFindingAStar(void)
{
	
}


Node* PathFindingAStar::A_Star(CubeGeomerty startNode, CubeGeomerty targetNode)
{
//	createGrid();
	calculateHeuristics((m_map[static_cast<int>(targetNode.location.x)][static_cast<int>(targetNode.location.y)]));
	//int* nodes =  GameWorld::getGameMap();
	nodeList.clear();
	nodeList.push_back(&(m_map[static_cast<int>(startNode.location.x)][static_cast<int>(startNode.location.y)]));	

	//int* nodes =  GameWorld::getGameMap();	
	Node* currentNode = nullptr;
	bool targetFound = false;
	bool pathResult = false;

	while(!targetFound)
	{
		currentNode = (nodeList.front());//(getFirstElementfromSet( nodeList, targetNode));

		if(CLOSSED == (*currentNode).getNodeStatus())
		{
			//Error No Path found
			pathResult = false;
			targetFound = true;
		//	std::cout << "no path found";
		}

		sort (nodeList.begin(), nodeList.end(), sortBy_FValue_NodeStatus);

		//Node n1 = currentNode;
		//(*currentNode).setNodeType(NODE_COLLISION);
		if(setNodeStatusToClosed(*currentNode, targetNode)){
			//sort (nodeList.begin(), nodeList.end(), sortBy_FValue_NodeStatus);

			// Add all the 8 surrounded node to the openList by checking if its not the end node in the Grid
			int current_X = currentNode->getX();
			int current_Y = currentNode->getY();
			if(_GRID_RESOLUTION_X_AXIS > (current_X+1)) // To the immidiate right
			{
				addToOpenList(&(m_map[current_X+1][current_Y]), *currentNode, 10);

			}
			if(_GRID_RESOLUTION_X_AXIS > (current_X+1) && 0 <= (current_Y-1)) // To the Right-Down
			{
				addToOpenList(&(m_map[current_X+1][current_Y-1]), *currentNode, 14);
			}
			if(0 <= (current_Y-1)) // To Below/Down
			{
				addToOpenList(&(m_map[current_X][current_Y-1]), *currentNode, 10);
			}
			if(0 <= (current_X-1) && 0 <= (current_Y-1) ) //To Left-Down
			{
				addToOpenList(&(m_map[current_X-1][current_Y-1]), *currentNode, 14);
			}

			if(0 <= (current_X-1)) //To Left
			{
				addToOpenList(&(m_map[current_X-1][current_Y]), *currentNode, 10);
			}

			if(0 <= (current_X-1) && _GRID_RESOLUTION_Y_AXIS >(current_Y+1) ) //To Left-Up
			{
				addToOpenList(&(m_map[current_X-1][current_Y+1]), *currentNode, 14);
			}

			if(_GRID_RESOLUTION_Y_AXIS >(current_Y+1) ) //To Up
			{
				addToOpenList(&(m_map[current_X][current_Y+1]), *currentNode, 10);
			}

			if(0 <= (current_X+1) && _GRID_RESOLUTION_Y_AXIS >(current_Y+1) ) //To UP-RIGHT
			{
				addToOpenList(&(m_map[current_X+1][current_Y+1]), *currentNode, 14);
			}
			sort (nodeList.begin(), nodeList.end(), sortBy_FValue_NodeStatus);
		}
		else{
			pathResult = true;
			targetFound = true ;			
		}

	}

	return currentNode;

}



void PathFindingAStar::calculateHeuristics(Node& targetNode)
{	  	  
	for(int x=0; x< _GRID_RESOLUTION_X_AXIS; x++)
	{
		for(int y=0; y< _GRID_RESOLUTION_Y_AXIS; y++)
		{
			int x_temp = abs(m_map[x][y].getX() - targetNode.getX());
			int y_temp = abs(m_map[x][y].getY() - targetNode.getY());

			m_map[x][y].setH((x_temp+y_temp)*10);
			m_map[x][y].setParentNode(nullptr);
			
			m_map[x][y].setG(0);

			if(m_map[x][y].getNodeStatus() !=LOCKED)
			{
				m_map[x][y].setNodeStatus(NONE);
			}
	/*		x = m_X;
		y = m_Y;
		H = 0;
		G = 0;
		parentNode = nullptr;
		nodeType= NODE_WALKABLE;
		nodeStatus = NONE;*/
		}
	}		

}

void PathFindingAStar::addToOpenList(Node* m_Node, Node& m_theParentNode, int m_G)
{
	if((NODE_COLLISION != m_Node->getNodeType()) ) // Avoid if the node is wall or something cant be passed by
	{
		if(LOCKED!= m_Node->getNodeStatus()){
			if(CLOSSED != m_Node->getNodeStatus() && OPEN!= m_Node->getNodeStatus()) // Avoid if the node is closed already or Opened
			{
				m_Node->setG(m_G + m_theParentNode.getG());// set the G Cost for this node and add it to the nodelist
				m_Node->setParentNode(&m_theParentNode);// set the parent.
				m_Node->setNodeStatus(OPEN);
				nodeList.push_back(m_Node);
			}
		}
	}

}


bool PathFindingAStar::setNodeStatusToClosed(Node &node, CubeGeomerty &targetNode)
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