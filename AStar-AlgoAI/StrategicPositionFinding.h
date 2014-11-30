#pragma once
#include <vector>
#include "GameWorld.h"

using namespace ds;

class StrategicPositionFinding
{
	
public:
	std::vector<Node*> nodeList;

	StrategicPositionFinding(void);
	~StrategicPositionFinding(void);	
	
	void calculateHeuristics(Node& targetNode);

	static bool  isLineOfSightPresent(ds::CubeGeomerty ,ds::CubeGeomerty );

	void addToOpenList(Node* m_Node);

	bool setNodeStatusToClosed(Node &node, CubeGeomerty &targetNode);
	
	Node* getClosestPosition(CubeGeomerty , CubeGeomerty );

};

