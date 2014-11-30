
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "CubeGeometry.h"

namespace ds {

	//#define sortBy_FValue_NodeStatus(Node,Node)

	enum NodeType
	{
		NODE_COLLISION, NODE_WALKABLE, NODE_WATER
	};

	enum NodeStatus
	{
		NONE, CLOSSED, OPEN, LOCKED
	};


	
	class Node{
	private:	
		int G;
		int H;
		int F;
		int PF; //Potential Field
		int x;
		int y;
		Node* parentNode;
		NodeType nodeType;
		NodeStatus nodeStatus;
		CubeGeomerty cubeCoordinates;


	public:
		//Public Methods Declaration
		int getG();
		void setG(int);
		int getH();
		void setH(int);
		int getF();
		void setF(int);
		int getPF();
		void setPF(int);

		int getX();
		int getY();
		void setX(int);
		void setY(int);

		glm::vec3 direction;

		CubeGeomerty getCubeCoordinates();
		void setCubeCoordinates(CubeGeomerty);

		Node* getParentNode();
		void setParentNode(Node*);

		//bool operator()(Node n1, Node n2);

		NodeType getNodeType();
		NodeStatus getNodeStatus();
		void setNodeType(NodeType);
		void setNodeStatus(NodeStatus);
		//Constructor Definetions
		Node();
		Node(int , int);
		Node(int , int, glm::vec3);


	};

	bool static sortBy_FValue_NodeStatus(Node* n1, Node* n2)
	{
		if(OPEN == (*n1).getNodeStatus() && OPEN == (*n2).getNodeStatus())
		{
			if((*n1).getF() < (*n2).getF())
				return true;
			else
				return false;

		} else if(OPEN == (*n1).getNodeStatus() && CLOSSED == (*n2).getNodeStatus())
		{
			return true;		
		} else if(CLOSSED == (*n1).getNodeStatus() && CLOSSED == (*n2).getNodeStatus())
		{
			if((*n1).getF() < (*n2).getF())
				return true;
			else
				return false;

		} else if(CLOSSED == (*n1).getNodeStatus() && OPEN == (*n2).getNodeStatus())
		{		
			return false;

		} 
	}

	bool static sortBy_Node_Huristics(Node* n1, Node* n2)
	{
		if((*n1).getH() < (*n2).getH())
			return true;
		else
			return false;

	
	}

}