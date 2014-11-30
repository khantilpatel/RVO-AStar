#include "AggresivePositionFinding.h"
#include <algorithm>


using namespace ds;
using namespace std;

AggresivePositionFinding::AggresivePositionFinding(void)
{

}


AggresivePositionFinding::~AggresivePositionFinding(void)
{
	
}


Node* AggresivePositionFinding::getClosestPosition(CubeGeomerty startNode, CubeGeomerty targetNode)
{
//	createGrid();
	
	//int* nodes =  GameWorld::getGameMap();
	nodeList.clear();
	//nodeList.push_back(&(m_map[static_cast<int>(startNode.location.x)][static_cast<int>(startNode.location.y)]));	

	//int* nodes =  GameWorld::getGameMap();	
//	Node* currentNode = nullptr;
	//bool targetFound = false;
//	bool pathResult = false;

	//	sort (nodeList.begin(), nodeList.end(), sortBy_FValue_NodeStatus);

		//Node n1 = currentNode;
		//(*currentNode).setNodeType(NODE_COLLISION);
		//if(setNodeStatusToClosed(*currentNode, targetNode)){
			//sort (nodeList.begin(), nodeList.end(), sortBy_FValue_NodeStatus);

			// Add all the 8 surrounded node to the openList by checking if its not the end node in the Grid
			int current_X = (int)targetNode.location.x;
			int current_Y = (int)targetNode.location.y;

			if(_GRID_RESOLUTION_X_AXIS > (current_X+1)) // To the immidiate right
			{
				addToOpenList(&(m_map[current_X+1][current_Y]));

			}
			if(_GRID_RESOLUTION_X_AXIS > (current_X+1) && 0 <= (current_Y-1)) // To the Right-Down
			{
				addToOpenList(&(m_map[current_X+1][current_Y-1]));
			}
			if(0 <= (current_Y-1)) // To Below/Down
			{
				addToOpenList(&(m_map[current_X][current_Y-1]));
			}
			if(0 <= (current_X-1) && 0 <= (current_Y-1) ) //To Left-Down
			{
				addToOpenList(&(m_map[current_X-1][current_Y-1]));
			}

			if(0 <= (current_X-1)) //To Left
			{
				addToOpenList(&(m_map[current_X-1][current_Y]));
			}

			if(0 <= (current_X-1) && _GRID_RESOLUTION_Y_AXIS >(current_Y+1) ) //To Left-Up
			{
				addToOpenList(&(m_map[current_X-1][current_Y+1]));
			}

			if(_GRID_RESOLUTION_Y_AXIS >(current_Y+1) ) //To Up
			{
				addToOpenList(&(m_map[current_X][current_Y+1]));
			}

			if(0 <= (current_X+1) && _GRID_RESOLUTION_Y_AXIS >(current_Y+1) ) //To UP-RIGHT
			{
				addToOpenList(&(m_map[current_X+1][current_Y+1]));
			}

			calculateHeuristics((m_map[static_cast<int>(startNode.location.x)][static_cast<int>(startNode.location.y)]));

			sort (nodeList.begin(), nodeList.end(), sortBy_Node_Huristics);
		
			return nodeList.front();

}



void AggresivePositionFinding::calculateHeuristics(Node& targetNode)
{	  	  

	for (std::vector<Node*>::iterator it = nodeList.begin() ; it != nodeList.end(); ++it)
	{
			int x_temp = abs((*it)->getX() - targetNode.getX());
			int y_temp = abs((*it)->getY() - targetNode.getY());
			(*it)->setH((x_temp+y_temp)*10);
	
	}
}

void AggresivePositionFinding::addToOpenList(Node* m_Node)
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


bool AggresivePositionFinding::setNodeStatusToClosed(Node &node, CubeGeomerty &targetNode)
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