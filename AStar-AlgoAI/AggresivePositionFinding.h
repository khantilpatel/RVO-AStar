#pragma once
#include <vector>
#include "GameWorld.h"

using namespace ds;

class AggresivePositionFinding
{
	
public:
	std::vector<Node*> nodeList;

	AggresivePositionFinding(void);
	~AggresivePositionFinding(void);	
	
	void calculateHeuristics(Node& targetNode);

	void addToOpenList(Node* m_Node);

	bool setNodeStatusToClosed(Node &node, CubeGeomerty &targetNode);
	
	Node* getClosestPosition(CubeGeomerty startNode, CubeGeomerty targetNode);

};

