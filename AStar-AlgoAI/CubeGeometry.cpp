#include "CubeGeometry.h"


using namespace ds;
using namespace glm;
CubeGeomerty::CubeGeomerty()
{
}
CubeGeomerty::CubeGeomerty(glm::vec3 m_a, glm::vec3 m_b, glm::vec3 m_c, glm::vec3 m_d, glm::vec3 m_center, float m_proximity ,glm::vec3 m_location)
{
	a = m_a;
	b = m_b; 
	c = m_c;
	d = m_d;
	center = m_center;
	location = m_location;
	proximity = m_proximity;
	//asPtr = m_center;
	//color = m_color;
}

CubeGeomerty::CubeGeomerty(glm::vec3 m_location)
{
	a = vec3(0.0,0.0,0.0);
	b = vec3(0.0,0.0,0.0); 
	c = vec3(0.0,0.0,0.0);
	d = vec3(0.0,0.0,0.0);
	color = vec4(0.0,0.0,0.0,0.0);
	this->location = m_location;//color = m_color;
	this->direction = vec3(0.0,0.0,0.0);
	//this->asPtr = vec3(0.0,0.0,0.0);
}

CubeGeomerty::CubeGeomerty(glm::vec3 m_location, glm::vec3 m_direction)
{
	a = vec3(0.0,0.0,0.0);
	b = vec3(0.0,0.0,0.0); 
	c = vec3(0.0,0.0,0.0);
	d = vec3(0.0,0.0,0.0);
	color = vec4(0.0,0.0,0.0,0.0);
	this->location = m_location;//color = m_color;
	this->direction = m_direction;
}

//glm::vec4 CubeGeomerty::getCubeColor()
//{
//	return color;
//}
//void CubeGeomerty::setCubeColor(glm::vec4 m_color)
//{
//	color = m_color;
//}
//
