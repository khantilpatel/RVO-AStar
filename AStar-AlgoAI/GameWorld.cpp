#include "GameWorld.h"
#include <glut/glut.h>
#include <algorithm> 
#include "SpatialHashing.h"
using namespace ds;
using namespace std;


ds::Node m_map[_GRID_RESOLUTION_X_AXIS][_GRID_RESOLUTION_Y_AXIS] ;

std::vector<Agent*> m_agents;

std::vector<ds::Node> collisionNodes;

std::vector<ds::Node> coverNodes;

std::vector<std::vector<int> > agent_hashtable;

GameWorld::GameWorld(void)
{
	_COLOR_WALKABLE_NODE= glm::vec4(0.2f, 0.2f, 0.2f, 0.0f); // Dark Gray;
	_COLOR_COLLISON_NODE = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f); //Blue
	_COLOR_TARGET_NODE = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f); // Red
	_COLOR_START_NODE = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);

	
	//startNode = Node(1,3);
	//targetNode = Node(5,3);
}
	void GameWorld::setPlayer(Player* player)
	{
		m_player = player;
	}
void GameWorld::WorldInit()
{
	
	collisionNodes.reserve(100);
	m_agents.reserve(10);
	//Node n = Node(1,7);
	//n.setNodeStatus(LOCKED);
	collisionNodes.push_back(Node(2,0));
	collisionNodes.push_back(Node(2,1));
	collisionNodes.push_back(Node(2,4));
	collisionNodes.push_back(Node(2,5));
	collisionNodes.push_back(Node(2,6));

	collisionNodes.push_back(Node(9,10));
	collisionNodes.push_back(Node(9,9));
	collisionNodes.push_back(Node(9,8));
	collisionNodes.push_back(Node(9,7));
	collisionNodes.push_back(Node(9,6));
	collisionNodes.push_back(Node(9,5));
	collisionNodes.push_back(Node(9,4));
	collisionNodes.push_back(Node(9,3));

//	collisionNodes.push_back(n);

//	collisionNodes.push_back(Node(2,3));
	collisionNodes.push_back(Node(14,9));
	collisionNodes.push_back(Node(14,10));
	collisionNodes.push_back(Node(14,11));
	collisionNodes.push_back(Node(14,12));
	collisionNodes.push_back(Node(14,13));
	collisionNodes.push_back(Node(14,14));
	collisionNodes.push_back(Node(14,15));

	collisionNodes.push_back(Node(20,5));
	collisionNodes.push_back(Node(20,6));
	collisionNodes.push_back(Node(20,7));
	collisionNodes.push_back(Node(20,12));
	collisionNodes.push_back(Node(20,13));
	collisionNodes.push_back(Node(20,14));

//	coverNodes for strategic dicission
	coverNodes.push_back(Node(19,12, glm::vec3(1.0f,0.0f,0.0f)));
	coverNodes.push_back(Node(19,7, glm::vec3(1.0f,0.0f,0.0f)));

	coverNodes.push_back(Node(21,12, glm::vec3(-1.0f,0.0f,0.0f)));
	coverNodes.push_back(Node(21,7, glm::vec3(-1.0f,0.0f,0.0f)));

	coverNodes.push_back(Node(20,4, glm::vec3(0.0f,1.0f,0.0f)));
	
	createGrid();
	agent_hashtable.reserve(_GRID_RESOLUTION_X_AXIS * _GRID_RESOLUTION_Y_AXIS);
	 for (int i=0; i<_GRID_RESOLUTION_X_AXIS * _GRID_RESOLUTION_Y_AXIS; i++) {
		 agent_hashtable.push_back( vector<int>()) ;
	 }

		float velocity = 30;
		float max_velocity = 40;
		float max_acc = 10;
	//	0.5f, 2.0f, 7.5f, 2.0f
	    m_agents.push_back(new Agent(0, 
		m_map[0][14].getCubeCoordinates(), m_map[11][9].getCubeCoordinates(),glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),velocity, 10.0f,
		new ROVNavigationSystem(velocity, max_velocity, 7.5f, max_acc, 250)));

		m_agents.push_back(new Agent(1, m_map[11][9].getCubeCoordinates(),m_map[0][14].getCubeCoordinates(),
		glm::vec3(1.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,1.0f), velocity,10.0f,
		new ROVNavigationSystem(velocity, max_velocity, 7.5f, max_acc, 250))); // Initial Agent location

	   m_agents.push_back( new Agent(2, 
		m_map[0][9].getCubeCoordinates(), m_map[11][14].getCubeCoordinates(),glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),velocity,10.0f,
		new ROVNavigationSystem(velocity, max_velocity, 7.5f, max_acc, 250)));

	    m_agents.push_back( new Agent(3, 
		m_map[11][14].getCubeCoordinates(), m_map[0][9].getCubeCoordinates(),glm::vec3(0.0f,1.0f,0.0f),
		glm::vec3(1.0f,0.0f,0.0f),velocity,10.0f,
		new ROVNavigationSystem(velocity, max_velocity, 7.5f, max_acc, 250)));
	 // Initial Agent location


	setPlayer(new Player(glm::vec3( 19.0f,8.0f,0.0f),glm::vec3(-1.0f,0.0f,0.0f))); // Initial Player Location

	updatePF();
}
void GameWorld::createGrid()//ds::Node nodes[GameWorld::_GRID_RESOLUTION_X_AXIS][_GRID_RESOLUTION_Y_AXIS], vector<Node> collisionNodesCoords)
{
	float width_of_each_grid = _WINDOW_WIDTH  / _GRID_RESOLUTION_X_AXIS;
	float height_of_each_grid =  _WINDOW_HEIGHT / _GRID_RESOLUTION_Y_AXIS;

	for(int x=0; x < _GRID_RESOLUTION_X_AXIS; x++)
	{
		//float current_X_coord = x * width_of_each_grid;
		for(int y=0; y < _GRID_RESOLUTION_Y_AXIS; y++)
		{
			float current_Y_coord = y * height_of_each_grid;
			glm::vec3 a = glm::vec3(width_of_each_grid * (x), height_of_each_grid * (y), 0);
			glm::vec3 b = glm::vec3(width_of_each_grid * (x+1), height_of_each_grid * (y), 0);
			glm::vec3 c = glm::vec3(width_of_each_grid * (x+1), height_of_each_grid * (y+1), 0);
			glm::vec3 d = glm::vec3(width_of_each_grid * (x), height_of_each_grid * (y+1), 0);
			
			float half_width = width_of_each_grid * (x+0.5);

			float half_height = height_of_each_grid * (y+0.5);
			glm::vec3 center = glm::vec3(half_width, half_height , 0);
			
			float proximity=0;
			if(width_of_each_grid<height_of_each_grid)
				proximity = width_of_each_grid;
			else
				proximity = height_of_each_grid;

			m_map[x][y]= Node(x,y);
			m_map[x][y].setCubeCoordinates(CubeGeomerty(a,b,c,d,center,proximity,glm::vec3(x,y,0.0)));
		}
	}

	for (int i = 0; i < collisionNodes.size(); i++)
	{
		
		ds::Node currentCoord = collisionNodes[i];
		if( _GRID_RESOLUTION_X_AXIS > currentCoord.getX() && _GRID_RESOLUTION_Y_AXIS > currentCoord.getY()){
			(m_map[currentCoord.getX()][currentCoord.getY()]).setNodeType(NODE_COLLISION);
		//	(nodes[currentCoord.getX()][currentCoord.getY()]).getCubeCoordinates().setCubeColor(_COLOR_COLLISON_NODE);
			//node->setNodeType(ds::NODE_COLLISION);
		}
	}
	
}

