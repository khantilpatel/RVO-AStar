#pragma once
#include <vector>
#include "GameWorld.h"

using namespace ds;
class LSPositionFindingAStar //L
{
public:
	LSPositionFindingAStar(void);
	~LSPositionFindingAStar(void);
	std::vector<Node*> nodeList;

    void calculateHeuristics(Node& targetNode);

	void addToOpenList(Node* m_Node, Node& m_theParentNode, int m_G);

	bool setNodeStatusToClosed(Node &node);
	
	Node* A_Star(CubeGeomerty startNode, CubeGeomerty targetNode);

};

