#include "Node.h"
#include <glm/glm.hpp>

namespace ds{

	int Node::getF()
	{
		return G + H;
	}

	void Node::setF(int m_F)
	{
		F = m_F;

	}

	int Node::getPF()
	{
		return PF;
	}

	void Node::setPF(int m_PF)
	{
		PF = m_PF;

	}

	int Node::getH()
	{
		return H;
	}

	void Node::setH(int m_H)
	{
		H = m_H;
		F = G + H;
	}

	void Node::setG(int m_G)
	{
		G = m_G;
		F = G + H;
	}

	int Node::getG()
	{
		return G ;
	}


	Node* Node::getParentNode()
	{
		return parentNode;
	}

	void Node::setParentNode(Node* m_ParentNode)
	{
		parentNode = m_ParentNode;
	}

	//bool Node::operator()(Node n1, Node n2)
	//{
	//	if(n1.getF() < n2.getF() && OPEN == n1.nodeStatus)
	//		return true;
	//	else
	//		return false;
	//
	//}

	void Node::setNodeType(NodeType m_NodeType)
	{
		nodeType = m_NodeType;
	}

	NodeType Node::getNodeType()
	{
		return nodeType;
	}

	NodeStatus Node::getNodeStatus()
	{
		return nodeStatus;
	}

	void Node::setNodeStatus(NodeStatus m_NodeStatus)
	{
		nodeStatus = m_NodeStatus;
	}

	Node::Node()
	{
	}

	Node::Node(int m_X, int m_Y)
	{

		x = m_X;
		y = m_Y;
		H = 0;
		G = 0;
		PF = 5;
		parentNode = nullptr;
		nodeType= NODE_WALKABLE;
		nodeStatus = NONE;
	
	}

	Node::Node(int m_X, int m_Y, glm::vec3 m_direction)
	{

		x = m_X;
		y = m_Y;
		H = 0;
		G = 0;
		PF = 5;
		parentNode = nullptr;
		nodeType= NODE_WALKABLE;
		nodeStatus = NONE;
		direction = m_direction;
	}

	int  Node::getX()
	{
		return x;
	}

	int  Node::getY()
	{
		return y;
	}

	void Node::setX(int m_X)
	{
		x = m_X;
	}

	void Node::setY(int m_Y)
	{
		x = m_Y;
	}

	CubeGeomerty Node::getCubeCoordinates()
	{
		return cubeCoordinates;
	}

	void Node::setCubeCoordinates(CubeGeomerty m_cube_Coordinates)
	{
		cubeCoordinates = m_cube_Coordinates;
	}
}