void GameWorld::updatePF()
{
	for(int x=0; x < _GRID_RESOLUTION_X_AXIS; x++)
	{
		//float current_X_coord = x * width_of_each_grid;


		for(int y=0; y < _GRID_RESOLUTION_Y_AXIS; y++)
		{
			m_map[x][y].setPF(5);
		}
	}

	int x_dir = this->m_player->direction.x;
	int y_dir = this->m_player->direction.y;

	int x_loc = (int)this->m_player->m_pCurrent_location->location.x;
	int y_loc = (int)this->m_player->m_pCurrent_location->location.y;
	
		int min_pf = 4;
		// LEFT Direction
		if(x_dir == -1 && y_dir == 0)
		{
			int pf = 12;
			for(int x = x_loc; x >= x_loc-3; x--){
				
				for(int y = y_loc+2; y>= y_loc-2; y--)
				{
					if((x >= 0 && x <=_GRID_RESOLUTION_X_AXIS-1) && (y >= 0 && y <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						if(y == y_loc+2)
						{
							m_map[x][y].setPF(min_pf);
						}
						else if(y == y_loc-2)
						{
							m_map[x][y].setPF(min_pf);
						}
						else
						{
							m_map[x][y].setPF(pf);
						}
					}
				}
				pf = pf - 2;
			}

			int x1 = 0;
			x1 = x_loc + 1;
			for(int y = y_loc+2; y>= y_loc-2; y--)
				{
					if((x1 >= 0 && x1 <=_GRID_RESOLUTION_X_AXIS-1) && (y >= 0 && y <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						m_map[x1][y].setPF(min_pf);
					}
			}

			x1 = x_loc - 4;
			for(int y = y_loc+2; y>= y_loc-2; y--)
				{
					if((x1 >= 0 && x1 <=_GRID_RESOLUTION_X_AXIS-1) && (y >= 0 && y <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						m_map[x1][y].setPF(min_pf);
					}
			}


		}

		// RIGHT Direction
		if(x_dir == 1 && y_dir == 0)
		{
			int pf = 12;
			for(int x = x_loc; x <= x_loc+3; x++){				
				for(int y = y_loc+2; y>= y_loc-2; y--)
				{
					if((x >= 0 && x <=_GRID_RESOLUTION_X_AXIS-1) && (y >= 0 && y <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						if(y == y_loc+2)
						{
							m_map[x][y].setPF(min_pf);
						}
						else if(y == y_loc-2)
						{
							m_map[x][y].setPF(min_pf);
						}
						else
						{
							m_map[x][y].setPF(pf);
						}
					}
				}
				pf = pf - 2;
			}

			int x1 = 0;
			x1 = x_loc - 1;
			for(int y = y_loc+2; y>= y_loc-2; y--)
				{
					if((x1 >= 0 && x1 <=_GRID_RESOLUTION_X_AXIS-1) && (y >= 0 && y <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						m_map[x1][y].setPF(min_pf);
					}
			}

			x1 = x_loc + 4;
			for(int y = y_loc+2; y>= y_loc-2; y--)
				{
					if((x1 >= 0 && x1 <=_GRID_RESOLUTION_X_AXIS-1) && (y >= 0 && y <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						m_map[x1][y].setPF(min_pf);
					}
			}
		}

		// UP Direction
		if(x_dir == 0 && y_dir == 1)
		{
			int pf = 12;
			for(int y = y_loc; y<= y_loc+3; y++){		
			
				for(int x = x_loc+2; x >= x_loc-2; x--)
					{				
					if((x >= 0 && x <=_GRID_RESOLUTION_X_AXIS-1) && (y >= 0 && y <=_GRID_RESOLUTION_Y_AXIS))
					{
						if(x == x_loc+2)
						{
							m_map[x][y].setPF(min_pf);
						}
						else if(x == x_loc-2)
						{
							m_map[x][y].setPF(min_pf);
						}
						else
						{
							m_map[x][y].setPF(pf);
						}
					}
				}
					pf = pf - 2;
			}

			int y1 = 0 ;
			y1 = y_loc - 1;
			for(int x = x_loc+2; x >= x_loc-2; x--)
				{
					if((x >= 0 && x <=_GRID_RESOLUTION_X_AXIS-1) && (y1 >= 0 && y1 <=_GRID_RESOLUTION_Y_AXIS))
					{
						m_map[x][y1].setPF(min_pf);
					}
				}

			y1 = y_loc + 4;
			for(int x = x_loc+2; x >= x_loc-2; x--)
				{
					if((x >= 0 && x <=_GRID_RESOLUTION_X_AXIS-1) && (y1 >= 0 && y1 <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						m_map[x][y1].setPF(min_pf);
					}
				}
		}

			// UP Down
		if(x_dir == 0 && y_dir == -1)
		{
			int pf = 12;
			for(int y = y_loc; y>= y_loc-3; y--){		
			
				for(int x = x_loc+2; x >= x_loc-2; x--)
					{				
					if((x >= 0 && x <=_GRID_RESOLUTION_X_AXIS-1) && (y >= 0 && y <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						if(x == x_loc+2)
						{
							m_map[x][y].setPF(min_pf);
						}
						else if(x == x_loc-2)
						{
							m_map[x][y].setPF(min_pf);
						}
						else
						{
							m_map[x][y].setPF(pf);
						}
					}
				}
					pf = pf - 2;
			}

			int y1 = 0 ;
			y1 = y_loc + 1;
			for(int x = x_loc+2; x >= x_loc-2; x--)
				{
					if((x >= 0 && x <=_GRID_RESOLUTION_X_AXIS-1) && (y1 >= 0 && y1 <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						m_map[x][y1].setPF(min_pf);
					}
				}

			y1 = y_loc - 4;
			for(int x = x_loc+2; x >= x_loc-2; x--)
				{
					if((x >= 0 && x <=_GRID_RESOLUTION_X_AXIS-1) && (y1 >= 0 && y1 <=_GRID_RESOLUTION_Y_AXIS-1))
					{
						m_map[x][y1].setPF(min_pf);
					}
				}
		}
}

void updateEachAgent(Agent* agent)
{
	//agent->m_pCurrent_target = ;

}

void GameWorld::AIupdate()
{
	float width_of_each_grid = _WINDOW_WIDTH  / _GRID_RESOLUTION_X_AXIS;
	float height_of_each_grid =  _WINDOW_HEIGHT / _GRID_RESOLUTION_Y_AXIS;

	construct_hash_table(m_agents,
						  _GRID_RESOLUTION_X_AXIS, _GRID_RESOLUTION_Y_AXIS, width_of_each_grid, height_of_each_grid );

	for(int i = 0 ; i< m_agents.size(); i++)
	{
		//m_player->m_pCurrent_location->direction = m_player->direction;
	//	m_agents[i]->m_pCurrent_target = m_player->m_pCurrent_location;
	}

		for(int i = 0 ; i< m_agents.size(); i++)
		{
				m_agents[i]->UpdateAI(delta_time);
		}
	//for_each (m_agents.begin(), m_agents.end(), updateEachAgent);

}

void renderEachAgent(Agent* agent)
{
	(*agent).render();
}


void GameWorld::renderGame() // Overall render function 1.Render enviornment 2.Render Agents 3.Render Player
{
	//1.Render enviornment 
	renderGameEnviornment();
	//2.Render Agents 
	for_each (m_agents.begin(), m_agents.end(), renderEachAgent);
	//3.Render Player
	(*m_player).renderPlayer();
}



void GameWorld::renderGameEnviornment()
{
	glBegin(GL_QUADS); 
	for(int x=0; x< _GRID_RESOLUTION_X_AXIS; x++)
	{
		for(int y=0; y< _GRID_RESOLUTION_Y_AXIS; y++)
		{
			CubeGeomerty geo = m_map[x][y].getCubeCoordinates();
			             // Each set of 4 vertices form a quad
			
			if(m_map[x][y].getNodeType() == NodeType::NODE_WALKABLE)
			{
				 glColor3f(_COLOR_WALKABLE_NODE.x, _COLOR_WALKABLE_NODE.y,_COLOR_WALKABLE_NODE.z);
			 // Red
				if(m_map[x][y].getPF() == 5){
				 glColor3f(_COLOR_WALKABLE_NODE.x, _COLOR_WALKABLE_NODE.y,_COLOR_WALKABLE_NODE.z);
				}
				if(m_map[x][y].getPF() == 4){
				 //glColor3f(1.0,1.0,1.0);
				  glColor3f(_COLOR_WALKABLE_NODE.x, _COLOR_WALKABLE_NODE.y,_COLOR_WALKABLE_NODE.z);
				}

				if(m_map[x][y].getPF() == 6){
				  glColor3f(0.0,0.8,0.0);
				}

				if(m_map[x][y].getPF() == 8){
					 glColor3f(0.0,0.6,0.0);				
				}

				if(m_map[x][y].getPF() == 10){
					 glColor3f(0.0,0.3,0.0);
				}

				if(m_map[x][y].getPF() == 12){
				 
				  	 glColor3f(0.0,0.1,0.0);
				}
				
			}


			if(m_map[x][y].getNodeType() == NodeType::NODE_COLLISION)
			{
				glColor3f(_COLOR_COLLISON_NODE.x,_COLOR_COLLISON_NODE.y,_COLOR_COLLISON_NODE.z); // Red
				
			}
		

			//if(m_map[x][y].getNodeStatus() == PATH)
			//{
				//glColor3f(_COLOR_TARGET_NODE.x, _COLOR_TARGET_NODE.y,_COLOR_TARGET_NODE.z); // Red
			//}
			
			glVertex2f(geo.a.x, geo.a.y);     // Define vertices in counter-clockwise (CCW) order
			glVertex2f(geo.b.x, geo.b.y);     //  so that the normal (front-face) is facing you
			glVertex2f(geo.c.x, geo.c.y);
			glVertex2f(geo.d.x, geo.d.y);
		
			
			
		}
	}

 glEnd();

	for(int x=0; x< _GRID_RESOLUTION_X_AXIS; x++)
	{
		for(int y=0; y< _GRID_RESOLUTION_Y_AXIS; y++)
		{
			CubeGeomerty geo = m_map[x][y].getCubeCoordinates();
					glLineWidth(0.1);
				glBegin(GL_LINE_LOOP);
		
					glColor3f(0.0f, 1.0f, 0.0f);
					//glVertex2f(p1.x(), p1.y());

				    glVertex2f(geo.a.x, geo.a.y);     // Define vertices in counter-clockwise (CCW) order
					glVertex2f(geo.b.x, geo.b.y);     //  so that the normal (front-face) is facing you
					glVertex2f(geo.c.x, geo.c.y);
					glVertex2f(geo.d.x, geo.d.y);
					glVertex2f(geo.a.x, geo.a.y);
				glEnd();
		}
	}
	//	for (std::vector<Node>::iterator it = coverNodes.begin() ; it != coverNodes.end(); ++it)
	//		{
	//		int x_loc_node = (int)(*it).getX();
	//		int y_loc_node = (int)(*it).getY();
	//		CubeGeomerty geo = m_map[x_loc_node][y_loc_node].getCubeCoordinates();
	//		glBegin(GL_QUADS);
	//		glColor3f(0.5,0.5,0.0); // Red
	//		glVertex2f(geo.a.x, geo.a.y);     // Define vertices in counter-clockwise (CCW) order
	//		glVertex2f(geo.b.x, geo.b.y);     //  so that the normal (front-face) is facing you
	//		glVertex2f(geo.c.x, geo.c.y);
	//		glVertex2f(geo.d.x, geo.d.y);
	//		glEnd();
	//		int height = (int)geo.d.y - (int)geo.a.y;
	//	int width  = (int)geo.b.x - (int)geo.a.x;

	//	// Generate Center points
	//	int x_dir_center = (int)geo.a.x + 0.5 * width;
	//	int y_dir_center = (int)geo.a.y + 0.5 * height;
	//	
	//	int x_dir_pt = 0;
	//	int y_dir_pt = 0;

	//	int x_dir = (int)(int)(*it).direction.x;
	//	int y_dir = (int)(*it).direction.y;

	//	// Generate middle point on line in direction
	//	if(x_dir == 0 && y_dir == 1)
	//	{
	//		x_dir_pt = x_dir_center;
	//		y_dir_pt = y_dir_center + 0.5 * height;
	//	}

	//	if(x_dir == 0 && y_dir == -1)
	//	{
	//		x_dir_pt = x_dir_center;
	//		y_dir_pt = y_dir_center - 0.5 * height;
	//	}

	//	if(x_dir == 1 && y_dir == 0)
	//	{
	//		x_dir_pt = x_dir_center + 0.5 * width;
	//		y_dir_pt = y_dir_center;
	//	}

	//	if(x_dir == -1 && y_dir == 0)
	//	{
	//		x_dir_pt = x_dir_center - 0.5 * width;
	//		y_dir_pt = y_dir_center;
	//	}

	//	//Draw line
	//	glLineWidth(2.5);
	//
	///*	glBegin(GL_LINES);
	//	glColor3f(1.0, 0.0, 0.0);
	//	glVertex3f(x_dir_center, y_dir_center, 0.0);
	//	glVertex3f(x_dir_pt, y_dir_pt, 0.0);
	//	glEnd();*/
				
		//	}


}