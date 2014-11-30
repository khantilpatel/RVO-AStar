#pragma once
#include <vector>
#include "GameWorld.h"

using namespace ds;

class DefensivePositionFinding
{
	
public:
	std::vector<Node*> nodeList;

	DefensivePositionFinding(void);
	~DefensivePositionFinding(void);	
	
	void calculateHeuristics(Node& targetNode);

	static bool  isLineOfSightPresent(ds::CubeGeomerty ,ds::CubeGeomerty );

	void addToOpenList(Node* m_Node);

	bool setNodeStatusToClosed(Node &node, CubeGeomerty &targetNode);
	
	Node* getClosestPosition(CubeGeomerty startNode, CubeGeomerty targetNode);

};

