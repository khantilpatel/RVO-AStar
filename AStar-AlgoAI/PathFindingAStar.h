#pragma once
#include <vector>
#include "GameWorld.h"

using namespace ds;

class PathFindingAStar
{


public:
	std::vector<Node*> nodeList;

	PathFindingAStar(void);
	~PathFindingAStar(void);
	
	void calculateHeuristics(Node& targetNode);

	void addToOpenList(Node* m_Node, Node& m_theParentNode, int m_G);

	bool setNodeStatusToClosed(Node &node, CubeGeomerty &targetNode);
	
	Node* A_Star(CubeGeomerty startNode, CubeGeomerty targetNode);

};

